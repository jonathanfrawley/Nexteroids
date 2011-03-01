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
#ifndef  NXNEWGAMEMENUITEM_H
#define  NXNEWGAMEMENUITEM_H

#include <nxGameView/nxMenuItem.hpp>
#include <nxEvent/nxEventManager.hpp>
#include <nxEvent/nxRequestNewGameEventData.hpp>

class nxNewGameMenuItem : public nxMenuItem
{
    public:
        nxNewGameMenuItem(std::string name);

        ~nxNewGameMenuItem();

        virtual void mousePressed (gcn::MouseEvent &mouseEvent);

};

#endif   // NXNEWGAMEMENUITEM_H
