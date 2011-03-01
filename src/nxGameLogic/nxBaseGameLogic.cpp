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
#include "nxBaseGameLogic.hpp"
#include <nxEvent/nxEventManager.hpp>
#include <nxEvent/nxLoadingGameEventData.hpp>
#include <nxPhysics/nxPhysics.hpp>

nxBaseGameLogic::nxBaseGameLogic()
{
}

nxBaseGameLogic::nxBaseGameLogic(nxGameOptions const &options)
{
	m_LastActorId = 0;
	m_pProcessManager = NX_NEW nxProcessManager;
	m_State = NX_GS_Initializing;
	m_bProxy = false;
	m_RenderDiagnostics = false;
	m_NRemotePlayers = 0;
	m_ExpectedRemotePlayers = options.nNetPlayers;
	m_ExpectedAI = 0;
	shared_ptr<nxIPhysics> physics(NX_NEW nxPhysics());
	m_pPhysics = physics;

	//TODO : AI
//	m_pAiEventListener = nxEventListenerPtr (NX_NEW nxAiEventListener ( ));
//	safeAddListener(m_pAiEventListener, nxEvtData_AiSteer::sk_EventType);
}


nxBaseGameLogic::~nxBaseGameLogic()
{
	while (!m_GameViews.empty())
	{
		m_GameViews.pop_front();
	}

	NX_SAFE_DELETE(m_pProcessManager);
}

nxActorId nxBaseGameLogic::GetNewActorId()
{
	return (m_LastActorId++);
}

void nxBaseGameLogic::VAddActor(shared_ptr<nxIActor> actor)
{
	nxActorId destActorID = actor->VGetId();
	m_ActorList[ destActorID ] = actor;
	actor->VSetId( destActorID );
}

void nxBaseGameLogic::VRemoveActor(nxActorId aid)
{
	if (m_bProxy)
	{
		return;
	}

	if( NULL != VGetActor(aid).get() )
	{
		m_pPhysics->VRemoveActor(aid);
		m_ActorList.erase(aid);
	}
	else
	{
		assert(0 && "Unknown actor!");
	}
}

void nxBaseGameLogic::VMoveActor(const nxActorId id, nxPoint3 pos, nxReal orientation)
{
	shared_ptr<nxIActor> actor = VGetActor(id);

	if(actor)
	{
		actor->VSetPos(pos);
		actor->VSetOrientation(orientation);
	}
}

shared_ptr<nxIActor> nxBaseGameLogic::VGetActor(const nxActorId id)
{
	nxActorMap::iterator i = m_ActorList.find(id);
	if (i==m_ActorList.end())
	{
		shared_ptr<nxIActor> null;
		return null;
	}

	return (*i).second;
}

void nxBaseGameLogic::VOnUpdate(int deltaMilliseconds)
{
	switch(m_State)
	{
		case NX_GS_Initializing:
			// If we get to here we're ready to attach players
			VChangeState(NX_GS_MainMenu);
			break;
		case NX_GS_MainMenu:
			break;
		case NX_GS_LoadingGameEnvironment:
			break;
		case NX_GS_WaitingForPlayers:
			// do nothing - the game class should handle this one.
			break;
		case NX_GS_SpawnAI:
			if (m_ExpectedAI == 0)
			{
				VChangeState(NX_GS_Running);
			}
			break;
		case NX_GS_Running:
			m_pProcessManager->UpdateProcesses(deltaMilliseconds);
			break;
		default:
			assert(1 && "Unrecognized state.");
	}

	for(int i = 0 ; i < 10 ; i++)
	{
		float32 physicsStep = 1.0f / 60.0f;
		m_pPhysics->VOnUpdate(physicsStep);
	}

	nxGameViewList::iterator i=m_GameViews.begin();
	nxGameViewList::iterator end=m_GameViews.end();
	while (i != end)
	{
		(*i)->VOnUpdate( deltaMilliseconds );
		++i;
	}
}

void nxBaseGameLogic::VChangeState(nxGameState newState)
{
	if (newState==NX_GS_WaitingForPlayers)
	{
		if(m_bProxy)
		{
			//Send event to server to signal connect.
			nxEventManager::GetInstance().VQueueEvent( nxIEventDataPtr(NX_NEW nxRemoteClientEventData(m_IpInt)) );
		}
		else
		{
			//Server should wait for clients here.

		}
	}

	m_State = newState;
	if (!m_bProxy)
	{
		nxEventManager::GetInstance().VQueueEvent( nxIEventDataPtr(NX_NEW nxGameStateEventData(m_State)) );
	}
}

void nxBaseGameLogic::VBuildInitialScene()
{
	//TODO: Done in script in book.
}

void nxBaseGameLogic::VRenderDiagnostics()
{
	if (m_RenderDiagnostics)
	{
		m_pPhysics->VRenderDiagnostics();
	}
}

void nxBaseGameLogic::TogglePause(bool active)
{
	// TODO This belongs in the view, not the game!
}

//Don't generate a view ID, assume it's been set.
void nxBaseGameLogic::VAddViewExplicit(shared_ptr<nxIGameView> pView, int viewId, nxActorId actorId)
{
	m_GameViews.push_back(pView);
	pView->VOnAttach(viewId, actorId);
	pView->VOnRestore();
}

void nxBaseGameLogic::VAddView(shared_ptr<nxIGameView> pView, nxActorId actorId)
{
	// This makes sure that all views have a non-zero view id.
	int viewId = static_cast<int>(m_GameViews.size());
	m_GameViews.push_back(pView);
	pView->VOnAttach(viewId, actorId);
	pView->VOnRestore();
}

void nxBaseGameLogic::VRemoveView(shared_ptr<nxIGameView> pView)
{
	m_GameViews.remove(pView);
}

