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
#ifndef  NXTHRUSTEVENTDATA_H
#define  NXTHRUSTEVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxThrustEventData
 *  Description: Add to target's linear velocity.
 * =====================================================================================
 */
class nxThrustEventData : public nxBaseEventData
{
	public:
		nxThrustEventData();

		nxThrustEventData(nxActorId actorId, float thrustAmount)
			:
				nxBaseEventData(),
				m_ActorId(actorId),
				m_ThrustAmount(thrustAmount)
		{
			m_EventType = NX_EVENT_Thrust;
		}

		virtual ~nxThrustEventData()
		{
		}

		nxThrustEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_Thrust;
			in >> m_ActorId;
			in >> m_ThrustAmount;
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << m_ActorId << " ";
			out << m_ThrustAmount << " ";
		}

		nxActorId GetActorId() const
		{
			return m_ActorId;
		}

		float GetThrustAmount() const
		{
			return m_ThrustAmount;
		}
		
	protected:
		nxActorId m_ActorId;
		float m_ThrustAmount;

	private:
};



#endif   // NXTHRUSTEVENTDATA_H
