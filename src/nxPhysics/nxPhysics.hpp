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
#ifndef  NXPHYSICS_H
#define  NXPHYSICS_H

#include <vector>

#include <Box2D/Box2D.h>

#include <nxPhysics/nxIPhysics.hpp>
#include <nxCore/nxCore.hpp>
#include <nxActor/nxRockActor.hpp>
/*
 * =====================================================================================
 *        Class: nxPhysics
 *  Description: Implements the physics world for the game using Box2D as the physics 
 *  engine.
 * =====================================================================================
 */
class nxPhysics : public nxIPhysics, public b2ContactListener
{
	public:
		nxPhysics();

		virtual ~nxPhysics();

		virtual void VInit();


		virtual void VCreateActor(shared_ptr<nxIActor> actor);

		virtual void VOnUpdate(float timestep);

		virtual void VRenderDiagnostics() 
		{ 
		}

		virtual void VRemoveActor(nxActorId aid)
		{
			vector<b2Body*>::iterator it, itEnd;
			for(it = m_Bodies.begin(), itEnd = m_Bodies.end() ; it != itEnd ; it++)
			{
				b2Body* body = (*it);
				nxIActor* actor = (nxIActor*)(body->GetUserData());
				if(actor->VGetId() == aid)
				{
					m_Bodies.erase(it);
					m_World->DestroyBody(body);
				}
			}
		}

		virtual void VApplyThrottle(nxActorId actorId, float throttle);

		virtual void VApplySteering(nxActorId actorId, float steering);

		vector<b2Vec2> ConvertPointToVec2(vector<nxPoint3> points);

		//Contact Listener stuff.
		virtual void BeginContact(b2Contact* contact);
		
	protected:
		b2World* m_World;
		std::vector<b2Body*> m_Bodies;

	private:
};


#endif   // NXPHYSICS_H
