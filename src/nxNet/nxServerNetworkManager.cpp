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
#include "nxServerNetworkManager.hpp"

#include <sstream>

int NX_N_SERVER_THREADS = 2;

nxServerNetworkManager::nxServerNetworkManager(string serverListenAddr, vector<string> clientIps)
{
	m_ClientIps = clientIps;
	m_ServerListenAddr = serverListenAddr;
}

nxServerNetworkManager::~nxServerNetworkManager()
{
	NX_SAFE_DELETE(m_Publisher);
	NX_SAFE_DELETE(m_Context);
}

bool nxServerNetworkManager::Init()
{
	m_Context = NX_NEW context_t(NX_N_SERVER_THREADS);

	//Create publisher socket.
	m_Publisher = NX_NEW socket_t(*m_Context, ZMQ_PUB);

    m_Publisher->bind (m_ServerListenAddr.c_str());

	vector<string>::iterator it, itEnd;
	for(it = m_ClientIps.begin(), itEnd = m_ClientIps.end() 
			; it != itEnd 
			; it++)
	{
		socket_t* client = NX_NEW socket_t(*m_Context, ZMQ_SUB);
		client->setsockopt (ZMQ_SUBSCRIBE, 0, 0); //Subscribe to all messages? Maybe make more efficient.
		client->connect ((*it).c_str());
		m_Clients.push_back(client);
	}

	return true;
}

void nxServerNetworkManager::AssertRcType(int rc)
{
	switch(rc)
	{
		case EAGAIN:
			{
			log(NX_LOG_ERROR, "EAGAIN");
			assert(0 && "EAGAIN");
			break;
			}
		case ENOTSUP:
			{
			log(NX_LOG_ERROR, "ENOTSUP");
			assert(0 && "ENOTSUP");
			break;
			}
		case EFSM:
			{
			log(NX_LOG_ERROR, "EFSM");
			assert(0 && "EFSM");
			break;
			}
		case EFAULT:
			{
			log(NX_LOG_ERROR, "EFAULT");
			assert(0 && "EFAULT");
			break;
			}
		default:
			{
			break;
			}
	}
}

void nxServerNetworkManager::ListenToAllClients()
{
	vector<socket_t*>::iterator it, itEnd;
	for(it = m_Clients.begin(), itEnd = m_Clients.end() 
			; it != itEnd 
			; it++)
	{
		bool finished = false;
		while(!finished)
		{
			zmq::message_t message(NX_MAX_PACKET_SIZE);

			int rc;
			rc = (*it)->recv(&message, ZMQ_NOBLOCK);
			AssertRcType(rc);

			if(message.size() == 0)
			{
				//A null packet received
				finished = true;
				break;
			}

			//Copy message into packet data structure and pass to packet-->event converter
			nxPacketPtr recvPacket(NX_NEW nxBinaryPacket(message.size()));
			memcpy ((void*)recvPacket->VGetData(), (void *) message.data(), message.size());

			stringstream out;
			out<<"message size is :" <<message.size()<<endl;
			out<<"message code is :" <<ntohl((*((int*)(message.data()))))<<endl;

			log(NX_LOG_DEBUG, out.str());

			//Do packet processing
			m_RemoteEventToLocal.ConvertAndQueuePacket(recvPacket);
		}
	}
}

void nxServerNetworkManager::VTick()
{
	ListenToAllClients();
}

void nxServerNetworkManager::SendToAllSubscribers(nxPacketPtr packet)
{
	zmq::message_t msg (packet->VGetSize());
	memcpy ((void *) msg.data(), packet->VGetData(), packet->VGetSize());

	
	char* string = (char*)(msg.data()+sizeof(uint32_t));
	m_Publisher->send (msg);	

	log(NX_LOG_DEBUG, "sending message to subscribers...");
}
