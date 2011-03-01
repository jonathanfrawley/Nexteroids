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
#include "nxMainMenuGameView.hpp"

#include <nxEvent/nxEventManager.hpp>
#include <nxEvent/nxIEventListener.hpp>
#include <nxGameView/nxMainMenuGameViewEventListener.hpp>

nxMainMenuGameView::nxMainMenuGameView ()
	:
		nxHumanView()
{
	m_EventListener = nxEventListenerPtr (NX_NEW nxMainMenuGameViewEventListener(this));
}

nxMainMenuGameView::~nxMainMenuGameView ()
{
	while( ! m_Screens.empty())
	{
		m_Screens.pop_back();
	}
	nxEventManager::GetInstance().VDelListener(m_EventListener, NX_EVENT_GameState);
}

bool nxMainMenuGameView::Init()
{
	nxHumanView::Init();

	//TODO:Do this statefully.
	boost::shared_ptr<nxMainMenuScreen> mainMenuScreen(NX_NEW nxMainMenuScreen());
	mainMenuScreen->Init();
	m_Screens.push_back(mainMenuScreen);
	ListenForMainMenuGameViewEvents();
	return true;
}

void nxMainMenuGameView::ListenForMainMenuGameViewEvents()
{
	nxEventManager::GetInstance().VAddListener(m_EventListener, NX_EVENT_GameState);
}

void nxMainMenuGameView::VHandleKeyboardCommands(SDL_Event event)
{
	//Handle core commands to quit, etc. first 
	nxHumanView::VHandleKeyboardCommands(event);
}

void nxMainMenuGameView::ShowLoadingScreen()
{
	while( ! m_Screens.empty())
	{
		m_Screens.pop_back();
	}
	boost::shared_ptr<nxLoadingScreen> loadingScreen(NX_NEW nxLoadingScreen());
	loadingScreen->Init();
	m_Screens.push_back(loadingScreen);
}
