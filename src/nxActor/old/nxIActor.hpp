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

#ifndef  NXIACTOR_H
#define  NXIACTOR_H

#include <jfpx/x86/jfMatrix4_x86.h>

//#include <nxActor/nxActorParams.hpp>
#include <nxCore/nxCore.hpp>
#include <nxCore/nxTypes.hpp>

//typedef boost::shared_ptr<nxActorParams> nxActorParamsPtr;

class nxIActor
{
	public:
		virtual ~nxIActor() { }

//		virtual jfMatrix4_x86 const &VGetMat()=0;
//		virtual void VSetMat(const jfMatrix4_x86 &newMat)=0;

		virtual const int VGetType()=0;

		virtual nxActorId VGetID()=0; 

//		virtual nxActorParamsPtr VGetParams()=0;
//		virtual nxActorParams* VGetParams()=0;

		virtual bool VIsPhysical()=0;

		virtual bool VIsGeometrical()=0;

		virtual void VOnUpdate(int deltaMilliseconds)=0;

		virtual void VRotateY(nxReal angleRadians) = 0;

		virtual void VSetID(nxActorId id)=0;
};

#endif   // NXIACTOR_H
