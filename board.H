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

# ifndef BOARD_H
# define BOARD_H

# include <stdexcept>
# include <random>

class Board
{
public:
  enum class Status
  {
    Busy_By_Ethnicity_1, Busy_By_Ethnicity_2, Empty, Num_Status
  };

private:
  std::mt19937 rng;

  using unif_dist_t = std::uniform_int_distribution<int>;

  unif_dist_t dist_cols;

  unif_dist_t dist_rows;

  using coin_dist_t = std::bernoulli_distribution;

  coin_dist_t coin;

  Status ** matrix;

  void init();

  bool is_good_for(size_t, size_t, Status) const;

  void move(size_t, size_t, Status);

public:
  Board();

  ~Board();

  Status get(size_t, size_t) const;

  void exec();
};

# endif // BOARD_H
