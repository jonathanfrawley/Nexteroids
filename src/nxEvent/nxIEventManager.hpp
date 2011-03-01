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
#ifndef  NXIEVENTMANAGER_H
#define  NXIEVENTMANAGER_H

#include <map>
#include <utility>
#include <list>

using namespace std;

#include <nxCore/nxCore.hpp>
#include <nxEvent/nxEventType.hpp>
#include <nxEvent/nxIEventListener.hpp>
#include <nxEvent/nxIEventData.hpp>

typedef boost::shared_ptr<nxIEventData> nxIEventDataPtr;
typedef boost::shared_ptr<nxIEventListener> nxEventListenerPtr;

/*
 * =====================================================================================
 *        Class: nxIEventManager
 *  Description: Interface for EventManager.
 * =====================================================================================
 */
class nxIEventManager
{
	public:
		enum nxIEventManagerConstants
		{
			NX_IEVENT_MANAGER_K_INFINITE = 0xffffffff
		};

		virtual bool VAddListener ( nxEventListenerPtr const & inHandler,
									nxEventType const & inType ) = 0;

		virtual bool VDelListener ( nxEventListenerPtr const & inHandler,
									nxEventType const & inType ) = 0;

		virtual bool VTrigger ( nxIEventData const & inEvent ) const = 0;

		virtual bool VQueueEvent ( nxIEventDataPtr const & inEvent ) = 0;

		virtual bool VAbortEvent ( nxEventType const & inType,
									bool allOfType = false ) = 0;

		virtual bool VTick ( unsigned long maxMillis = NX_IEVENT_MANAGER_K_INFINITE ) = 0;

		virtual bool VValidateType( nxEventType const & inType ) const = 0;

	protected:

		nxIEventManager();

		virtual ~nxIEventManager();

	private:
};

#endif   // NXIEVENTMANAGER_H
