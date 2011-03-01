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
#ifndef  NXIPHYSICS_H
#define  NXIPHYSICS_H

#include <nxActor/nxIActor.hpp>
#include <nxCore/nxCore.hpp>

/*
 * =====================================================================================
 *        Class: nxIPhysics
 *  Description: Interface for physics world.
 * =====================================================================================
 */
class nxIPhysics
{
	public:
		virtual ~nxIPhysics() { }

		virtual void VInit() = 0;

		virtual void VOnUpdate(float timestep) = 0;

		virtual void VRenderDiagnostics() = 0;

		virtual void VCreateActor(shared_ptr<nxIActor> actor) = 0;

		virtual void VRemoveActor(nxActorId) = 0;

		virtual void VApplyThrottle(nxActorId actorId, float throttle) = 0;

		virtual void VApplySteering(nxActorId actorId, float steering) = 0;

	protected:
	private:
};


#endif   // NXIPHYSICS_H
