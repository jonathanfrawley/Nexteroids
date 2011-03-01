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
#ifndef  NXSPACESHIPACTOR_H
#define  NXSPACESHIPACTOR_H

#include <nxCore/nxCore.hpp>
#include <nxCore/nxMath.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxActor/nxBaseActor.hpp>
#include <nxGeom/nxPoint3.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>

/*
 * =====================================================================================
 *        Class: nxSpaceshipActor
 *  Description: Actor to represent Spaceships.
 * =====================================================================================
 */
class nxSpaceshipActor : public nxBaseActor
{
	public:

		nxSpaceshipActor();

		nxSpaceshipActor(nxReal yrot, nxPoint3 pos);

		virtual ~nxSpaceshipActor();

		virtual void VInit(stringstream& in)
		{
			nxBaseActor::VInit(in);
			in >> m_Radius;
			in >> m_Colour.r;
			in >> m_Colour.g;
			in >> m_Colour.b;
			in >> m_Colour.alpha;
		}

		virtual void VSerialize(stringstream& out)
		{
			nxBaseActor::VSerialize(out);
			out << m_Radius << " ";
			out << m_Colour.r << " ";
			out << m_Colour.g << " ";
			out << m_Colour.b << " ";
			out << m_Colour.alpha << " ";
		}

		virtual nxSpaceshipActor* VClone()
		{
			nxSpaceshipActor* result = new nxSpaceshipActor(m_Orientation, m_Pos);
			result->VSetRadius(m_Radius);
			result->VSetColour(m_Colour);
			result->VSetViewId(m_ViewId);
			result->VSetId(m_Id);
			return result;
		}

		virtual void VOnUpdate(int deltaMilliseconds)
		{
		}

		virtual void VCreate() 
		{
		}

		virtual nxReal GetRadius() const
		{
			return m_Radius;
		}

		virtual void VSetRadius(float val)
		{
			m_Radius = val;
		}

		virtual void VSetColour(nxColour colour)
		{
			m_Colour = colour;
		}

		virtual nxColour VGetColour() const
		{
			return m_Colour;
		}
		
	protected:
		nxReal m_Radius;
		nxColour m_Colour;
	private:
};

#endif   // NXSPACESHIPACTOR_H
