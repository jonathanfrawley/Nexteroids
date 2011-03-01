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
#include "nxBaseActor.hpp"

#include <nxActor/nxSpaceshipActor.hpp>
#include <nxActor/nxRockActor.hpp>
#include <nxActor/nxBulletActor.hpp>

nxIActor* nxBaseActor::CreateFromStream(stringstream &in)
{
	int actorType;
	in >> actorType;

	nxIActor *actor = NULL;
	switch (actorType)
	{
		case NX_ACTOR_SPACESHIP:
			actor = NX_NEW nxSpaceshipActor();
			break;
		case NX_ACTOR_BULLET:
			actor = NX_NEW nxBulletActor();
			break;
		case NX_ACTOR_ROCK:
			actor = NX_NEW nxRockActor();
			break;
		default:
			assert(0 && "Unimplemented actor type in stream");
			return 0;
	}

	actor->VInit(in);

	return actor;
}
