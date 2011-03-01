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
#ifndef  NXREQUESTNEWACTOREVENTDATA_H
#define  NXREQUESTNEWACTOREVENTDATA_H

#include <nxCore/nxCore.hpp>
#include <nxEvent/nxBaseEventData.hpp>
#include <nxActor/nxIActor.hpp>

/*
 * =====================================================================================
 *        Class: nxRequestNewActorEventData
 *  Description: Request the creation of a new actor.
 * =====================================================================================
 */
class nxRequestNewActorEventData : public nxBaseEventData
{
	public:
		nxRequestNewActorEventData(shared_ptr<nxIActor> actor)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_RequestNewActor;
			m_Actor = actor->VClone();
		}

		virtual ~nxRequestNewActorEventData()
		{
		}

		nxIActor* GetActor() const
		{
			return m_Actor;
		}

	protected:
		nxIActor* m_Actor;

	private:
};

#endif
