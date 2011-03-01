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
#include "nxRemoteEventToLocalConverter.hpp"

#include <nxEvent/nxEventType.hpp>
#include <nxEvent/nxEventManager.hpp>
#include <nxEvent/nxRemoteClientEventData.hpp>

nxRemoteEventToLocalConverter::nxRemoteEventToLocalConverter()
{
}

nxRemoteEventToLocalConverter::~nxRemoteEventToLocalConverter()
{
}

void nxRemoteEventToLocalConverter::ConvertAndQueuePacket(nxPacketPtr packet)
{
	string packetString(packet->VGetData()+sizeof(uint32_t), packet->VGetSize()-sizeof(uint32_t));
	stringstream in(packetString);

	nxEventType type;
	uint32_t typeInt;
	in >> typeInt;
	type = (nxEventType)typeInt;

	if(type==NX_EVENT_RemoteClient)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxRemoteClientEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_NewActor)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxNewActorEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_ActorMoved)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxActorMovedEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_ActorDeath)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxActorDeathEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_GameState)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxGameStateEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_Thrust)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxThrustEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_Steer)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxSteerEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}
	else if(type==NX_EVENT_FireWeapon)
	{
		const nxIEventDataPtr eventPtr( NX_NEW nxFireWeaponEventData(in));
		nxEventManager::GetInstance().VQueueEvent(eventPtr);
	}

	return;
}
