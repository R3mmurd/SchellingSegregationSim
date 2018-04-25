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

# ifndef VALUES_H
# define VALUES_H

# include <singleton.H>

class Values : public Designar::Singleton<Values>
{
  friend class Singleton<Values>;

  static constexpr double OFF_SET = 0.7;

  size_t map_width;
  size_t map_height;
  size_t num_agents;
  size_t tolerance;
  size_t num_steps;
  size_t refresh_time;

public:
  Values();

  size_t get_map_width() const;

  size_t get_map_height() const;

  size_t get_num_agents() const;

  size_t get_tolerance() const;

  size_t get_num_steps() const;

  size_t get_refresh_time() const;
};

# endif // VALUES_H
