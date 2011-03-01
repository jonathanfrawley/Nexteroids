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
#ifndef  NXPHYSCOLLISIONEVENTDATA_H
#define  NXPHYSCOLLISIONEVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxPhysCollisionEventData
 *  Description: Collision of two actors in the physics world.
 * =====================================================================================
 */
class nxPhysCollisionEventData : public nxBaseEventData
{
	public:
		nxPhysCollisionEventData();

		nxPhysCollisionEventData(nxActorId actorIdA, nxActorId actorIdB)
			:
				nxBaseEventData(),
				m_ActorIdA(actorIdA),
				m_ActorIdB(actorIdB)
		{
			m_EventType = NX_EVENT_PhysCollision;
		}

		virtual ~nxPhysCollisionEventData()
		{
		}

		nxActorId GetActorIdA() const
		{
			return m_ActorIdA;
		}

		nxActorId GetActorIdB() const
		{
			return m_ActorIdB;
		}

	protected:
		nxActorId m_ActorIdA;
		nxActorId m_ActorIdB;

	private:
};

#endif   // NXPHYSCOLLISIONEVENTDATA_H
