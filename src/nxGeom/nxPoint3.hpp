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
#ifndef  NXPOINT3_H
#define  NXPOINT3_H

#include <sstream>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxPoint3
 *  Description: Simple 3D nxPoint Class.
 * =====================================================================================
 */
class nxPoint3
{
	public:
		nxPoint3();

		nxPoint3(float x, float y, float z);

		nxPoint3(const nxPoint3& other)
		{
			m_X = other.GetX();
			m_Y = other.GetY();
			m_Z = other.GetZ();
		}

		nxPoint3& operator=( const nxPoint3& rhs ) {
			m_X = rhs.GetX();
			m_Y = rhs.GetY();
			m_Z = rhs.GetZ();
			return *this;
		}

		~nxPoint3();

		void VInit(stringstream& in)
		{
			float x,y,z;
			in >> x;
			in >> y;
			in >> z;
			m_X = x;
			m_Y = y;
			m_Z = z;
		}

		void VSerialize(stringstream& out) const
		{
			float x,y,z;
			x = m_X;
			y = m_Y;
			z = m_Z;
			out << x << " ";
			out << y << " ";
			out << z << " ";
		}

		void SetX(float x)
		{
			m_X = x;
		}

		void SetY(float y)
		{
			m_Y = y;
		}

		void SetZ(float z)
		{
			m_Z = z;
		}

		float GetX () const
		{
			return m_X;
		}

		float GetY () const
		{
			return m_Y;
		}

		float GetZ () const
		{
			return m_Z;
		}

		nxPoint3 Add(const nxPoint3& other)
		{
			nxPoint3 temp;	
			temp.SetX(m_X + other.GetX());
			temp.SetY(m_Y + other.GetY());
			temp.SetZ(m_Z + other.GetZ());
			return temp;
		}

		nxPoint3 Subtract(const nxPoint3& other)
		{
			nxPoint3 temp;	
			temp.SetX(m_X - other.GetX());
			temp.SetY(m_Y - other.GetY());
			temp.SetZ(m_Z - other.GetZ());
			return temp;
		}

		nxPoint3 Multiply(const nxPoint3& other)
		{
			nxPoint3 temp;	
			temp.SetX(m_X * other.GetX());
			temp.SetY(m_Y * other.GetY());
			temp.SetZ(m_Z * other.GetZ());
			return temp;
		}

		nxPoint3 Multiply(float val)
		{
			nxPoint3 temp;	
			temp.SetX(m_X * val);
			temp.SetY(m_Y * val);
			temp.SetZ(m_Z * val);
			return temp;
		}

		nxPoint3 Divide(float val)
		{
			nxPoint3 temp;	
			temp.SetX(m_X / val);
			temp.SetY(m_Y / val);
			temp.SetZ(m_Z / val);
			return temp;
		}

		bool equals(nxPoint3 other)
		{
			if( m_X == other.GetX() &&
					m_Y == other.GetY() &&
					m_Z == other.GetZ())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	protected:
		float m_X;
		float m_Y;
		float m_Z;

	private:
};


#endif   // NXPOINT3_H
