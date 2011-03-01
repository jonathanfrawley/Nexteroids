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
#include "nxEventManager.hpp"

nxEventManager nxEventManager::m_Instance;

nxEventManager::nxEventManager()
	:
		nxIEventManager(),
		m_ActiveQueue(0)
{
}

nxEventManager::~nxEventManager()
{
	m_ActiveQueue = 0;
}

nxEventManager& nxEventManager::GetInstance()
{
	return nxEventManager::m_Instance;
}

nxEventListenerMap::iterator nxEventManager::FindAndAddListenerMapEntry(nxEventListenerMap::iterator listenerMapEntry, nxEventType eventType)
{
	nxEventListenerMap::iterator listenerEntry = listenerMapEntry;
	//Add listener to registry if not found already
	if ( listenerEntry == m_ListenerRegistry.end() )
	{
		nxEventListenerMapInsertRes insertElem = m_ListenerRegistry.insert(
			nxEventListenerMapEnt( eventType,
								  nxEventListenerTable() ) );

		if ( insertElem.second == false )
		{
			assert(0);
		}

		if ( insertElem.first == m_ListenerRegistry.end() )
		{
			assert(0);
		}

		// store it so we can update the mapped list next ...
		listenerEntry = insertElem.first;
	}
	return listenerEntry;
}

bool nxEventManager::IsListenerInTable(nxEventListenerPtr listener, nxEventListenerTable& listenerTable)
{
	//Look for listener in event listener table for event type
	for ( nxEventListenerTable::iterator it2 = listenerTable.begin(),
			  it2End = listenerTable.end(); it2 != it2End ; it2++ )
	{
		bool bListenerMatch = ( *it2 == listener );

		if ( bListenerMatch )
		{
			return true;
		}
	}
	return false;
}


bool nxEventManager::VAddListener ( nxEventListenerPtr const & inListener,
		nxEventType const & inType )
{
	if ( ! VValidateType( inType ) )
	{
		return false;
	}

	nxEventListenerMap::iterator listenerMapEntry = m_ListenerRegistry.find( inType );
	listenerMapEntry = FindAndAddListenerMapEntry(listenerMapEntry, inType);

	// note: use reference to make following code more simple
	nxEventListenerTable & listenerTable = (*listenerMapEntry).second;

	if( IsListenerInTable(inListener, listenerTable) )
	{
		return false;
	}
	else
	{
		listenerTable.push_back( inListener );
		return true;
	}
}

bool nxEventManager::VDelListener (
	nxEventListenerPtr const & inListener, nxEventType const & inType )
{
	if ( ! VValidateType( inType ) )
	{
		return false;
	}

	bool rc = false;

	// brute force method, iterate through all existing mapping
	// entries looking for the matching listener and remove it.
	for ( nxEventListenerMap::iterator it = m_ListenerRegistry.begin(),
			  itEnd = m_ListenerRegistry.end(); it != itEnd; it++ )
	{
		nxEventListenerTable & table = it->second;

		for ( nxEventListenerTable::iterator it2 = table.begin(),
				  it2End = table.end(); it2 != it2End; it2++ )
		{
			if ( *it2 == inListener )
			{
				// found match, remove from table,
				table.erase( it2 );

				// update return code
				rc = true;

				// and early-quit the inner loop as addListener()
				// code ensures that each listener can only
				// appear in one event's processing list once.
				break;
			}
		}
	}

	return rc;
}

bool nxEventManager::VTrigger (
	nxIEventData const & inEvent ) const
{
	if ( ! VValidateType( inEvent.VGetEventType() ) )
	{
		return false;
	}

	//Iterate through listeners which listen to all events, such as a snooper.
	nxEventListenerMap::const_iterator itWC = m_ListenerRegistry.find( NX_EVENT_MANAGER_GLOBAL_LISTENER_IDX );

	if ( itWC != m_ListenerRegistry.end() )
	{
		nxEventListenerTable const & table = itWC->second;

		bool processed = false;

		for ( nxEventListenerTable::const_iterator it2 = table.begin(),
				  it2End = table.end(); it2 != it2End; it2++ )
		{
			(*it2)->HandleEvent( inEvent );
		}
	}

	//Now iterate through listeners which specifically register for certain events
	nxEventListenerMap::const_iterator it =
		m_ListenerRegistry.find( inEvent.VGetEventType() );

	if ( it == m_ListenerRegistry.end() )
	{
		return false;
	}

	nxEventListenerTable const & table = it->second;

	bool processed = false;

	for ( nxEventListenerTable::const_iterator it2 = table.begin(),
			  it2End = table.end(); it2 != it2End; it2++ )
	{
		nxEventListenerPtr listener = *it2;
		if ( listener->HandleEvent( inEvent ) )
		{
			// only set to true, if processing eats the messages
			processed = true;
		}
	}

	return processed;
}

bool nxEventManager::VQueueEvent ( nxIEventDataPtr const & inEvent )
{
	m_EventQueues[m_ActiveQueue].push_back( inEvent );
	return true;
}

bool nxEventManager::VAbortEvent ( nxEventType const & inType, bool
		allOfType )
{
	assert ( m_ActiveQueue >= 0 );
	assert ( m_ActiveQueue < NX_EVENT_MANAGER_K_NQUEUES );
	if ( ! VValidateType( inType ) )
	{
		return false;
	}
	nxEventListenerMap::iterator it = m_ListenerRegistry.find(
			inType );
	if ( it == m_ListenerRegistry.end() )
	{
		return false; // no listeners for this event, skip it
	}

	bool rc = false;
	nxEventQueue &evtQueue = m_EventQueues[m_ActiveQueue];
	for ( nxEventQueue::iterator it = evtQueue.begin(),
			itEnd = evtQueue.end(); it != itEnd; it++ )
	{
		if ( (*it)->VGetEventType() == inType )
		{
			it = evtQueue.erase(it);
			rc = true;
			if ( !allOfType )
			{
				break;
			}
		}
		else
		{
			++it;
		}
	}
	return rc;
}

bool nxEventManager::VTick ( unsigned long maxMillis )
{
    jfFPSTimer timer;
    timer.Start();
	unsigned long curMs = 0;
	unsigned long maxMs =
		( maxMillis == nxIEventManager::NX_IEVENT_MANAGER_K_INFINITE ) ?
		nxIEventManager::NX_IEVENT_MANAGER_K_INFINITE
		: (curMs + maxMillis );
	nxEventListenerMap::const_iterator itWC = m_ListenerRegistry.find( NX_EVENT_MANAGER_GLOBAL_LISTENER_IDX );
	
	// swap active queues, make sure new queue is empty after the swap ...
	int queueToProcess = m_ActiveQueue;
	m_ActiveQueue = ( m_ActiveQueue + 1 ) % NX_EVENT_MANAGER_K_NQUEUES;
	m_EventQueues[m_ActiveQueue].clear();
	
	while ( m_EventQueues[queueToProcess].size() > 0 )
	{
		nxIEventDataPtr event = m_EventQueues[queueToProcess].front();
		m_EventQueues[queueToProcess].pop_front();
		nxEventType const & eventType = event->VGetEventType();
		nxEventListenerMap::const_iterator itListeners =
			m_ListenerRegistry.find( eventType );
		if ( itListeners == m_ListenerRegistry.end() )
		{
			continue;
		}
		nxEventListenerTable const & table = itListeners->second;

		//Let all events in table handle event.
		for ( nxEventListenerTable::const_iterator
				it = table.begin(), end = table.end();
				it != end ; it++ )
		{
			if ( (*it)->HandleEvent( *event ) )
			{
				continue;
			}
		}

		//Check to see if time is up
		curMs = timer.GetTicks();
		if ( maxMillis != nxIEventManager::NX_IEVENT_MANAGER_K_INFINITE )
		{
			if ( curMs >= maxMs )
			{
				// time ran about, abort processing loop
				break;
			}
		}
	}
	//if any events left to process, push them onto the active
	//	queue.
	//		Note: to preserve sequencing, go bottom-up on the
	//		remainder, inserting them at the head of the active
	//		queue...
	bool queueFlushed = ( m_EventQueues[queueToProcess].size() == 0 );
	if ( !queueFlushed )
	{
		while ( m_EventQueues[queueToProcess].size() > 0 )
		{
			nxIEventDataPtr event = m_EventQueues[queueToProcess].back();
			m_EventQueues[queueToProcess].pop_back();
			m_EventQueues[m_ActiveQueue].push_front( event );
		}
		queueFlushed = true;
	}
	// all done, this pass
	return queueFlushed;
}

bool nxEventManager::VValidateType( nxEventType const & inType )
	const
{
	//Just check it is in enum somewhere.
	if((inType >= 0) && (inType < NX_EVENT_Endsentinal)) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

nxEventListenerList nxEventManager::GetListenerList (
	nxEventType const & eventType ) const
{
	if ( ! VValidateType( eventType ) )
	{
		return nxEventListenerList();
	}

	nxEventListenerMap::const_iterator itListeners =
		m_ListenerRegistry.find( eventType );

	// no listerners currently for this event type, so sad
	if ( itListeners == m_ListenerRegistry.end() )
	{
		return nxEventListenerList();
	}

	nxEventListenerTable const & table = itListeners->second;

	// there was, but is not now, any listerners currently for
	// this event type, so sad
	if ( table.size() == 0 )
	{
		return nxEventListenerList();
	}

	nxEventListenerList result;

	result.reserve( table.size() );

	for ( nxEventListenerTable::const_iterator it = table.begin(),
			  end = table.end(); it != end ; it++ )
	{
		result.push_back( *it );
	}

	return result;
}
