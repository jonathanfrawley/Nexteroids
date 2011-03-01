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
#include "nxSpaceshipParams.hpp"


nxSpaceshipParams::nxSpaceshipParams()
	:
		nxActorParams()
{
}

nxSpaceshipParams::~nxSpaceshipParams()
{
}

shared_ptr<nxIActor> VCreate(nxBaseGameLogic *logic)
{
	//	Mat4x4 mat;
//	mat.BuildTranslation(m_Pos);
//	shared_ptr<IActor> pSphere(new BaseActor(mat, AT_Sphere, shared_ptr<SphereParams>(GCC_NEW SphereParams(*this))));
//	logic->VAddActor(pSphere, this);
//	logic->VGetGamePhysics()->VAddSphere(m_Radius, &*pSphere, SpecificGravity(PhysDens_Pine), PhysMat_Bouncy);
//	logic->VGetGamePhysics()->VApplyForce(m_NormalDir, m_Force, *( m_Id ));
//	return pSphere;

//	jfMatrix4 mat;
//	mat.BuildTranslatrion(m_Pos);
//	shared_ptr<nxIActor> pActor(NX_NEW nxBaseActor(mat, NX_ACTOR_SHIP, shared_ptr<nxSpaceshipParams>(NX_NEW nxSpaceshipParams(*this))));;

	m_Rot = 0.0f; //XXX:Magic Number, should be random?
	m_Radius = 3.0f; //XXX : Magic number

	shared_ptr<nxIActor> pActor(NX_NEW nxBaseActor(rot, NX_ACTOR_SHIP, shared_ptr<nxSpaceshipParams>(NX_NEW nxSpaceshipParams(*this))));;
	logic->VAddActor(pActor, this);
	//TODO:Add physics
	logic->VGetGamePhysics()->VAddSphere(m_Radius, m_Pos, m_Rot);
	
	return pActor;
}

bool VInit(std::istrstream &in)
{
	nxActorParams::VInit(in);
}

void VSerialize(std::ostrstream &out) const
{
	nxActorParams::VSerialize(out);
}

