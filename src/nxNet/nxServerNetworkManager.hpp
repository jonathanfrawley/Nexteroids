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

#ifndef  NXSERVEREVENTMANAGER_H
#define  NXSERVEREVENTMANAGER_H

#include <vector>
#include <string>

//TODO: Remove these 2
#include <iostream>
#include <netinet/in.h>

#include <zmq.hpp>

#include <nxCore/nxCore.hpp>
#include <nxNet/nxRemoteEventToLocalConverter.hpp>
#include <nxNet/nxINetworkManager.hpp>
#include <nxNet/nxBinaryPacket.hpp>


using namespace std;
using namespace zmq;

/*
 * =====================================================================================
 *        Class: nxServerNetworkManager
 *  Description: Sends packets to clients with events and subscribes to updates from all
 *  clients.
 * =====================================================================================
 */
class nxServerNetworkManager : public nxINetworkManager
{
	public:
		nxServerNetworkManager(string serverListenAddr, vector<string> clientIps);

		virtual ~nxServerNetworkManager();

		virtual bool Init();

		virtual void Step() { ; }

		void AssertRcType(int rc);

		void ListenToAllClients();

		virtual void VTick();

		virtual void SendToAllSubscribers(nxPacketPtr packet);
		
	protected:
		context_t *m_Context;
		socket_t *m_Publisher;
		vector<string> m_ClientIps;
		vector<socket_t*> m_Clients;
		nxRemoteEventToLocalConverter m_RemoteEventToLocal;
		string m_ServerListenAddr;

	private:
};

#endif   // NXSERVEREVENTMANAGER_H
