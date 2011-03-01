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
#include "nxNexteroidsGameApp.hpp"

#include <arpa/inet.h>

#include <nxGameView/nxIGameView.hpp>
#include <nxGameView/nxHumanView.hpp>
#include <nxGameView/nxNetworkEventForwarder.hpp>
#include <nxGameView/nxMainMenuGameView.hpp>
#include <nxEvent/nxEventManager.hpp>
#include <nxNet/nxClientNetworkManager.hpp>
#include <nxNet/nxServerNetworkManager.hpp>

nxNexteroidsGameApp nxNexteroidsGameApp::m_Instance;

nxNexteroidsGameApp::nxNexteroidsGameApp()
	:
		nxGameApp()
{
}

nxNexteroidsGameApp::~nxNexteroidsGameApp()
{
}

nxNexteroidsGameApp& nxNexteroidsGameApp::GetInstance()
{
	static nxNexteroidsGameApp m_Instance;
	return m_Instance;
}

void nxNexteroidsGameApp::VCreateNetworkManager()
{
	if(m_Config->GetBool(NX_CONFIG_IS_CLIENT))
	{
		//TODO: Get these from file.
		string clientListenAddr = m_Config->GetString(NX_CONFIG_CLIENT_LISTEN_ADDR);
		string serverAddr = m_Config->GetString(NX_CONFIG_CLIENT_SERVER_ADDR);
		m_NetworkManager = NX_NEW nxClientNetworkManager(clientListenAddr, serverAddr);
	}
	else
	{
		int nNetPlayers = m_Config->GetInt(NX_CONFIG_N_NET_PLAYERS);
		string serverListenAddr = m_Config->GetString(NX_CONFIG_SERVER_LISTEN_ADDR);
		//These are client publisher ips, we are going to subscribe to them.
		vector<string> clientIps = m_Config->GetVector(NX_CONFIG_SERVER_CLIENT_IPS);
		m_NetworkManager = NX_NEW nxServerNetworkManager(serverListenAddr, clientIps);
	}
	m_NetworkManager->Init();
}

void nxNexteroidsGameApp::ListenForNexteroidsViewCommands(nxEventListenerPtr listener)
{
	//Events sent from client to server
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_RemoteClient);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_Thrust);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_Steer);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_FireWeapon);
}

void nxNexteroidsGameApp::ListenForNexteroidsGameCommands(nxEventListenerPtr listener)
{
	//Events sent from server to client
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_GameState);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_ActorDeath);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_ActorMoved);
    nxEventManager::GetInstance().VAddListener(listener, NX_EVENT_NewActor);
}

unsigned nxNexteroidsGameApp::ConvertIpStringToUInt(string ip)
{
	struct sockaddr_in sa; // IPv4
	inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)); // IPv4
	return ntohl(sa.sin_addr.s_addr);
}

void nxNexteroidsGameApp::VCreateGameLogicAndGameView()
{
	nxGameOptions opt;
	opt.nNetPlayers = m_Config->GetInt(NX_CONFIG_N_NET_PLAYERS);
	
	m_GameLogic = NX_NEW nxNexteroidsGameLogic(opt);

	if(m_Config->GetBool(NX_CONFIG_IS_CLIENT))
	{
		log(NX_LOG_DEBUG,"is a client");
		nxEventListenerPtr listener ( NX_NEW nxNetworkEventForwarder() );
		ListenForNexteroidsViewCommands(listener);
		m_GameLogic->SetProxy(true);
		string ipString = m_Config->GetString(NX_CONFIG_MY_IP);
		unsigned ipInt = ConvertIpStringToUInt(ipString);
		m_GameLogic->SetIpInt(ipInt);
		m_GameLogic->VInit();

		shared_ptr<nxIGameView> gameView(NX_NEW nxMainMenuGameView());
		gameView->Init();
		m_GameLogic->VAddView(gameView, ipInt);
	}
	else
	{
		nxEventListenerPtr listener ( NX_NEW nxNetworkEventForwarder() );
		ListenForNexteroidsGameCommands(listener);
		m_GameLogic->SetProxy(false);
		m_GameLogic->VInit();
		log(NX_LOG_DEBUG,"is a server");

		shared_ptr<nxIGameView> gameView(NX_NEW nxMainMenuGameView());
		gameView->Init();
		m_GameLogic->VAddView(gameView, -1);
	}
}
