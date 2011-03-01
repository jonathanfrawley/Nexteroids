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
#include "nxNexteroidsGameLogic.hpp"

#include <nxCore/nxTypes.hpp>
#include <nxGameView/nxNexteroidsGameView.hpp>
#include <nxEvent/nxEventManager.hpp>
#include <nxGameApp/nxGameApp.hpp>

nxNexteroidsGameLogic::nxNexteroidsGameLogic(nxGameOptions const &options)
	:
		nxNexteroidsBaseGameLogic(options)
{
	m_EventListener = nxEventListenerPtr(NX_NEW nxNexteroidsGameLogicEventListener(this));
	m_HasBuiltLevel = false;
}

nxNexteroidsGameLogic::~nxNexteroidsGameLogic()
{
}


void nxNexteroidsGameLogic::VInit()
{
	if(!m_bProxy)
	{
		ListenForNexteroidsGameLogicEvents();
	}
	else
	{
		ListenForProxyNexteroidsGameLogicEvents();
	}
}

void nxNexteroidsGameLogic::VOnUpdate(int deltaMilliseconds)
{
	nxNexteroidsBaseGameLogic::VOnUpdate(deltaMilliseconds);

	switch(m_State)
	{
		case NX_GS_WaitingForPlayers:
			{
				if(m_bProxy)
				{
					break;
				}	

				if(m_NRemotePlayers < m_ExpectedRemotePlayers)
				{
					break;
				}

				if(!m_HasBuiltLevel)
				{
					//Now to create actors and views...
					m_HasBuiltLevel = true;
					VChangeState(NX_GS_LoadedLevel00);
				}
				break;
			}
	}

	m_Time += deltaMilliseconds;
	if(m_Time > 1000)
	{
		m_Time = 0;
	}
}

void nxNexteroidsGameLogic::VBuildLevel00()
{
	//Create Human Player
	float maxPlayerRot = (2*NX_PI);
	int minPlayerX = 0;
	int maxPlayerX = 100;
	int minPlayerY = 0;
	int maxPlayerY = 100;

	int nPlayers = 1; //TODO Add this to n net players
	int playerSpawnChoice = m_Random.NextRandom() % nPlayers; 
	//TODO Add more choices
	
	int playerPosX = 400;
	int playerPosY = 400;
	if(playerSpawnChoice == 0)
	{
		playerPosX = 400;
		playerPosY = 400;
	}

	nxPoint3 playerPos(playerPosX, playerPosY,0);

	nxReal playerRot = 0;

	shared_ptr<nxSpaceshipActor> pPlayer(NX_NEW nxSpaceshipActor(playerRot, playerPos));

	const nxActorId actorId = GetNewActorId();
	pPlayer->VSetId(actorId);
	nxColour playerColour;
	playerColour.r = 0;
	playerColour.g = 1;
	playerColour.b = 0; //Server is always green! Best colour
	pPlayer->VSetColour(playerColour);

	//Create Human player view
	shared_ptr<nxIGameView> gameView(NX_NEW nxNexteroidsGameView());
	gameView->Init();
	m_GameViews.pop_back(); //XXX: Better to search for this?
	VAddView(gameView, actorId); //View Id set here

	pPlayer->VSetViewId(gameView->VGetId());

	const nxIEventDataPtr eventPtr( NX_NEW nxRequestNewActorEventData(pPlayer));
	nxEventManager::GetInstance().VQueueEvent(eventPtr);

	//Create Rocks
	
	int nRocks = 14;
	srand ( time(NULL) );

	for(int i = 0; i < nRocks ; i++)
	{
		int minRockX = 100;
		int maxRockX = 300;
		int minRockY = 100;
		int maxRockY = 300;
		int maxRockSpeed = 1;

		int rockPosX = 0;
		int rockPosY = 0; 
		nxReal rockRot = 0;
		//Choose a side to place the rock
		int side = m_Random.NextRandom() % 4;
		if(side == 0)
		{
			//Bottom
			rockPosX = m_Random.NextRandomFloat(NX_SCREEN_WIDTH);
			rockPosY = 10;
			rockRot = NX_PI_OVER_2;
		}
		else if (side==1)
		{
			//Top
			rockPosX = m_Random.NextRandomFloat(NX_SCREEN_WIDTH);
			rockPosY = NX_SCREEN_HEIGHT - 10;
			rockRot = -NX_PI_OVER_2;
		}
		if(side == 2)
		{
			//left
			rockPosX = 10;
			rockPosY = m_Random.NextRandomFloat(NX_SCREEN_HEIGHT);
			rockRot = 0;
		}
		else if (side==3)
		{
			//Right
			rockPosX = NX_SCREEN_WIDTH - 10;
			rockPosY = m_Random.NextRandomFloat(NX_SCREEN_HEIGHT);
			rockRot = NX_PI;
		}

		nxPoint3 rockPos(rockPosX, rockPosY,0);
		nxReal rockSpeed = 2; //TODO : Increment with time spent in game for awesome fun.
	   	nxReal rockRadius = 20; //XXX: Is needed?
		shared_ptr<nxRockActor> pRock(NX_NEW nxRockActor(rockRot, rockPos, rockRadius, rockSpeed));
		nxColour rockColour;
		rockColour.r = 1;
		rockColour.g = 1;
		rockColour.b = 1; //Server is always green! Best colour
		pRock->VSetColour(rockColour);
		pRock->VSetViewId(-1); //Don't need this I think
		const nxActorId rockActorId = GetNewActorId();
		pRock->VSetId(rockActorId);
		const nxIEventDataPtr rockEventPtr( NX_NEW nxRequestNewActorEventData(pRock));
		nxEventManager::GetInstance().VQueueEvent(rockEventPtr);
	}

	//TODO : Create Net Player actors with view ids of their ips.
	vector<int>::iterator it, itEnd;
	for(it = m_ConnectedClientIds.begin(), itEnd = m_ConnectedClientIds.end() ; 
			it != itEnd ; 
			it++)
	{
		maxPlayerRot = (2*NX_PI);
		minPlayerX = 0;
		maxPlayerX = 100;
		minPlayerY = 0;
		maxPlayerY = 100;
		playerPosX = (rand() % maxPlayerX);
		playerPosY = (rand() % maxPlayerY);
		nxPoint3 netPlayerPos(playerPosX, playerPosY,0);
		nxReal netPlayerRot = fmod((nxReal)rand(), maxPlayerRot);
		shared_ptr<nxSpaceshipActor> pNetPlayer(NX_NEW nxSpaceshipActor(netPlayerRot, netPlayerPos));
		const nxActorId netActorId = GetNewActorId();

		pNetPlayer->VSetId(netActorId);
		nxColour netPlayerColour;
		//TODO: Change colour on each client
		netPlayerColour.r = 1;
		netPlayerColour.g = 0;
		netPlayerColour.b = 0;
		pNetPlayer->VSetColour(netPlayerColour);
		//This is the important part. Set view id and ship to event manager.
		pNetPlayer->VSetViewId((*it));

		const nxIEventDataPtr netEventPtr( NX_NEW nxRequestNewActorEventData(pNetPlayer) );
		nxEventManager::GetInstance().VQueueEvent(netEventPtr);
	}
}

//TODO:Remove, ideally proxy wouldn't respond to any events.
void nxNexteroidsGameLogic::ListenForProxyNexteroidsGameLogicEvents()
{
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_RequestNewGame);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_RemoteClient); //Sent when we want to connect.
}

void nxNexteroidsGameLogic::ListenForNexteroidsGameLogicEvents()
{
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_RequestNewGame);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_GameState);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_RequestNewActor);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_NewActor);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_Thrust);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_Steer);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_FireWeapon);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_PhysCollision);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_ActorDeath);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_ActorMoved);
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_RemoteClient);
}

void nxNexteroidsGameLogic::SpawnActor(nxActorType type)
{
	if(type == NX_ACTOR_ROCK)
	{
		int minRockX = 100;
		int maxRockX = 300;
		int minRockY = 100;
		int maxRockY = 300;
		int maxRockSpeed = 1;
		int rockPosX = minRockX + (rand() % maxRockX);
		int rockPosY = minRockY + (rand() % maxRockY);

		nxPoint3 rockPos(rockPosX, rockPosY,0);
		nxReal rockRot = (fmod((nxReal)rand(), (NX_PI/16)));
		nxReal rockSpeed = (nxReal)(rand() % maxRockSpeed);
		nxReal rockRadius = 20; //XXX: Is needed?
		shared_ptr<nxRockActor> pRock(NX_NEW nxRockActor(rockRot, rockPos, rockRadius, rockSpeed));
		nxColour rockColour;
		rockColour.r = 1;
		rockColour.g = 1;
		rockColour.b = 1; //Server is always green! Best colour
		pRock->VSetColour(rockColour);
		pRock->VSetViewId(-1); //Don't need this I think
		const nxActorId rockActorId = GetNewActorId();
		pRock->VSetId(rockActorId);
		const nxIEventDataPtr rockEventPtr( NX_NEW nxRequestNewActorEventData(pRock));
		nxEventManager::GetInstance().VQueueEvent(rockEventPtr);
	}
}
