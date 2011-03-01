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
#ifndef  NXEVENTTYPE_H
#define  NXEVENTTYPE_H

enum nxEventType
{
	NX_EVENT_GlobalListenerType,
	NX_EVENT_RequestNewGame,
	NX_EVENT_NewActor,
	NX_EVENT_RequestNewActor,
	NX_EVENT_LoadingGame,
	NX_EVENT_GameState,
	NX_EVENT_Thrust,
	NX_EVENT_Steer,
	NX_EVENT_FireWeapon,
	NX_EVENT_PhysCollision,
	NX_EVENT_ActorDeath,
	NX_EVENT_ActorMoved,
	NX_EVENT_RemoteClient,
	//XXX: Remove these? Not needed anymore?
	NX_EVENT_Null,
	NX_EVENT_Endsentinal
};

#endif   // NXEVENTTYPE_H
