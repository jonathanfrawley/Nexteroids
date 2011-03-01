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
#ifndef  NXFIREWEAPONEVENTDATA_H
#define  NXFIREWEAPONEVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxFireWeaponEventData
 *  Description: Represents a weapon being fired.
 * =====================================================================================
 */
class nxFireWeaponEventData : public nxBaseEventData
{
	public:
		nxFireWeaponEventData();

		nxFireWeaponEventData(nxActorId actorId)
			:
				nxBaseEventData(),
				m_ActorId(actorId)
		{
			m_EventType = NX_EVENT_FireWeapon;
		}

		nxFireWeaponEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_FireWeapon;
			in >> m_ActorId;
		}

		virtual ~nxFireWeaponEventData()
		{
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << m_ActorId << " ";
		}

		nxActorId GetActorId() const
		{
			return m_ActorId;
		}

	protected:
		nxActorId m_ActorId;

	private:
};

#endif   // NXFIREWEAPONEVENTDATA_H
