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
#ifndef  NXREMOTECLIENTEVENTDATA_H
#define  NXREMOTECLIENTEVENTDATA_H

#include <sstream>

#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxRemoteClientEventData
 *  Description: Remote client joined.
 * =====================================================================================
 */
class nxRemoteClientEventData : public nxBaseEventData
{
	public:
		nxRemoteClientEventData(unsigned ipInt)
			:
				nxBaseEventData(),
				m_IpInt(ipInt)
		{
			m_EventType = NX_EVENT_RemoteClient;
		}

		nxRemoteClientEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_RemoteClient;
			in >> m_IpInt;
		}

		virtual ~nxRemoteClientEventData()
		{
		}

		unsigned GetIpInt() const
		{
			return m_IpInt;
		}

		//Serializing for network out.
		virtual void VSerialize(stringstream &out) const
		{
			out << m_IpInt << " ";
		}

	protected:
		unsigned m_IpInt;

	private:
};


#endif   // NXREMOTECLIENTEVENTDATA_H
