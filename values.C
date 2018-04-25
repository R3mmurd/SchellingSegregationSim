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

# include <values.H>
# include <fstream>

# define SIZE 100

Values::Values()
  : map_width(SIZE), map_height(SIZE), num_agents(SIZE * SIZE * 0.7),
    tolerance(7), num_steps(1000000), refresh_time(2)
{
  std::ifstream file("data.txt");

  if (not file)
    return;

  file >> map_width >> map_height >> num_agents >> tolerance >> num_steps
       >> refresh_time;

  if (num_agents > map_width * map_height * OFF_SET)
    num_agents = map_width * map_height * OFF_SET;
}

size_t Values::get_map_width() const
{
  return map_width;
}

size_t Values::get_map_height() const
{
  return map_height;
}

size_t Values::get_num_agents() const
{
  return num_agents;
}

size_t Values::get_tolerance() const
{
  return tolerance;
}

size_t Values::get_num_steps() const
{
  return num_steps;
}

size_t Values::get_refresh_time() const
{
  return refresh_time;
}

