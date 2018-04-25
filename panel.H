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

# ifndef PANEL_H
# define PANEL_H

# include <QWidget>
# include <QThread>
# include <QPainter>

# include <board.H>

# define SCALE 10

class Panel;

struct BoardExecutor : public QThread
{
  Board & board;

  BoardExecutor(Board & _map) : board(_map) { }

  void run()
  {
    board.exec();
  }
};

struct Repainter : public QThread
{
  Panel * panel;

  bool stopped;

  Repainter(Panel * _panel) : panel(_panel), stopped(false) { }

  void stop()
  {
    stopped = true;
  }

  void run();
};

class Panel : public QWidget
{
  Q_OBJECT

  Board map;

  BoardExecutor exec_map;

  Repainter repainter;

protected:
  void closeEvent(QCloseEvent *);

public:
  Panel(QWidget * parent = 0);

  void paintEvent(QPaintEvent *);

public slots:
  void board_finished();
};

# endif // PANEL_H
