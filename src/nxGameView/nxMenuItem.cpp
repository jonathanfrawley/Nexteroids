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
#include "nxMenuItem.hpp"

#include <nxGameApp/nxNexteroidsGameApp.hpp>

nxMenuItem::nxMenuItem(std::string str)//, nxNexteroidsGameApp* gameApp)
	:
		gcn::Button(str)
{
	// The widget needs to be focusable in order to receive key events.
	setFocusable(true);
	addKeyListener(this);
    setBaseColor(gcn::Color(0,0,0,255));
}

void nxMenuItem::keyPressed(gcn::KeyEvent& keyEvent)
{
//	std::cout << "Key pressed: " << keyEvent.getKey().getValue() << std::endl;
}

void nxMenuItem::keyReleased(gcn::KeyEvent& keyEvent)
{
//	std::cout << "Key released: " << keyEvent.getKey().getValue() << std::endl;
}

void nxMenuItem::mousePressed (gcn::MouseEvent &mouseEvent)
{
}

void nxMenuItem::draw(gcn::Graphics* g)
{
	gcn::Button::draw(g);
}


