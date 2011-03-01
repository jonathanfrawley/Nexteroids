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
#include "nxNexteroidsGameViewEventListener.hpp"

#include <sstream>

#include <nxEvent/nxGameStateEventData.hpp>
#include <nxEvent/nxActorDeathEventData.hpp>
#include <nxEvent/nxActorMovedEventData.hpp>

bool nxNexteroidsGameViewEventListener::HandleEvent( nxIEventData const & event )
{
	if(event.VGetEventType() == NX_EVENT_GameState)
	{
        nxGameStateEventData* gameStateEvent = (nxGameStateEventData*)(&event);
		/*
		if(gameStateEvent->GetState() == NX_GS_LoadingGameEnvironment)
		{
			m_pGameView->ShowLoadingScreen();
		}
		
		else
	   */

		if(gameStateEvent->GetState() == NX_GS_LoadedLevel00)
		{
			m_pGameView->BuildInitialLevel00();
		}
		
		return true;
	}
	else if(event.VGetEventType() == NX_EVENT_NewActor)
	{
		const nxNewActorEventData & castEvent =
			static_cast< const nxNewActorEventData & >( event );
		nxIActor* actor = castEvent.GetActor();

		stringstream out;
		out<<"NewActor event here:"<<castEvent.GetActor()->VGetId()<<endl;
		out<<"type:"<<castEvent.GetActor()->VGetType()<<endl;
		log(NX_LOG_DEBUG, out.str());

		shared_ptr<nxIActor> pActor(actor->VClone());
//		pActor->VCreate();

		m_pGameView->VAddActor(pActor);

//		stringstream out;
		out.clear();
		out<<"actor->VGetViewId() is : " << pActor->VGetViewId()<<endl;
		out<<"m_PGameView->VGetId() : "<< m_pGameView->VGetId()<<endl;
		log(NX_LOG_DEBUG, out.str());

		if(pActor->VGetViewId() == m_pGameView->VGetId())
		{
			m_pGameView->VSetActor(pActor);
		}
	}
	else if(event.VGetEventType() == NX_EVENT_ActorDeath) 
	{
		const nxActorDeathEventData & castEvent =
			static_cast< const nxActorDeathEventData & >( event );


		nxActorId aid = castEvent.GetActorId();
		shared_ptr<nxIActor> actor = m_pGameView->VGetActor(aid);

		shared_ptr<nxIActor> null;

		if(actor == null)
		{
//			assert(0 && "Null actor found");
			return true;
		}

		if(aid == m_pGameView->GetViewActorId())
		{
			m_pGameView->SetViewActorIdInvalid();
		}
				
		if(actor->VGetType() == NX_ACTOR_ROCK)
		{
			m_pGameView->PlayRockDeathSound();

			if(m_pGameView->GetViewActorId() != -1)
			{
				m_pGameView->AddToScore(1);
			}
		}
		else if(actor->VGetType() == NX_ACTOR_SPACESHIP)
		{
			if(actor->VGetId() == m_pGameView->GetViewActorId())
			{
				m_pGameView->PlaySpaceshipDeathSound();
				if(m_pGameView->GetViewActorId() != -1)
				{
					m_pGameView->AddToScore(2);
				}
			}
		}

		m_pGameView->VRemoveActor(aid);

	}
	else if(event.VGetEventType() == NX_EVENT_ActorMoved) 
	{
		const nxActorMovedEventData & castEvent =
			static_cast< const nxActorMovedEventData & >( event );
		m_pGameView->VMoveActor(castEvent.GetActorId(), castEvent.GetPos(), castEvent.GetOrientation());
	}

	return false;
}
