/*
  This file is part of Schelling Segregation Simulator.
  Copyright (C) 2013 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
*/

# include <panel.H>
# include <values.H>

void Repainter::run()
{
  while (not stopped)
    {
      sleep(Values::get_instance().get_refresh_time());
      panel->repaint();
    }
}

Panel::Panel(QWidget *parent)
  : QWidget(parent), exec_map(map), repainter(this)
{
  Values & values = Values::get_instance();
  setWindowTitle("Population");
  setFixedSize(values.get_map_width() * SCALE, values.get_map_height() * SCALE);

  connect(&exec_map, SIGNAL(finished()), this, SLOT(board_finished()));

  repainter.start();
  exec_map.start();
  move(0, 0);
}

void Panel::closeEvent(QCloseEvent *)
{
  repainter.stop();
}

void Panel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  Values & values = Values::get_instance();
  const size_t & height = values.get_map_height();
  const size_t & width = values.get_map_width();

  for (size_t i = 0; i < height; ++i)
    for (size_t j = 0; j < width; ++j)
      {
        switch (map.get(i, j))
          {
          case Board::Status::Busy_By_Ethnicity_1:
            painter.setBrush(Qt::red);
            break;
          case Board::Status::Busy_By_Ethnicity_2:
            painter.setBrush(Qt::darkGreen);
            break;
          default:
            painter.setBrush(Qt::black);
          }
        painter.drawRect(j * SCALE, i * SCALE, SCALE, SCALE);
    }
}

void Panel::board_finished()
{
  repainter.stop();
  repaint();
}

