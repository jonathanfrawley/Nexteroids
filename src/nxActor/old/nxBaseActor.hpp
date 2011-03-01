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

#include <jfpx/x86/jfMatrix4_x86.h>

#include <nxCore/nxTypes.hpp>
#include <nxActor/nxIActor.hpp>
//#include <nxActor/nxActorParams.hpp>

class nxBaseActor : public nxIActor
{
	public:
		/*
		nxBaseActor(jfMatrix4_x86 mat, int type, shared_ptr<nxActorParams> params)
        { m_Mat=mat; m_Type=type; m_Params=params; }
		*/

		nxBaseActor(float rot, int type, shared_ptr<nxActorParams> params)
        { m_Rot=rot; m_Type=type; m_Params=params; }

//		virtual void VSetMat(const jfMatrix4_x86 &newMat) { m_Mat = newMat; }
//		virtual jfMatrix4_x86 const &VGetMat() { return m_Mat; }

		virtual const int VGetType() { return m_Type; }	

		virtual nxActorId VGetID() { return m_id; }

		virtual nxActorParams* VGetParams() { return m_Params; }

		virtual bool VIsPhysical() { return true; }

		virtual bool VIsGeometrical() { return true; }

		virtual void VOnUpdate(int deltaMilliseconds) { }

		virtual void VRotateY(float angleRadians)
		{
			m_Rot += angleRadians;
		}

		virtual void VSetID(nxActorId id) { m_id = id; } 


	protected:
		nxActorId m_id;
//		jfMatrix4_x86 m_Mat;
		float m_Rot;
		int m_Type;
		shared_ptr<nxActorParams> m_Params;
};

#endif   // NXBASEACTOR_H
