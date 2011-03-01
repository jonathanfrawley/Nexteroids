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
#ifndef  NXGAMESCREEN_H
#define  NXGAMESCREEN_H

#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <FTGL/ftgl.h>

#include <nxCore/nxCore.hpp>
#include <nxCore/nxMath.hpp>
#include <nxActor/nxIActor.hpp>
#include <nxGameView/nxIScreen.hpp>

using namespace std;

/*
 * =====================================================================================
 *        Class: nxGameScreen
 *  Description: Game Screen class which shows the game being played.
 * =====================================================================================
 */
class nxGameScreen : public nxIScreen
{
	public:
		nxGameScreen();

		virtual ~nxGameScreen();

		void SetupLighting();

		virtual bool InitGL();

		virtual bool Init();

		virtual void VOnUpdate(int deltaMilliseconds);

		virtual void VOnRender();

		void VOnRenderActor(shared_ptr<nxIActor> actor);

		virtual void VAddActor(shared_ptr<nxIActor> actor)
		{
			m_Actors.push_back(actor);
		}

		virtual void AddToScore(int val)
		{
			m_Score += val;
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
		}

		//Convenience functions
		void DrawBox(nxReal halfSize);

		void DrawPoints(vector<nxPoint3> points);
		
	protected:
		bool m_RenderDebug;
		vector<shared_ptr<nxIActor> > m_Actors;
		GLint m_ShipList;

		int m_Score;
		FTGLPixmapFont* m_Font;

	private:
};

#endif   // NXGAMESCREEN_H
