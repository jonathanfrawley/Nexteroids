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
#ifndef  NXEVENTMANAGER_H
#define  NXEVENTMANAGER_H

#include <vector>
#include <set>

#include <nxCore/nxCore.hpp>
#include <nxEvent/nxIEventManager.hpp>
#include <nxEvent/nxEventType.hpp>
#include <nxEvent/nxIEventData.hpp>
#include <jfTimer/jfFPSTimer.hpp>

//Typedefs so that things don't get messy.
typedef std::set< nxEventType > nxEventTypeSet;

//typedef std::map< nxEventType, nxIRegisteredEventPtr > nxRegisteredEventTypeMap;
typedef std::pair< nxEventTypeSet::iterator, bool >	nxEventTypeMapInsertRes;
typedef std::list< nxEventListenerPtr > nxEventListenerTable;

typedef std::map< unsigned int, nxEventListenerTable > nxEventListenerMap;
typedef std::pair< unsigned int, nxEventListenerTable >	nxEventListenerMapEnt;
typedef std::pair< nxEventListenerMap::iterator, bool >	nxEventListenerMapInsertRes;

typedef std::vector<nxEventListenerPtr> nxEventListenerList;
typedef std::vector<nxEventType> nxEventTypeList;
typedef std::pair< nxEventListenerMap::iterator, bool >	nxEventListenerMapInsertRes;

typedef std::list< nxIEventDataPtr > nxEventDataTable;

typedef boost::shared_ptr<nxIEventData> nxEventPtr;
typedef std::list< nxEventPtr > nxEventQueue;

/*
 * =====================================================================================
 *        Class: nxEventManager
 *  Description: Singleton object, queues and dispatches events to all registered listeners.
 * =====================================================================================
 */
class nxEventManager : public nxIEventManager
{
	public:

		static nxEventManager& GetInstance();

		enum nxEventManagerConstants
		{
			NX_EVENT_MANAGER_K_NQUEUES = 2,
			NX_EVENT_MANAGER_GLOBAL_LISTENER_IDX = 0
		};

		bool IsListenerInTable(nxEventListenerPtr listener, nxEventListenerTable& listenerTable);

		nxEventListenerMap::iterator FindAndAddListenerMapEntry(nxEventListenerMap::iterator listenerMapEntry, nxEventType eventType);

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VAddListener
         *  Description:  Add registration to event type for listener
         * =====================================================================================
         */
		virtual bool VAddListener ( nxEventListenerPtr const & inHandler,
				nxEventType const & inType );

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VDelListener
         *  Description:  Remove registration to event type for listener
         * =====================================================================================
         */
		virtual bool VDelListener ( nxEventListenerPtr const & inHandler,
				nxEventType const & inType );

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VTrigger
         *  Description:  Dispatch event to all registered events.
         * =====================================================================================
         */
		virtual bool VTrigger ( nxIEventData const & inEvent ) const;

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VQueueEvent
         *  Description:  Queue event and dispatch event on next tick.
         * =====================================================================================
         */
		virtual bool VQueueEvent ( nxIEventDataPtr const & inEvent );

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VAbortEvent
         *  Description:  Abort first event of given type, or all of them if the option is set.
         * =====================================================================================
         */
		virtual bool VAbortEvent ( nxEventType const & inType,
				bool allOfType = false );

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  VTick
         *  Description:  Dispatch events which were queued for a length of time.
         * TODO:Implement time limit.
         * =====================================================================================
         */
		virtual bool VTick ( unsigned long maxMillis = NX_IEVENT_MANAGER_K_INFINITE);

		virtual bool VValidateType( nxEventType const & inType ) const;

        /*
         * ===  FUNCTION  ======================================================================
         *         Name:  GetListenerList
         *  Description:  Get the list of listeners associated with a specific event type
         * =====================================================================================
         */
		nxEventListenerList GetListenerList (
                nxEventType const & eventType ) const;

	protected:

		static nxEventManager m_Instance;

		nxEventManager();

		virtual ~nxEventManager();

		nxEventTypeSet m_EventTypes;

		nxEventListenerMap m_ListenerRegistry;

		nxEventQueue m_EventQueues[NX_EVENT_MANAGER_K_NQUEUES];

		int m_ActiveQueue;

	private:
};


#endif   // NXEVENTMANAGER_H
