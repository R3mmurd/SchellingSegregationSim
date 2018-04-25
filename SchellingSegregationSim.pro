
#  This file is part of Schelling Segregation Simulator.
#  Copyright (C) 2013 by Alejandro J. Mujica

#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#  Any user request of this software, write to

#  Alejandro Mujica

#  aledrums@gmail.com

QT += core widgets

QMAKE_CXX = clang++

INCLUDEPATH += ../DeSIGNAR/include

CONFIG += c++14

HEADERS += \
    values.H \
    panel.H \ 
    board.H

SOURCES += \
    values.C \
    main.C \
    panel.C \
    board.C
