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
#ifndef  NXSTEEREVENTDATA_H
#define  NXSTEEREVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxSteerEventData
 *  Description: Change angular velocity of target.
 * =====================================================================================
 */
class nxSteerEventData : public nxBaseEventData
{
	public:
		nxSteerEventData();

		nxSteerEventData(nxActorId actorId, float steerAmount)
			:
				nxBaseEventData(),
				m_ActorId(actorId),
				m_SteerAmount(steerAmount)
		{
			m_EventType = NX_EVENT_Steer;
		}

		virtual ~nxSteerEventData()
		{
		}

		nxSteerEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_Steer;

			in >> m_ActorId;
			in >> m_SteerAmount;
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << m_ActorId << " ";
			out << m_SteerAmount << " ";
		}

		nxActorId GetActorId() const
		{
			return m_ActorId;
		}

		float GetSteerAmount() const
		{
			return m_SteerAmount;
		}
		
	protected:
		nxActorId m_ActorId;
		float m_SteerAmount;

	private:
};

#endif   // NXSTEEREVENTDATA_H
