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
#ifndef  NXIPACKET_H
#define  NXIPACKET_H

#include <inttypes.h>

#include <nxCore/nxCore.hpp>

/*
 * =====================================================================================
 *        Class: nxIPacket
 *  Description: Interface for all packets to implement.
 * =====================================================================================
 */
class nxIPacket
{
	public:
		virtual ~nxIPacket()
		{
		}

		virtual char const * VGetType() const = 0;

		virtual char const * VGetData() const = 0;

		virtual uint32_t VGetSize() const = 0;
		
	protected:
	private:
};

typedef shared_ptr<nxIPacket> nxPacketPtr;

#endif   // NXIPACKET_H
