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
#include "nxRockActor.hpp"

nxRockActor::nxRockActor()
	:
		nxBaseActor(NX_ACTOR_ROCK)
{

}

nxRockActor::nxRockActor(nxReal yrot, nxPoint3 pos, float radius, float speed)
	:
		nxBaseActor(yrot, pos, NX_ACTOR_ROCK)
		,m_Radius(radius)
		,m_Speed(speed)
		,m_RockType(0)
{
}

nxRockActor::~nxRockActor()
{
}

void nxRockActor::VCreate() 
{
	switch(m_RockType)
	{
		case 0:
			{
			//TODO: Have multiple rock types
			nxPoint3 p0(-2*m_Radius, 0, 0);
			nxPoint3 p1(-1*m_Radius, -2*m_Radius, 0);
			nxPoint3 p2(2*m_Radius, -1*m_Radius, 0);
			nxPoint3 p3(2*m_Radius, 1*m_Radius, 0);
			nxPoint3 p4(-1*m_Radius, 2*m_Radius, 0);
			m_Points.push_back(p0);
			m_Points.push_back(p1);
			m_Points.push_back(p2);
			m_Points.push_back(p3);
			m_Points.push_back(p4);
			break;
			}
		case 1:
			{
			nxPoint3 p0(-2*m_Radius, 0, 0);
			nxPoint3 p1(-1*m_Radius, -2*m_Radius, 0);
			nxPoint3 p2(2*m_Radius, -1*m_Radius, 0);
			m_Points.push_back(p0);
			m_Points.push_back(p1);
			m_Points.push_back(p2);
			break;
			}
		default:
			{
			assert(0 && "Invalid rock type");
			break;
			}
	}
	return;
}
