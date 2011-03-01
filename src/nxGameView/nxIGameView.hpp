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
#ifndef  NXIGAMEVIEW_H
#define  NXIGAMEVIEW_H

#include <nxCore/nxCore.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxGameView/nxIScreen.hpp>
#include <nxGameView/nxGameViewTypes.hpp>

enum nxGameViewType
{
	NX_GAMEVIEW_HUMAN,
	NX_GAMEVIEW_REMOTE,
	NX_GAMEVIEW_AI,
	NX_GAMEVIEW_RECORDER,
	NX_GAMEVIEW_OTHER
};

/*
 * =====================================================================================
 *        Class: nxIGameView
 *  Description: Interface for all views to implement.
 * =====================================================================================
 */
class nxIGameView
{
	public:

		virtual ~nxIGameView() { };

        virtual bool Init() = 0;

		virtual void VOnAttach(nxGameViewId, nxActorId aid) = 0;

		virtual void VOnRestore() = 0;

		virtual void VOnUpdate(int deltaMilliseconds) = 0;

		virtual void VOnRender()=0;

		virtual nxGameViewType VGetType()=0;

		virtual nxGameViewId VGetId() const=0;

	protected:
	private:
};

#endif   // NXIGAMEVIEW_H
