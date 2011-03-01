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
#ifndef  NXBINARYPACKET_H
#define  NXBINARYPACKET_H

#include <string.h>

#include <netinet/in.h>

#include <nxCore/nxCore.hpp>
#include <nxNet/nxIPacket.hpp>

/*
 * =====================================================================================
 *        Class: nxBinaryPacket
 *  Description: Represents binary packets.
 * =====================================================================================
 */
class nxBinaryPacket : public nxIPacket
{
	public:
		nxBinaryPacket(char const * data, uint32_t size);

		nxBinaryPacket(uint32_t size);

		virtual ~nxBinaryPacket();

		virtual char const * VGetType() const
		{
			return m_Type;
		}

		virtual char const * VGetData() const
		{
			return m_Data;
		}

		virtual uint32_t VGetSize() const
		{
			return ntohl(*(uint32_t*)m_Data);
		}
		
	protected:
		const char* m_Type;
		char* m_Data;
	private:
};

#endif   // NXBINARYPACKET_H
