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
#ifndef  NXBASEGAMELOGIC_H
#define  NXBASEGAMELOGIC_H

#include <map>
#include <list>
#include <vector>

#include <boost/optional/optional.hpp>

#include <nxActor/nxIActor.hpp>
#include <nxCore/nxCore.hpp>
#include <nxProcess/nxProcessManager.hpp>
#include <nxRandom/nxRandom.hpp>
#include <nxPhysics/nxIPhysics.hpp>
#include <nxGameView/nxIGameView.hpp>
#include <nxEvent/nxIEventListener.hpp>
#include <nxUtil/nxUtil.hpp>
#include <nxGameLogic/nxGameOptions.hpp>
#include <nxGameLogic/nxIGameLogic.hpp>
#include <nxEvent/nxIEventManager.hpp>
#include <nxEvent/nxGameStateEventData.hpp>
#include <nxEvent/nxRemoteClientEventData.hpp>

using namespace std;

//TODO Put these in more logical place.
typedef std::list<shared_ptr<nxIGameView> > nxGameViewList;
typedef std::map<nxActorId, shared_ptr<nxIActor> > nxActorMap;

/*
 * =====================================================================================
 *        Class: nxBaseGameLogic
 *  Description: Base Game Logic for all game logics to inherit from.
 * =====================================================================================
 */
class nxBaseGameLogic : public nxIGameLogic
{
	public:
		nxBaseGameLogic();

		nxBaseGameLogic(nxGameOptions const &options);

		virtual ~nxBaseGameLogic();

		void TogglePause(bool active);

		void SetProxy(bool isProxy) { m_bProxy = isProxy; }

		bool IsProxy() 
		{ 
			return m_bProxy;
		}

		nxActorId GetNewActorId();

		nxActorId GetRandomActor(nxActorId ignoreMe);

		nxRandom& GetRNG(void) { return m_Random; }

		virtual void VBuildInitialScene();

		//Doesn't auto gen a view id
		virtual void VAddViewExplicit(shared_ptr<nxIGameView> pView, int viewId, nxActorId actorId);

		virtual void VAddView(shared_ptr<nxIGameView> pView, nxActorId actorId);

		virtual void VRemoveView(shared_ptr<nxIGameView> pView);

		virtual void VAddActor(shared_ptr<nxIActor> actor);

		virtual shared_ptr<nxIActor> VGetActor(const nxActorId id);

		virtual void VRemoveActor(nxActorId id);

		virtual void VMoveActor(const nxActorId id, nxPoint3 pos, nxReal orientation);

		virtual bool VLoadGame(std::string gameName) { return true; }

		virtual void VSetProxy() { m_bProxy = true; }

		// Logic Update
		virtual void VOnUpdate(int deltaMilliseconds);

		// Changing Game Logic State
		virtual void VChangeState(nxGameState newState);

		// Render Diagnostics TODO
		virtual void VRenderDiagnostics();
		virtual shared_ptr<nxIPhysics> VGetGamePhysics(void) 
		{ 
			return m_pPhysics; 
		}

		void AttachProcess(shared_ptr<nxProcess> pProcess) 
		{ 
			if (m_pProcessManager) 
			{
				m_pProcessManager->Attach(pProcess);
			} 
		}

		shared_ptr<nxIPhysics> VGetPhysics()
		{
			return m_pPhysics;
		}

        nxGameViewList& GetGameViews()
        {
            return m_GameViews;
        }

		void SetNRemotePlayers(int val)
		{
			m_NRemotePlayers = val;
		}

		int GetNRemotePlayers()
		{
			return m_NRemotePlayers;
		}

		void SetIpInt(unsigned ip)
		{
			m_IpInt = ip;
		}

		int GetIpInt()
		{
			return m_IpInt;
		}

		void VAddConnectedClientId(unsigned id)
		{
			m_ConnectedClientIds.push_back(id);
		}

		virtual void VPopView()
		{
			m_GameViews.pop_back();
		}

	protected:
		nxProcessManager* m_pProcessManager;
		nxRandom m_Random;
		nxActorMap m_ActorList;
		nxActorId m_LastActorId;
		nxGameState m_State;
		vector<int> m_ConnectedClientIds;
		int m_NRemotePlayers;
		int m_ExpectedRemotePlayers;
		int m_ExpectedAI;

		unsigned m_IpInt; //If we are client, this is id on remote machine.

		nxGameViewList m_GameViews;
		nxEventListenerPtr m_pAiEventListener;			// AI event listener

		bool m_bProxy;									// set if this is a proxy game logic, not a real one
		int m_remotePlayerId;							// if we are a remote player - what is out socket number on the server

		bool m_RenderDiagnostics;						// Are we rendering diagnostics?
		shared_ptr<nxIPhysics> m_pPhysics;
};

#endif   // NXBASEGAMELOGIC_H
