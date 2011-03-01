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
#include "nxNexteroidsGameView.hpp"

#include <nxEvent/nxEventManager.hpp>
#include <nxEvent/nxIEventListener.hpp>
#include <nxGameView/nxNexteroidsGameViewEventListener.hpp>

nxNexteroidsGameView::nxNexteroidsGameView ()
	:
		nxHumanView()
{
	m_WAlreadyPressed = false;
	m_SAlreadyPressed = false;
	m_AAlreadyPressed = false;
	m_DAlreadyPressed = false;
	m_SpaceAlreadyPressed = false;
	m_ActorValid = true;
}

nxNexteroidsGameView::~nxNexteroidsGameView ()
{
}

bool nxNexteroidsGameView::Init()
{
	nxHumanView::Init();

    m_EventListener = nxEventListenerPtr (NX_NEW nxNexteroidsGameViewEventListener(this));
	ListenForNexteroidsGameViewEvents();

	m_Explosion = Mix_LoadWAV( "../../media/sounds/explosion.wav" );
	m_Laser = Mix_LoadWAV( "../../media/sounds/laser.wav" );

    return true;
}

void nxNexteroidsGameView::ListenForNexteroidsGameViewEvents()
{
    nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_GameState);
    nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_NewActor);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_ActorDeath);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_ActorMoved);
}

void nxNexteroidsGameView::PlaySound()
{
}

void nxNexteroidsGameView::PlayRockDeathSound()
{
	/*
	if( Mix_PlayChannel( -1, m_Explosion, 0 ) == -1 ) 
	{ 
		;
//		assert(0 && "Can't play sound");
	}
	*/
}

void nxNexteroidsGameView::PlaySpaceshipDeathSound()
{
	/*
	if( Mix_PlayChannel( -1, m_Explosion, 0 ) == -1 ) 
	{ 
		;
//		assert(0 && "Can't play sound");
	}
	*/
}

void nxNexteroidsGameView::PlayFireBulletSound()
{
	if( Mix_PlayChannel( -1, m_Laser, 0 ) == -1 ) 
	{ 
		;
//		assert(0 && "Can't play sound");
	}
}

void nxNexteroidsGameView::VHandleKeyboardCommands(SDL_Event event)
{
	//Handle core commands to quit, etc. first 
	nxHumanView::VHandleKeyboardCommands(event);

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
//			if(! m_WAlreadyPressed)
//			{
			nxActorId actorId = m_pActor->VGetId();
			const nxIEventDataPtr eventPtr( NX_NEW nxThrustEventData(actorId, 1.0));
			nxEventManager::GetInstance().VQueueEvent(eventPtr);
			m_WAlreadyPressed = true;
//			}
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
//			if(!m_SAlreadyPressed)
//			{
			nxActorId actorId = m_pActor->VGetId();
			const nxIEventDataPtr eventPtr( NX_NEW nxThrustEventData(actorId, -1.0));
			nxEventManager::GetInstance().VQueueEvent(eventPtr);
			m_SAlreadyPressed = true;
//			}
		}
		if (event.key.keysym.sym == SDLK_a)
		{
//			if(!m_AAlreadyPressed)
			{
				nxActorId actorId = m_pActor->VGetId();
				const nxIEventDataPtr eventPtr( NX_NEW nxSteerEventData(actorId, 1.0));
				nxEventManager::GetInstance().VQueueEvent(eventPtr);
				m_AAlreadyPressed = true;
			}
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
//			if(!m_DAlreadyPressed)
			{
				nxActorId actorId = m_pActor->VGetId();
				const nxIEventDataPtr eventPtr( NX_NEW nxSteerEventData(actorId, -1.0));
				nxEventManager::GetInstance().VQueueEvent(eventPtr);
				m_DAlreadyPressed = true;
			}
		}
		else if(event.key.keysym.sym == SDLK_SPACE)
		{
			if(!m_SpaceAlreadyPressed)
			{
				nxActorId actorId = m_pActor->VGetId();
				const nxIEventDataPtr eventPtr( NX_NEW nxFireWeaponEventData(actorId) );
				nxEventManager::GetInstance().VQueueEvent(eventPtr);
				m_SpaceAlreadyPressed = true;
//				PlayFireBulletSound();
			}
		}
	}
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
			m_WAlreadyPressed = false;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			m_SAlreadyPressed = false;
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			nxActorId actorId = m_pActor->VGetId();
			const nxIEventDataPtr eventPtr( NX_NEW nxSteerEventData(actorId, 0.0));
			nxEventManager::GetInstance().VQueueEvent(eventPtr);
			m_AAlreadyPressed = false;
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			nxActorId actorId = m_pActor->VGetId();
			const nxIEventDataPtr eventPtr( NX_NEW nxSteerEventData(actorId, 0.0));
			nxEventManager::GetInstance().VQueueEvent(eventPtr);
			m_DAlreadyPressed = false;
		}
		else if(event.key.keysym.sym == SDLK_SPACE)
		{
			m_SpaceAlreadyPressed = false;
		}
	}
}

void nxNexteroidsGameView::ShowLoadingScreen()
{
	while( ! m_Screens.empty())
	{
		m_Screens.pop_back();
	}
    boost::shared_ptr<nxLoadingScreen> loadingScreen(NX_NEW nxLoadingScreen());
    loadingScreen->Init();
    m_Screens.push_back(loadingScreen);
}

void nxNexteroidsGameView::BuildInitialLevel00()
{
	while( ! m_Screens.empty())
	{
		m_Screens.pop_back();
	}

	log(NX_LOG_DEBUG, "Building initial Scene");
    boost::shared_ptr<nxGameScreen> screen(NX_NEW nxGameScreen());
    screen->Init();

	vector<shared_ptr<nxIActor> >::iterator it, itEnd;
	for(it = m_Actors.begin(), itEnd = m_Actors.end() ; it != itEnd ; it++)
	{
		screen->VAddActor((*it));
	}
	
    m_Screens.push_back(screen);
}
