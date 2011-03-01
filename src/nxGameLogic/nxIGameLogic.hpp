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
#ifndef  NXIGAMELOGIC_H
#define  NXIGAMELOGIC_H

#include <nxCore/nxCore.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxActor/nxIActor.hpp>
#include <nxGameLogic/nxGameState.hpp>

#include <string>

/*
 * =====================================================================================
 *        Class: nxIGameLogic
 *  Description: Interface for all game logics to implement.
 * =====================================================================================
 */
class nxIGameLogic
{
	public:
		virtual shared_ptr<nxIActor> VGetActor(const nxActorId id)=0;

		virtual void VInit() = 0;

		virtual void VAddActor(shared_ptr<nxIActor> actor)=0;

		virtual void VRemoveActor(nxActorId id)=0;

		virtual bool VLoadGame(std::string gameName)=0;

		virtual void VOnUpdate(int deltaMilliseconds)=0;	

		virtual void VChangeState(nxGameState newState)=0;
};

#endif   // NXIGAMELOGIC_H
