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

#ifndef  NXNETWORKEVENTFORWARDER_H
#define  NXNETWORKEVENTFORWARDER_H

#include <sstream>

#include <nxCore/nxCore.hpp>
#include <nxEvent/nxIEventData.hpp>
#include <nxEvent/nxIEventListener.hpp>
#include <nxNet/nxBinaryPacket.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxNetworkEventForwarder
 *  Description:
 * =====================================================================================
 */
class nxNetworkEventForwarder : public nxIEventListener
{
	public:
		nxNetworkEventForwarder();

		virtual ~nxNetworkEventForwarder();

		virtual char const * GetName(void)
		{
			return "nxNetworkEventForwarder";
		}

		virtual bool HandleEvent( nxIEventData const & event );
		
	protected:
	private:
};


#endif   // NXNETWORKEVENTFORWARDER_H
