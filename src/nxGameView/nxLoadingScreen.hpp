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
#ifndef  NXLOADINGSCREEN_H
#define  NXLOADINGSCREEN_H

#include <guichan.hpp>

#include <nxGameView/nxIScreen.hpp>
#include <nxGameView/nxLabel.hpp>

const int NX_LABEL_X_OFFSET = 20;
const int NX_LABEL_Y_OFFSET = 20;
const std::string NX_LOADING_FILENAME("../../media/images/loading_background.png");

/*
 * =====================================================================================
 *        Class: nxLoadingScreen
 *  Description:
 * =====================================================================================
 */
class nxLoadingScreen : public nxIScreen
{
	public:
		nxLoadingScreen();

		virtual ~nxLoadingScreen();

		virtual void Init();

		virtual void VOnUpdate(int deltaMilliseconds);

		virtual void VOnRender();
	protected:
		gcn::Gui* m_pGui;
		gcn::Container* m_TopContainer;
		nxLabel* m_LoadingLabel;
	    gcn::Icon* m_BackgroundIcon;
	private:
};


#endif   // NXLOADINGSCREEN_H
