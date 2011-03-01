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
#ifndef  NXBULLETACTOR_H
#define  NXBULLETACTOR_H

#include <nxCore/nxCore.hpp>
#include <nxCore/nxMath.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxActor/nxBaseActor.hpp>
#include <nxGeom/nxPoint3.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>

/*
 * =====================================================================================
 *        Class: nxBulletActor
 *  Description: Actor to represent Bullets in the game.
 * =====================================================================================
 */
class nxBulletActor : public nxBaseActor
{
	public:

		nxBulletActor();

		nxBulletActor(nxReal yrot, nxPoint3 pos, float radius, float speed);

		virtual ~nxBulletActor();

		virtual nxBulletActor* VClone()
		{
			nxBulletActor* result = new nxBulletActor(m_Orientation, m_Pos, m_Radius, m_Speed);
			result->VSetColour(m_Colour);
			result->VSetViewId(m_ViewId);
			result->VSetId(m_Id);
			return result;
		}

		virtual void VInit(stringstream& in)
		{
			nxBaseActor::VInit(in);
			in >> m_Radius;
			in >> m_Colour.r;
			in >> m_Colour.g;
			in >> m_Colour.b;
			in >> m_Colour.alpha;
			in >> m_Speed;
		}

		virtual void VSerialize(stringstream& out)
		{
			nxBaseActor::VSerialize(out);
			out << m_Radius << " ";
			out << m_Colour.r << " ";
			out << m_Colour.g << " ";
			out << m_Colour.b << " ";
			out << m_Colour.alpha << " ";
			out << m_Speed << " ";
		}

		virtual void VOnUpdate(int deltaMilliseconds)
		{
		}

		virtual void VCreate() 
		{
		}

		virtual void VSetRadius(float val)
		{
			m_Radius = val;
		}

		virtual nxReal GetRadius() const
		{
			return m_Radius;
		}

		virtual void VSetColour(nxColour colour)
		{
			m_Colour = colour;
		}

		virtual nxColour VGetColour() const
		{
			return m_Colour;
		}

		virtual float VGetSpeed() const
		{
			return m_Speed;
		}
		
	protected:
		nxReal m_Radius;
		nxColour m_Colour;
		float m_Speed;
	private:
};


#endif   // NXBULLETACTOR_H
