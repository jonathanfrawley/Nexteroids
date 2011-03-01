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
#ifndef  NXGAMESTATE_H
#define  NXGAMESTATE_H

//Game State type
enum nxGameState
{
	NX_GS_Initializing,
	NX_GS_MainMenu,
	NX_GS_WaitingForPlayers,
	NX_GS_LoadingGameEnvironment,
	NX_GS_LoadedLevel00,
	NX_GS_SpawnAI,
	NX_GS_Running
};

#endif   // NXGAMESTATE_H
