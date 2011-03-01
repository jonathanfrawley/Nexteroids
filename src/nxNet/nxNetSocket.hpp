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
#ifndef  NXNETSOCKET_H
#define  NXNETSOCKET_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <nxCore/nxCore.hpp>
#include <nxNet/nxIPacket.hpp>

using boost::asio::ip::tcp;

const int NX_MAX_PACKET_SIZE = 1024;
const int NX_RECV_BUFFER_SIZE = (NX_MAX_PACKET_SIZE * 512);

typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef std::list< shared_ptr <nxIPacket> > nxPacketList;

/*
 * =====================================================================================
 *        Class: nxNetSocket
 *  Description: Socket 
 * =====================================================================================
 */
class nxNetSocket
{
	public:
		nxNetSocket();

		nxNetSocket(socket_ptr new_sock, unsigned int hostIP);

		virtual ~nxNetSocket();

		bool Connect(unsigned int ip, unsigned int port, int
fCoalesce = 0);

		void SetBlocking(int block);

		void Send(shared_ptr<nxIPacket> pkt, bool clearTimeOut=1);
		
		virtual HasOutput() { return ! m_OutList.empty(); }

		virtual HandleOutput();

		virtual HandleInput();

		virtual TimeOut() { m_timeOut=0; }

		void HandleException() { m_deleteFlag |= 1; }

		void SetTimeOut(int ms=45*1000) { m_timeOut = timeGetTime() + ms; }
		
	protected:
		socket_ptr m_Socket;
		int m_Id;
		nxPacketList m_OutList;
		nxPacketList m_InList;
		char m_RecvBuf[NX_RECV_BUFFER_SIZE];
		bool m_bBinaryProtocol;
		int m_SendOfs;
		unsigned int m_TimeOut;
		unsigned int m_Ip; 
		int m_TimeCreated; 

//		int m_IsInternal;  ///TODO
///		int m_DeleteFlag; ///TODO
//		unsigned int m_recvOfs, m_recvBegin;




	private:
};


#endif   // NXNETSOCKET_H
