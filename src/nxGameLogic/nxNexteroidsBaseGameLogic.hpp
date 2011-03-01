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
#ifndef  NXNEXTEROIDSBASEGAMELOGIC_H
#define  NXNEXTEROIDSBASEGAMELOGIC_H

#include <nxGameLogic/nxGameOptions.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>
#include <nxGameLogic/nxNexteroidsGameData.hpp>
#include <nxCore/nxTypes.hpp>

/*
 * =====================================================================================
 *        Class: nxNexteroidsBaseGameLogic
 *  Description: Base for nexteroids game logic.
 * =====================================================================================
 */
class nxNexteroidsBaseGameLogic : public nxBaseGameLogic
{
	public:
		nxNexteroidsBaseGameLogic(nxGameOptions const &options);

		virtual ~nxNexteroidsBaseGameLogic();

		virtual void VBuildLevel00() = 0;

		virtual void VAddActor(shared_ptr<nxIActor> actor);
		
		virtual void VRemoveActor(nxActorId actor);

		virtual void VRegisterHit(nxActorId rock, nxActorId ship);

		virtual void SpawnActor(nxActorType type) = 0;

	protected:
		nxNexteroidsGameData m_Data;
	private:
};

#endif   // NXNEXTEROIDSBASEGAMELOGIC_H
