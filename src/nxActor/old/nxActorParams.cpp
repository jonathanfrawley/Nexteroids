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
#include "nxActorParams.hpp"


nxActorParams::nxActorParams() 
{
	m_Pos = jfVector3_x86(0,0,0); 
	m_Type = NX_ACTOR_UNKOWN; 
	m_Colour.alpha = 0.0f;
    m_Colour.r = 0.0f;
    m_Colour.g = 0.0f;
    m_Colour.b = 0.0f;
	m_Size=sizeof(nxActorParams); 
}

bool nxActorParams::VInit(std::istrstream &in)
{ 
	int hasActorId = 0;
	float x,y,z;

	in >> m_Size;
	in >> m_Id

//	in >> hasActorId;
//	if (hasActorId)
//	{
//		in >> hasActorId;
//		m_Id = hasActorId;
//	}
	in >> x >> y >> z;
	m_Pos.setX(x);
	m_Pos.setY(y);
	m_Pos.setZ(z);
//	in >> m_Colour.r >> m_Colour.g >> m_Colour.b >> m_Colour.alpha;
	return true;
}

void nxActorParams::VSerialize(std::ostrstream &out) const
{
    //TODO
	out << m_Type << " ";
	out << m_Size << " ";
//	out << static_cast<int>(m_Id.valid()) << " ";
//	if (m_Id.valid())
//	{
//		out << *m_Id << " ";
//	}
	out << *m_Id << " ";
	out << m_Pos.getX() << " " << m_Pos.getY() << " " << m_Pos.getZ() << " ";
//	out << m_Colour.r << " " << m_Colour.g << " " << m_Colour.b << " " << m_Colour.alpha << " ";
}

