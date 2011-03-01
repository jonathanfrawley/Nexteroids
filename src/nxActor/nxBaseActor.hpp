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
#ifndef  NXBASEACTOR_H
#define  NXBASEACTOR_H

#include <Box2D/Box2D.h>

#include <nxCore/nxCore.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxActor/nxIActor.hpp>
#include <nxGeom/nxPoint3.hpp>

/*
 * =====================================================================================
 *        Class: nxBaseActor
 *  Description: Base class which all actors inherit from.
 * =====================================================================================
 */
class nxBaseActor : public nxIActor
{
	public:

		nxBaseActor(nxActorType type)
			:
				m_Type(type)
		{
		}

		nxBaseActor(nxReal yrot, nxPoint3 pos, nxActorType type)
			:
				m_Orientation(yrot),
				m_Type(type)
		{
			m_Pos = pos;
		}

		nxBaseActor(const nxBaseActor& other)
			:
				m_Orientation(other.VGetOrientation()),
				m_Type(other.VGetType())
		{
			m_Pos = other.VGetPos();
			m_Id = other.VGetId();
			m_ViewId = other.VGetViewId();
		}

		virtual ~nxBaseActor()
		{
		}


		virtual void VInit(stringstream& in)
		{
			//Type has already been decided.
			in >> m_Orientation;
			in >> m_Id;
			in >> m_ViewId;
			m_Pos.VInit(in);
		}

		virtual void VSerialize(stringstream& out)
		{
			int typeInt = (int)m_Type;
			out << typeInt << " ";
			out << m_Orientation << " ";
			out << m_Id << " ";
			out << m_ViewId << " ";
			m_Pos.VSerialize(out);
		}

		virtual void VOnUpdate(int deltaMilliseconds)
		{
		}

		virtual void VRotate(nxReal angleRadians)
		{
			m_Orientation += angleRadians;
		}

		virtual void VSetOrientation(float val)
		{
			m_Orientation = val;
		}

		virtual void VSetPos(nxPoint3 val)
		{
			m_Pos = val;
		}

		virtual void VSetPos(b2Vec2 val)
		{
			m_Pos.SetX(val.x);
			m_Pos.SetY(val.y);
		}

		virtual void VSetViewId(nxGameViewId val)
		{
			m_ViewId = val;
		}

		virtual void VSetId(nxActorId id)
		{
			m_Id = id;
		}

		virtual nxActorType VGetType() const
		{
			return m_Type;
		}

		//Up to subclasses to define what speed is
		virtual float VGetSpeed() const
		{
			return 0;
		}

		virtual nxReal VGetOrientation() const
		{
			return m_Orientation;
		}

		virtual nxActorId VGetId() const
		{
			return m_Id;
		}

		virtual nxGameViewId VGetViewId() const
		{
			return m_ViewId;
		}

		virtual nxPoint3 VGetPos() const
		{
			return m_Pos;
		}

		//Static method called to create an actor from a stream.
		static nxIActor* CreateFromStream(stringstream &in);

	protected:
		nxActorType m_Type;
		nxReal m_Orientation;
		nxPoint3 m_Pos;
		nxActorId m_Id;
		nxGameViewId m_ViewId;

	private:
};

#endif   // NXBASEACTOR_H
