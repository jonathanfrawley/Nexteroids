/**
Nexteroids - A cross platform, networked asteroids game.
Copyright (C) 2010 Jonathan Frawley

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
**/
#ifndef  NXMATH_H
#define  NXMATH_H

#include <math.h>
#include <nxGeom/nxPoint3.hpp>

const double NX_PI = 3.14159265;
const double NX_PI_OVER_2 = 1.57079633;
const double NX_PI_OVER_3 = 1.04719755;
const double NX_PI_OVER_4 = 0.785398163;
const double NX_PI_OVER_6 = 0.523598775;
const double NX_PI_OVER_8 = 0.392699082;
const double NX_PI_OVER_12 = 0.261799388;
const double NX_PI_OVER_16 = 0.196349540;
const double NX_PI_OVER_32 = 0.098174770;
const double NX_PI_OVER_64 = 0.098174770;
const double NX_PI_OVER_128 = 0.049087385;

inline float nx_degrees_to_radians(float degrees)
{
	return (degrees*NX_PI) / 180;
}

inline float nx_radians_to_degrees(float radians)
{
	return (radians*180) / NX_PI;
}

inline float nx_square(float a)
{
	return (a*a);
}

inline float nx_cube(float a)
{
	return (a*a*a);
}

inline float nx_distance(nxPoint3 a, nxPoint3 b)
{
	return sqrt(
				nx_square(b.GetX() - a.GetX()) + 
				nx_square(b.GetY() - a.GetY()) +
				nx_square(b.GetZ() - a.GetZ())
				);
}

#endif   // NXMATH_H
