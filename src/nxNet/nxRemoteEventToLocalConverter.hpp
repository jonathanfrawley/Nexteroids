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
#ifndef  NXREMOTEEVENTTOLOCALCONVERTER_H
#define  NXREMOTEEVENTTOLOCALCONVERTER_H

#include <netinet/in.h>
#include <sstream>

#include <nxNet/nxIPacket.hpp>

#include <nxEvent/nxGameStateEventData.hpp>
#include <nxEvent/nxRequestNewActorEventData.hpp>
#include <nxEvent/nxNewActorEventData.hpp>
#include <nxEvent/nxThrustEventData.hpp>
#include <nxEvent/nxSteerEventData.hpp>
#include <nxEvent/nxFireWeaponEventData.hpp>
#include <nxEvent/nxPhysCollisionEventData.hpp>
#include <nxEvent/nxActorDeathEventData.hpp>
#include <nxEvent/nxActorMovedEventData.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxRemoteEventToLocalConverter
 *  Description: Deserialises events from network and queues them in local event manager.
 * =====================================================================================
 */
class nxRemoteEventToLocalConverter
{
	public:
		nxRemoteEventToLocalConverter();

		virtual ~nxRemoteEventToLocalConverter();

		void ConvertAndQueuePacket(nxPacketPtr packet);

	protected:
	private:
};

#endif   // NXREMOTEEVENTTOLOCALCONVERTER_H
