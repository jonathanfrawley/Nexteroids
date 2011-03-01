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

#ifndef  NXSPHERE_H
#define  NXSPHERE_H

/*
 * =====================================================================================
 *        Class: nxSphere
 *  Description:
 * =====================================================================================
 */
class nxSphere
{
	public:
		nxSphere()
		{
		}

		virtual ~nxSphere()
		{
		}

		jfVector3_x86 GetPos()
		{
			return m_Pos;
		}

		void SetPos(jfVector3_x86 pos)
		{
			m_Pos = pos;
		}

		void SetRot(float rot)
		{
			m_Rot = rot;
		}

		float GetRot()
		{
			return m_Rot;
		}

		void SetRadius(float radius)
		{
			m_Radius = radius;
		}

		float GetRadius()
		{
			return m_Radius;
		}
		
	protected:
		jfVector3_x86 m_Pos;
		float m_Rot;
		float m_Radius;
	private:
};

#endif   // NXSPHERE_H
