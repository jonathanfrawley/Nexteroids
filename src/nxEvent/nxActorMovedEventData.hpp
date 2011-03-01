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
#ifndef  NXACTORMOVEDEVENTDATA_H
#define  NXACTORMOVEDEVENTDATA_H

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxActorMovedEventData
 *  Description: Represents an actor moving to a new position with new orientation.
 * =====================================================================================
 */
class nxActorMovedEventData : public nxBaseEventData
{
	public:
		nxActorMovedEventData(nxActorId aid, nxPoint3 pos, nxReal orientation)
			:
				nxBaseEventData(),
				m_Aid(aid),
				m_Pos(pos),
				m_Orientation(orientation)
		{
			m_EventType = NX_EVENT_ActorMoved;
		}

		virtual ~nxActorMovedEventData()
		{
		}

		nxActorMovedEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_ActorMoved;
			in >> m_Aid;
			m_Pos.VInit(in);
			in >> m_Orientation;
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << m_Aid << " ";
			m_Pos.VSerialize(out);
			out << m_Orientation << " ";
		}

		nxReal GetOrientation() const
		{
			return m_Orientation;
		}

		nxActorId GetActorId() const
		{
			return m_Aid;
		}

		nxPoint3 GetPos() const
		{
			return m_Pos;
		}

	protected:
		nxActorId m_Aid;
		nxPoint3 m_Pos;
		nxReal m_Orientation;

	private:
};

#endif   // NXACTORMOVEDEVENTDATA_H
