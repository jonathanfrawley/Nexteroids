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
#include "nxBinaryPacket.hpp"

nxBinaryPacket::nxBinaryPacket(char const * data, uint32_t size)
{
	m_Type = "Binary Packet";

	m_Data = NX_NEW char[size + sizeof(uint32_t)];
	assert(m_Data);
	*(uint32_t *)m_Data = htonl(size+sizeof(uint32_t));
	memcpy(m_Data+sizeof(uint32_t), data, size);
}

nxBinaryPacket::nxBinaryPacket(uint32_t size)
{
	m_Type = "Binary Packet";

	m_Data = NX_NEW char[size + sizeof(uint32_t)];
	assert(m_Data);
	*(uint32_t *)m_Data = htonl(size+sizeof(uint32_t));
}

nxBinaryPacket::~nxBinaryPacket()
{
	NX_SAFE_DELETE_ARRAY(m_Data);
}
