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

#ifndef  NXMENUSCREEN_H
#define  NXMENUSCREEN_H

#include <string>
#include <vector>

#include <guichan.hpp>

#include <nxCore/nxCore.hpp>
#include <nxGameView/nxIScreen.hpp>
#include <nxGameView/nxMenuItem.hpp>
#include <nxGameView/nxNewGameMenuItem.hpp>
#include <nxGameView/nxLabel.hpp>

const int NX_MENU_TITLE_X = 10;
const int NX_MENU_TITLE_Y = 10;

const int NX_MENU_LEFT_OFFSET = 20;
const int NX_MENU_TOP_OFFSET = 80;
const int NX_MENU_BETWEEN_OFFSET = 5;

const std::string NX_BACKGROUND_FILENAME("../../media/images/menu_background.png");

/*
 * =====================================================================================
 *        Class: nxMenuScreen
 *  Description:
 * =====================================================================================
 */
class nxMenuScreen : public nxIScreen
{
	public:
		nxMenuScreen();

		virtual ~nxMenuScreen();

		virtual void Init();

		virtual void VOnUpdate(int deltaMilliseconds);

		virtual void VOnRender();

	protected:
		gcn::Gui* m_pGui;
		gcn::Container* m_TopContainer;
        int m_NMenuItems;
		std::vector<nxMenuItem*> m_MenuItems;
		nxLabel* m_TitleLabel;
	    gcn::Icon* m_BackgroundIcon;


	private:
};

#endif   // NXMENUSCREEN_H
