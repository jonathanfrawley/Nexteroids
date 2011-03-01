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
#ifndef  NXEVENTLISTENER_H
#define  NXEVENTLISTENER_H

#include <nxEvent/nxIEventListener.hpp>

/*
 * =====================================================================================
 *        Class: nxEventListener
 *  Description: Base class for all event listeners to inherit from.
 * =====================================================================================
 */
class nxEventListener : public nxIEventListener
{
	public:
		nxEventListener() {}

		virtual ~nxEventListener() {}

		virtual char const * GetName(void) = 0;

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  HandleEvent
		 *  Description:  Returns true when consumed event, false otherwise.
		 * =====================================================================================
		 */
		virtual bool HandleEvent( nxIEventData const & event ) = 0;

	protected:
	private:
};


#endif   // NXEVENTLISTENER_H
