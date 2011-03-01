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
#include "nxBulletActor.hpp"

nxBulletActor::nxBulletActor()
	:
		nxBaseActor(NX_ACTOR_SPACESHIP)
{
}

nxBulletActor::nxBulletActor(nxReal yrot, nxPoint3 pos, float radius, float speed)
	:
		nxBaseActor(yrot, pos, NX_ACTOR_BULLET)
		,m_Radius(radius)
		,m_Speed(speed)
{
}

nxBulletActor::~nxBulletActor()
{
}
