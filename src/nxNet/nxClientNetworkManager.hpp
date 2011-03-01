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
#ifndef  NXCLIENTNETWORKMANAGER_H
#define  NXCLIENTNETWORKMANAGER_H

#include <string>

//TODO: Remove these 2
#include <iostream>
#include <netinet/in.h>

#include <zmq.hpp>

#include <nxNet/nxRemoteEventToLocalConverter.hpp>
#include <nxNet/nxINetworkManager.hpp>
#include <nxNet/nxBinaryPacket.hpp>

using namespace std;
using namespace zmq;

/*
 * =====================================================================================
 *        Class: nxClientNetworkManager
 *  Description: Clients use this to connect to servers and to publish their updates.
 * =====================================================================================
 */
class nxClientNetworkManager : public nxINetworkManager
{
	public:

		nxClientNetworkManager(string publisherAddr, string serverAddress);

		virtual ~nxClientNetworkManager();

		virtual bool Init();

		virtual void VTick();

		void AssertRcType(int rc);

		void ListenToServer();

		void SendToAllSubscribers(nxPacketPtr packet);
		
	protected:
		string m_PublisherAddr;
		string m_ServerAddr;
		context_t *m_Context;
		socket_t *m_Publisher;
		socket_t *m_ServerListener;
		nxRemoteEventToLocalConverter m_RemoteEventToLocal;

	private:
};


#endif   // NXCLIENTNETWORKMANAGER_H
