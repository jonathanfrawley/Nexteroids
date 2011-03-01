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
#ifndef  NXNEXTEROIDSGAMELOGIC_H
#define  NXNEXTEROIDSGAMELOGIC_H

#include <iostream>

#include <nxGeom/nxPoint3.hpp>
#include <nxActor/nxSpaceshipActor.hpp>
#include <nxActor/nxRockActor.hpp>
#include <nxGameLogic/nxGameOptions.hpp>
#include <nxGameLogic/nxNexteroidsBaseGameLogic.hpp>
#include <nxGameLogic/nxNexteroidsGameLogicEventListener.hpp>
#include <nxGameLogic/nxGameState.hpp>
#include <nxEvent/nxIEventManager.hpp>

/*
 * =====================================================================================
 *        Class: nxNexteroidsGameLogic
 *  Description: Actual nexteroids game logic.
 * =====================================================================================
 */
class nxNexteroidsGameLogic : public nxNexteroidsBaseGameLogic
{
	public:
		nxNexteroidsGameLogic(nxGameOptions const &options);

		virtual ~nxNexteroidsGameLogic();

		virtual void VInit();

		void VOnUpdate(int deltaMilliseconds);

		virtual void VBuildLevel00();

		void ListenForProxyNexteroidsGameLogicEvents();

        void ListenForNexteroidsGameLogicEvents();

		void SpawnActor(nxActorType type);

	protected:
		nxEventListenerPtr m_EventListener;
		bool m_HasBuiltLevel;
		int m_Time;


	private:
};


#endif   // NXNEXTEROIDSGAMELOGIC_H
