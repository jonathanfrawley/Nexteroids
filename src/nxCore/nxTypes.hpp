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
#ifndef  NXTYPES_H
#define  NXTYPES_H

typedef unsigned int nxActorId;
typedef float nxReal;
enum nxActorType { NX_ACTOR_UNKOWN, NX_ACTOR_SPACESHIP, NX_ACTOR_BULLET, NX_ACTOR_ROCK };

typedef struct _nxColour
{
	nxReal r;
	nxReal g;
	nxReal b;
	nxReal alpha;
} nxColour;

#endif   // NXTYPES_H
