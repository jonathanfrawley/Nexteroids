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
#ifndef  NXHUMANVIEW_H
#define  NXHUMANVIEW_H

#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <SDL.h>
#include <boost/optional/optional.hpp>

#include <nxCore/nxCore.hpp>
#include <nxGameView/nxIGameView.hpp>
#include <nxGameView/nxMenuScreen.hpp>
#include <nxGameView/nxMainMenuScreen.hpp>
#include <nxProcess/nxProcessManager.hpp>

typedef std::list<shared_ptr<nxIScreen> > nxScreenList;

/*
 * =====================================================================================
 *        Class: nxHumanView
 *  Description: View of game world for human player.
 * =====================================================================================
 */
class nxHumanView : public nxIGameView
{
	public:
		nxHumanView();

		virtual ~nxHumanView();

		bool Init();

		virtual void VOnAttach(nxGameViewId vid, nxActorId aid)
		{
			m_ViewId = vid;
			m_ActorId = aid;
		}

		virtual void VOnRestore()
		{
		    assert(1 && "Have not implemented restore");
		}

		virtual void VHandleKeyboardCommands(SDL_Event event);

		virtual void VOnUpdate(int deltaMilliseconds);

		virtual void VOnRender();

		virtual nxGameViewType VGetType()
		{
			return NX_GAMEVIEW_HUMAN;
		}

		virtual nxGameViewId VGetId() const
		{
			return m_ViewId;
		}

	protected:
		gcn::SDLInput* m_Input;
		nxGameViewId m_ViewId;
		boost::optional<nxActorId> m_ActorId;
		nxProcessManager* m_pProcessManager;
		nxScreenList m_Screens;

	private:
};


#endif   // NXHUMANVIEW_H
