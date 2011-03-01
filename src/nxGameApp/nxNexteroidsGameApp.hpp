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
#ifndef  NXNEXTEROIDSGAMEAPP_H
#define  NXNEXTEROIDSGAMEAPP_H

#include <string>

#include <nxCore/nxCore.hpp>
#include <nxGameApp/nxGameApp.hpp>
#include <nxGameView/nxNexteroidsGameView.hpp>
#include <nxGameLogic/nxNexteroidsGameLogic.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxNexteroidsGameApp
 *  Description: Entry point for nexteroids game. Handles game specific init such as 
 *  network.
 * =====================================================================================
 */
class nxNexteroidsGameApp : public nxGameApp
{
	public:
		static nxNexteroidsGameApp& GetInstance();

		virtual void VCreateGameLogicAndGameView();

		virtual void VCreateNetworkManager();

		unsigned ConvertIpStringToUInt(string ip);

		virtual void ListenForNexteroidsViewCommands(nxEventListenerPtr listener);

		virtual void ListenForNexteroidsGameCommands(nxEventListenerPtr listener);

	protected:
		static nxNexteroidsGameApp m_Instance;

		nxNexteroidsGameApp();

		virtual ~nxNexteroidsGameApp();
	private:
};

#endif   // NXNEXTEROIDSGAMEAPP_H
