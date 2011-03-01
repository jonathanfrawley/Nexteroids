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
#ifndef  NXACTORDEATHEVENTDATA_H
#define  NXACTORDEATHEVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>
#include <nxActor/nxBaseActor.hpp>

/*
 * =====================================================================================
 *        Class: nxActorDeathEventData
 *  Description: Event which represents an actor death.
 * =====================================================================================
 */
class nxActorDeathEventData : public nxBaseEventData
{
	public:
		nxActorDeathEventData();

		nxActorDeathEventData(nxActorId actorId)
			:
				nxBaseEventData(),
				m_ActorId(actorId)
		{
			m_EventType = NX_EVENT_ActorDeath;
		}

		nxActorDeathEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_ActorDeath;
			in >> m_ActorId;
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << m_ActorId << " ";
		}

		virtual ~nxActorDeathEventData()
		{
		}

		nxActorId GetActorId() const
		{
			return m_ActorId;
		}

	protected:
		nxActorId m_ActorId;

	private:
};

#endif   // NXACTORDEATHEVENTDATA_H
