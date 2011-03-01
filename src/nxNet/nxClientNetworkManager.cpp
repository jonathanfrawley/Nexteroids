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
#include "nxClientNetworkManager.hpp"

int NX_N_CLIENT_THREADS = 1;

nxClientNetworkManager::nxClientNetworkManager(string publisherAddr, string serverAddr)
{
	m_PublisherAddr = publisherAddr;
	m_ServerAddr = serverAddr;
}

nxClientNetworkManager::~nxClientNetworkManager()
{
	NX_SAFE_DELETE(m_Publisher);
	NX_SAFE_DELETE(m_Context);
}

bool nxClientNetworkManager::Init()
{
	m_Context = NX_NEW context_t(NX_N_CLIENT_THREADS);

	//Create publisher socket.
	m_Publisher = NX_NEW socket_t(*m_Context, ZMQ_PUB);

    m_Publisher->bind (m_PublisherAddr.c_str());

	//Now sub to server messages
	m_ServerListener = NX_NEW socket_t(*m_Context, ZMQ_SUB);
	m_ServerListener->setsockopt (ZMQ_SUBSCRIBE, 0, 0); //Subscribe to all messages? Maybe make more efficient.
	m_ServerListener->connect (m_ServerAddr.c_str());

	return true;
}

void nxClientNetworkManager::AssertRcType(int rc)
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

void nxClientNetworkManager::ListenToServer()
{
	bool finished = false;
	while(!finished)
	{
		zmq::message_t message(NX_MAX_PACKET_SIZE);

		int rc;
		rc = m_ServerListener->recv(&message, ZMQ_NOBLOCK);

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

void nxClientNetworkManager::VTick()
{
	ListenToServer();
}

void nxClientNetworkManager::SendToAllSubscribers(nxPacketPtr packet)
{
	zmq::message_t msg (packet->VGetSize());

	cout <<"packet->VGetSize() is :" << packet->VGetSize()<<endl;
	cout <<"packet->VGetData() is :" << packet->VGetData()<<endl;

	memcpy ((void *) msg.data(), packet->VGetData(), packet->VGetSize());
	
	string string((char*)(packet->VGetData()+sizeof(uint32_t)), packet->VGetSize()-sizeof(uint32_t));
	cout<<"SENDING string :" <<string<<endl;
	cout<<"SENDING size:"<<ntohl( (uint32_t)*((uint32_t*)packet->VGetData()))<<endl;

	m_Publisher->send (msg);

	log(NX_LOG_DEBUG, "sending message to subscribers...");
}
