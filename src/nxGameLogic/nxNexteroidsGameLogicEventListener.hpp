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
#ifndef  NXNEXTEROIDSGAMELOGICEVENTLISTENER_H
#define  NXNEXTEROIDSGAMELOGICEVENTLISTENER_H

#include <nxGameLogic/nxNexteroidsBaseGameLogic.hpp>
#include <nxEvent/nxEventListener.hpp>
#include <nxEvent/nxEventType.hpp>
#include <nxEvent/nxRequestNewActorEventData.hpp>
#include <nxEvent/nxNewActorEventData.hpp>
#include <nxEvent/nxThrustEventData.hpp>
#include <nxEvent/nxSteerEventData.hpp>
#include <nxEvent/nxFireWeaponEventData.hpp>
#include <nxEvent/nxPhysCollisionEventData.hpp>
#include <nxEvent/nxActorDeathEventData.hpp>
#include <nxEvent/nxActorMovedEventData.hpp>

/*
 * =====================================================================================
 *        Class: nxNexteroidsGameLogicEventListener
 *  Description: Event Listener for the game logic.
 * =====================================================================================
 */
class nxNexteroidsGameLogicEventListener : public nxEventListener
{
	public:
		nxNexteroidsGameLogicEventListener(nxNexteroidsBaseGameLogic* gameLogic)
			:
				m_pGameLogic(gameLogic)
		{
		}

		virtual ~nxNexteroidsGameLogicEventListener()
		{
		}

		virtual char const * GetName(void)
		{
			return "nxNexteroidsGameViewEventListener";
		}

		virtual bool HandleEvent( nxIEventData const & event );

	protected:
		nxNexteroidsBaseGameLogic* m_pGameLogic;
	private:
};


#endif   // NXNEXTEROIDSGAMELOGICEVENTLISTENER_H
