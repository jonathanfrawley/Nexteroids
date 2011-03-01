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
#include "nxLoadingScreen.hpp"
#include <nxGameApp/nxGameApp.hpp>
#include <nxGameApp/nxNexteroidsGameApp.hpp>

nxLoadingScreen::nxLoadingScreen()
{
	m_pGui = nxNexteroidsGameApp::GetInstance().VGetGui();
	m_TopContainer = NX_NEW gcn::Container();
    m_LoadingLabel = NX_NEW nxLabel(std::string("Loading..."));
    m_BackgroundIcon = NX_NEW gcn::Icon(NX_LOADING_FILENAME);
}

nxLoadingScreen::~nxLoadingScreen()
{
	nxNexteroidsGameApp::GetInstance().VGetTopContainer()->remove(m_TopContainer);
	NX_SAFE_DELETE(m_BackgroundIcon);
    NX_SAFE_DELETE(m_LoadingLabel);
    NX_SAFE_DELETE(m_TopContainer);
}

void nxLoadingScreen::Init()
{
	m_TopContainer->setDimension(gcn::Rectangle(0, 0, NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT));
	m_TopContainer->setOpaque(false);
	nxNexteroidsGameApp::GetInstance().VGetTopContainer()->add(m_TopContainer);

	m_LoadingLabel->setPosition(NX_LABEL_X_OFFSET, NX_LABEL_Y_OFFSET);

	m_TopContainer->add(m_BackgroundIcon);
	m_TopContainer->add(m_LoadingLabel);
}

void nxLoadingScreen::VOnUpdate(int deltaMilliseconds)
{
	m_pGui->logic();
}

void nxLoadingScreen::VOnRender()
{
	m_pGui->draw();

	SDL_GL_SwapBuffers();
}
