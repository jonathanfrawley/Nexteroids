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
#include "nxNetworkEventForwarder.hpp"

#include <nxGameApp/nxNexteroidsGameApp.hpp>


nxNetworkEventForwarder::nxNetworkEventForwarder()
{
}

nxNetworkEventForwarder::~nxNetworkEventForwarder()
{
}


bool nxNetworkEventForwarder::HandleEvent( nxIEventData const & event )
{
	log(NX_LOG_DEBUG, "forwarding event to network manager...");
	stringstream out;

//	out << static_cast<int>(RemoteEventSocket::NetMsg_Event) << " ";
//	out << event.getType().getStr() << " ";

//	out << static_cast<int>(event.VGetEventType()) << " ";

	out << static_cast<uint32_t>(event.VGetEventType()) << " ";
	event.VSerialize(out);

	out << "\n";
	shared_ptr<nxBinaryPacket> eventMsg(
			NX_NEW nxBinaryPacket(out.str().c_str(), out.str().size()));

	/*
	cout <<"sending:";
	cout << out.rdbuf()->str() <<endl;
	cout <<"sending size:";
	cout << out.pcount() <<endl;
	*/

	nxNexteroidsGameApp::GetInstance().VGetNetworkManager()->SendToAllSubscribers(eventMsg);
	return true;
}
