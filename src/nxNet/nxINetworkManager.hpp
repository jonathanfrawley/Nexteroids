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
#ifndef  NXINETWORKMANAGER_H
#define  NXINETWORKMANAGER_H

#include <nxNet/nxIPacket.hpp>

const int NX_MAX_PACKET_SIZE = 255;

/*
 * =====================================================================================
 *        Class: nxINetworkManager
 *  Description: Interface for all network managers to implement.
 * =====================================================================================
 */
class nxINetworkManager
{
	public:
		virtual ~nxINetworkManager(){ ; }

		virtual bool Init() = 0;

		virtual void VTick() = 0;

		virtual void SendToAllSubscribers(nxPacketPtr packet) = 0;
		
	protected:
	private:
};

#endif   // NXINETWORKMANAGER_H
