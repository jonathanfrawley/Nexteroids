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
#ifndef  NXNEXTEROIDSGAMEVIEW_H
#define  NXNEXTEROIDSGAMEVIEW_H

#include "SDL_mixer.h"

#include <nxCore/nxCore.hpp>
#include <nxGameView/nxHumanView.hpp>
#include <nxGameView/nxLoadingScreen.hpp>
#include <nxGameView/nxGameScreen.hpp>
#include <nxEvent/nxThrustEventData.hpp>
#include <nxEvent/nxSteerEventData.hpp>
#include <nxEvent/nxFireWeaponEventData.hpp>

/*
 * =====================================================================================
 *        Class: nxNexteroidsGameView
 *  Description:
 * =====================================================================================
 */
class nxNexteroidsGameView : public nxHumanView
{
	public:
		nxNexteroidsGameView();

		virtual ~nxNexteroidsGameView();

		bool Init();

		void ShowLoadingScreen();
		
        void ListenForNexteroidsGameViewEvents();

		void BuildInitialLevel00();

		virtual void VHandleKeyboardCommands(SDL_Event event);

		virtual void VAddActor(shared_ptr<nxIActor> actor)
		{
			m_Actors.push_back(actor);
			
			nxScreenList::iterator it, itEnd;
			for(it = m_Screens.begin(), itEnd = m_Screens.end() ; it != itEnd ; it++)
			{
				(*it)->VAddActor(actor);
			}
		}

		virtual void VRemoveActor(nxActorId aid)
		{
			vector<shared_ptr<nxIActor> >::iterator it, itEnd;
			for(it=m_Actors.begin(), itEnd = m_Actors.end() ; it!=itEnd; it++)
			{
				if((*it)->VGetId() == aid)
				{
					m_Actors.erase(it);
				}
			}
			nxScreenList::iterator itScreen, itScreenEnd;
			for(itScreen = m_Screens.begin(), itScreenEnd = m_Screens.end() ; itScreen != itScreenEnd ; itScreen++)
			{
				(*itScreen)->VRemoveActor(aid);
			}
		}

		virtual void VMoveActor(nxActorId aid, nxPoint3 pos, nxReal orientation)
		{
			vector<shared_ptr<nxIActor> >::iterator it, itEnd;
			for(it=m_Actors.begin(), itEnd = m_Actors.end() ; it!=itEnd; it++)
			{
				if((*it)->VGetId() == aid)
				{
					(*it)->VSetPos(pos);
					(*it)->VSetOrientation(orientation);
				}
			}
			nxScreenList::iterator itScreen, itScreenEnd;
			for(itScreen = m_Screens.begin(), itScreenEnd = m_Screens.end() ; itScreen != itScreenEnd ; itScreen++)
			{
				(*itScreen)->VMoveActor(aid, pos, orientation);
			}
		}

		virtual void VSetActor(shared_ptr<nxIActor> actor)
		{
			m_pActor = actor;
		}

		virtual shared_ptr<nxIActor> VGetActor(const nxActorId aid)
		{
			vector<shared_ptr<nxIActor> >::iterator it, itEnd;
			for(it=m_Actors.begin(), itEnd = m_Actors.end() ; it!=itEnd; it++)
			{
				if((*it)->VGetId() == aid)
				{
					return (*it);
				}
			}

			shared_ptr<nxIActor> null;
			return null;
		}

		void AddToScore(int val)
		{
			nxScreenList::iterator itScreen, itScreenEnd;
			for(itScreen = m_Screens.begin(), itScreenEnd = m_Screens.end() ; itScreen != itScreenEnd ; itScreen++)
			{
				(*itScreen)->AddToScore(val);
			}
		}

		void PlaySound();

		void PlayRockDeathSound();

		void PlaySpaceshipDeathSound();

		void SetViewActorIdInvalid()
		{
			m_ActorValid = false;
		}

		nxActorId GetViewActorId()
		{
			if(!m_ActorValid)
			{
				return -1;
			}
			else
			{
				if(m_pActor)
				{
					return m_pActor->VGetId();
				}
				else
				{
					assert(0);
				}
			}
		}

		void PlayFireBulletSound();

	protected:
        nxEventListenerPtr m_EventListener;
		vector<shared_ptr<nxIActor> > m_Actors;
		shared_ptr<nxIActor> m_pActor;
		bool m_WAlreadyPressed;
		bool m_SAlreadyPressed;
		bool m_AAlreadyPressed;
		bool m_DAlreadyPressed;
		bool m_SpaceAlreadyPressed;

		Mix_Chunk *m_Explosion;
		Mix_Chunk *m_Laser;
		bool m_ActorValid;


	private:
};


#endif   // NXNEXTEROIDSGAMEVIEW_H
