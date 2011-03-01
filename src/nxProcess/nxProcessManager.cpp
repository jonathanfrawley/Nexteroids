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
#include "nxProcessManager.hpp"

nxProcessManager::nxProcessManager()
{
}

nxProcessManager::~nxProcessManager()
{
	for(nxProcessList::iterator it = m_ProcessList.begin(); it != m_ProcessList.end(); )
	{
		Detach(* (it++) );
	}
}

void nxProcessManager::Attach( shared_ptr<nxProcess> pProcess )
{
	m_ProcessList.push_back(pProcess);
}

bool nxProcessManager::HasProcesses()
{
	return (! m_ProcessList.empty());
}

bool nxProcessManager::IsProcessActive( int nType )
{
	for( nxProcessList::iterator it = m_ProcessList.begin() ; it != m_ProcessList.end() ; it++)
    {
        if ( ( *it )->GetType() == nType &&
        //     ( ( *it )->IsDead() == false || ( *it )->GetNext() ) )
             ( ( *it )->IsActive() || ( *it )->GetNext() ) )
            return true;
    }
    return false;

}

void nxProcessManager::UpdateProcesses(int iDelta)
{
/*
	shared_ptr<nxProcess> processNext;
	for ( nxProcessList::iterator it = m_ProcessList.begin() ; it != m_ProcessList.end() ; ++it )
	{
		log(NX_LOG_DEBUG, "Start of loop");
		std::cout<<m_ProcessList.size()<<std::endl;
		shared_ptr<nxProcess> process( *it );
		log(NX_LOG_DEBUG, "q");
		if ( process->IsDead() )
		{
			log(NX_LOG_DEBUG, "IsDead");
			// Check for a child process and add if exists
			processNext = process->GetNext();
			if ( processNext )
			{
				log(NX_LOG_DEBUG, "Next process added");
				process->SetNext(shared_ptr<nxProcess>((nxProcess *)NULL));
				Attach( processNext );
			}
			Detach( process );
		}
		else if ( process->IsActive() && !process->IsPaused() )
		{
			log(NX_LOG_DEBUG, "Process is not dead");
			process->VOnUpdate( iDelta );
		}
	}
*/
	nxProcessList::iterator i = m_ProcessList.begin();
	nxProcessList::iterator end = m_ProcessList.end();
	shared_ptr<nxProcess> pNext;

	while ( i != end )
	{
		shared_ptr<nxProcess> p( *i );
		++i;

		if ( p->IsDead() )
		{
			// Check for a child process and add if exists
			pNext = p->GetNext();
			if ( pNext )
			{
				p->SetNext(shared_ptr<nxProcess>((nxProcess *)NULL));
				Attach( pNext );
			}
			Detach( p );
		}
		else if ( p->IsActive() && !p->IsPaused() )
		{
			p->VOnUpdate( iDelta );
		}
	}
}

void nxProcessManager::Detach( shared_ptr<nxProcess> pProcess )
{
	m_ProcessList.remove(pProcess);
	pProcess->SetAttached(false);
}
