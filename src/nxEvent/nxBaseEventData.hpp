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
#ifndef  NXBASEEVENTDATA_H
#define  NXBASEEVENTDATA_H

#include <strstream>

#include <nxEvent/nxIEventData.hpp>
#include <nxEvent/nxEventType.hpp>

/*
 * =====================================================================================
 *        Class: nxBaseEventData
 *  Description: Base class which all events inherit from.
 * =====================================================================================
 */
class nxBaseEventData : public nxIEventData
{
	public:
		nxBaseEventData()
		{
			m_EventType = NX_EVENT_Null;
		}

		virtual ~nxBaseEventData()
		{
		}

		virtual nxEventType VGetEventType() const
		{
			return m_EventType;
		}

		//Serializing for network out.
		virtual void VSerialize(stringstream &out) const
		{
		};
		
	protected:
		nxEventType m_EventType;
	private:
};


#endif   // NXBASEEVENTDATA_H
