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

# include <unistd.h>
# include <iostream>

# include <board.H>

# include <values.H>

# include <QThread>

# define CONDITION s == ethnicity or s == Board::Status::Empty
# define PAUSE 5

void Board::init()
{
  Values & values = Values::get_instance();

  const size_t & height = values.get_map_height();
  const size_t & width = values.get_map_width();
  const size_t & num_agents = values.get_num_agents();

  dist_cols.param(unif_dist_t::param_type(0, int(width) - 1));
  dist_rows.param(unif_dist_t::param_type(0, int(height) - 1));

  matrix = new Status *[height];

  for (size_t i = 0; i < height; ++i)
    {
      matrix[i] = new Status[width];
      for (size_t j = 0; j < width; ++j)
        matrix[i][j] = Status::Empty;
    }

  for (size_t k = 0; k < num_agents; )
    {
      size_t i = dist_rows(rng);
      size_t j = dist_cols(rng);

      if (matrix[i][j] != Status::Empty)
        continue;

      double p = coin(rng);

      if (p)
        matrix[i][j] = Status::Busy_By_Ethnicity_1;
      else
        matrix[i][j] = Status::Busy_By_Ethnicity_2 ;

      ++k;
    }
}

bool Board::is_good_for(size_t i, size_t j,
                      Status ethnicity) const
{
  size_t num = 0;

  try
  {
    Status s = get(i - 1, j - 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i, j - 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i + 1, j - 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i - 1, j);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i + 1, j);
    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i - 1, j + 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i, j + 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  try
  {
    Status s = get(i + 1, j + 1);

    if (CONDITION)
      ++num;
  }
  catch(...)
  {
    // nothing
  }

  if (num >= Values::get_instance().get_tolerance())
    return true;
  return false;
}

void Board::move(size_t _i, size_t _j,
               Status ethnicity)
{
  Values & values = Values::get_instance();

  const size_t & height = values.get_map_height();
  const size_t & width = values.get_map_width();

  for (size_t i = 0; i < height; ++i)
    for (size_t j = 0; j < width; ++j)
      {
        if (matrix[i][j] != Board::Status::Empty)
          continue;

        if (not is_good_for(i, j, ethnicity))
          continue;

        std::swap(matrix[i][j], matrix[_i][_j]);
        return;
      }
}


Board::Board()
  : rng(time(nullptr)), coin(0.5)
{
  init();
}

Board::~Board()
{
  const size_t & height = Values::get_instance().get_map_height();

  for (size_t i = 0; i < height; ++i)
    delete [] matrix[i];
  delete [] matrix;
}

Board::Status Board::get(size_t i, size_t j) const
{
  Values & values = Values::get_instance();

  const size_t & height = values.get_map_height();
  const size_t & width = values.get_map_width();

  if (i >= height or j >= width)
    throw std::overflow_error("Cell is not valid");

  return matrix[i][j];
}

void Board::exec()
{
  Values & values = Values::get_instance();

  const size_t & num_steps = values.get_num_steps();

  size_t k = 0, i, j;

  while (k < num_steps)
    {
      i = dist_rows(rng);
      j = dist_cols(rng);

      if (matrix[i][j] == Board::Status::Empty)
        continue;

      ++k;

      if (is_good_for(i, j, matrix[i][j]))
        continue;

      move(i, j, matrix[i][j]);
    }
}

