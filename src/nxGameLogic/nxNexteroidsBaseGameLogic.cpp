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
#include "nxNexteroidsBaseGameLogic.hpp"

nxNexteroidsBaseGameLogic::nxNexteroidsBaseGameLogic(nxGameOptions const &options)
	:
		nxBaseGameLogic(options)	
{
}

nxNexteroidsBaseGameLogic::~nxNexteroidsBaseGameLogic()
{
}


void nxNexteroidsBaseGameLogic::VAddActor(shared_ptr<nxIActor> actor)
{
	nxBaseGameLogic::VAddActor(actor);
	if (actor->VGetType()==NX_ACTOR_SPACESHIP)
	{
		m_Data.UpdateScore(actor->VGetId(), 0);
	}
	m_pPhysics->VCreateActor(actor);
}

void nxNexteroidsBaseGameLogic::VRemoveActor(nxActorId aid)
{
	shared_ptr<nxIActor> actor = VGetActor(aid);
	if (actor->VGetType()==NX_ACTOR_SPACESHIP)
	{
		m_Data.UpdateScore(actor->VGetId(), 0);
	}
	nxBaseGameLogic::VRemoveActor(aid);
}

void nxNexteroidsBaseGameLogic::VRegisterHit(nxActorId rockId, nxActorId shipId)
{
	if (m_bProxy)
	{
		return;
	}
	shared_ptr<nxIActor> ship = VGetActor(shipId);

	int pointsPerRock = 10;
	m_Data.UpdateScore(ship->VGetId(), m_Data.GetScore(ship->VGetId()) + pointsPerRock);
}
