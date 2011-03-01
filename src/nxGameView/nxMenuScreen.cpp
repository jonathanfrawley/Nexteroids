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
#include "nxMenuScreen.hpp"
#include <nxGameApp/nxGameApp.hpp>
#include <nxGameApp/nxNexteroidsGameApp.hpp>

nxMenuScreen::nxMenuScreen()
{
	m_pGui = nxNexteroidsGameApp::GetInstance().VGetGui();
	m_TopContainer = NX_NEW gcn::Container();
	m_TitleLabel = NX_NEW nxLabel("Main Menu");
	//TODO:Put this in App layer.
//    m_BackgroundImage = gcn::Image::load(NX_BACKGROUND_FILENAME);
    m_BackgroundIcon = NX_NEW gcn::Icon(NX_BACKGROUND_FILENAME);
}

nxMenuScreen::~nxMenuScreen()
{
    m_pGui->focusNone();
    m_TopContainer->clear();
	nxNexteroidsGameApp::GetInstance().VGetTopContainer()->remove(m_TopContainer);
/*    for(int i = 0; i < m_MenuItems.size() ; i++)
	{
        m_TopContainer->remove(m_MenuItems[i]);
	}
  */
    NX_SAFE_DELETE(m_TopContainer);
	NX_SAFE_DELETE(m_TitleLabel);
	NX_SAFE_DELETE(m_BackgroundIcon);
//	m_BackgroundImage->free();
}

void nxMenuScreen::Init()
{
	m_TopContainer->setDimension(gcn::Rectangle(0, 0, NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT));

	nxNexteroidsGameApp::GetInstance().VGetTopContainer()->add(m_TopContainer);
	m_TopContainer->add(m_BackgroundIcon);

	m_TitleLabel->setPosition(NX_MENU_TITLE_X, NX_MENU_TITLE_Y);
	m_TopContainer->add(m_TitleLabel);

	m_MenuItems[0]->setPosition(NX_MENU_LEFT_OFFSET, NX_MENU_TOP_OFFSET);
	m_TopContainer->add(m_MenuItems[0]);

	for(int i = 1; i < m_MenuItems.size() ; i++)
	{
		m_MenuItems[i]->setPosition(NX_MENU_LEFT_OFFSET, m_MenuItems[i-1]->getHeight() + m_MenuItems[i-1]->getY() + NX_MENU_BETWEEN_OFFSET);
		m_TopContainer->add(m_MenuItems[i]);
	}
}

void nxMenuScreen::VOnUpdate(int deltaMilliseconds)
{
	m_pGui->logic();
}

void nxMenuScreen::VOnRender()
{
	m_pGui->draw();

	SDL_GL_SwapBuffers();
}
