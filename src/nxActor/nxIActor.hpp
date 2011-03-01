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

#include <sstream>

#include <Box2D/Box2D.h>

#include <nxCore/nxCore.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxGeom/nxPoint3.hpp>
#include <nxGameView/nxGameViewTypes.hpp>

using namespace std;

class nxBaseGameLogic;

/*
 * =====================================================================================
 *        Class: nxIActor
 *  Description: Interface for all actors to implement.
 * =====================================================================================
 */
class nxIActor
{
	public:
		virtual ~nxIActor()
		{
		}

		virtual void VInit(stringstream& in) = 0;

		virtual void VSerialize(stringstream& out) = 0;

		virtual nxIActor* VClone() = 0;

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  VOnUpdate
		 *  Description:  Updates the logic of this actor such as integrating its velocity.
		 * =====================================================================================
		 */
		virtual void VOnUpdate(int deltaMilliseconds) = 0;

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  VRotateY
		 *  Description:  Rotates this actor about the y axis
		 * =====================================================================================
		 */
		virtual void VRotate(nxReal angleRadians) = 0;

		virtual void VSetOrientation(float val) = 0;

		virtual void VSetPos(nxPoint3 val) = 0;

		virtual void VSetPos(b2Vec2 val) = 0;

//		virtual void VSetBody(b2Body* body) = 0;
		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  VSetId
		 *  Description:  Sets the unique id for this actor.
		 * =====================================================================================
		 */
		virtual void VSetId(nxActorId id) = 0;

		virtual void VSetViewId(nxGameViewId val) = 0;

		virtual void VCreate() = 0;

		virtual nxReal VGetOrientation() const = 0;

		virtual nxPoint3 VGetPos() const = 0;

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  VGetId
		 *  Description:  Id will be a unique id for this actor across clients.
		 * =====================================================================================
		 */
		virtual nxActorId VGetId() const = 0;

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  VGetType
		 *  Description:  Types defined in nxTypes.hpp
		 * =====================================================================================
		 */
		virtual nxActorType VGetType() const = 0;

		virtual nxGameViewId VGetViewId() const = 0;

		virtual void VSetRadius(float val) = 0;

		virtual nxReal GetRadius() const = 0;

		virtual nxColour VGetColour() const = 0;

		virtual float VGetSpeed() const = 0;
		
	protected:

	private:
};


#endif   // NXIACTOR_H
