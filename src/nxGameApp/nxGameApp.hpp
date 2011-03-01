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
#ifndef  NXGAMEAPP_H
#define  NXGAMEAPP_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "SDL_mixer.h"

#include <guichan.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>
#include <guichan/sdl.hpp>

#include <jfTimer/jfFPSTimer.hpp>
#include <nxConfig/nxConfig.hpp>
#include <nxCore/nxCore.hpp>
#include <nxEvent/nxEventManager.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>
#include <nxNet/nxINetworkManager.hpp>

const std::string NX_FONT_PATH = "../../media/font/techyfontbig.png";
const std::string NX_CONFIG_PATH = "../../conf/nexteroids.conf";
const int NX_SCREEN_HEIGHT = 600;
const int NX_SCREEN_WIDTH = 800;

//Capping FPS
const bool NX_CAPFPS = true;
const unsigned NX_FRAMES_PER_SECOND = 60;

/*
 * =====================================================================================
 *        Class: nxGameApp
 *  Description: Application layer which handles initialisation of window manager,
 *  graphics, sound, etc. 
 *  Also acts as the entry point for clients into the game.
 *  This serves as the base for other GameApps to inherit from.
 * =====================================================================================
 */
class nxGameApp
{
	public:

		bool Init();

		void CreateAudio();

		bool CreateWindow(int width, int height, int bpp, bool fullscreen, const std::string& title);

		void CreateGUI();

		void CreateInput();

		void VOnRender();

		void MainLoop();

		virtual void SetShuttingDown()
		{
		    m_IsFinished = true;
		}

		virtual void ToggleFullscreen()
		{
			// Works with X11 only
			SDL_WM_ToggleFullScreen(m_pScreen);
		}

		static void Shutdown() { }

		virtual void VCreateGameLogicAndGameView() { ; }

		virtual void VCreateNetworkManager() { ; }

		virtual gcn::Gui* VGetGui()
		{
			return m_Gui;
		}

		virtual gcn::SDLInput* VGetInput()
		{
			return m_Input;
		}

		virtual gcn::Container* VGetTopContainer()
		{
			return m_TopContainer;
		}

		virtual nxINetworkManager* VGetNetworkManager()
		{
			return m_NetworkManager;
		}

		void SetArgs(int argc, char* argv[])
		{
			m_Argc = argc;
			m_Argv = argv;
		}

	protected:
		nxGameApp();

		virtual ~nxGameApp();

		int m_Argc;
		char** m_Argv;

		SDL_Surface* m_pScreen;
		bool m_CapFrameRate;
        bool m_IsFinished;
		gcn::Gui* m_Gui;
		gcn::ImageFont* m_Font;
		gcn::OpenGLGraphics* m_Graphics;
		gcn::SDLInput* m_Input;
		gcn::OpenGLSDLImageLoader* m_ImageLoader;
		gcn::Container* m_TopContainer;

		nxBaseGameLogic* m_GameLogic;
		jfFPSTimer m_FpsTimer;
		nxConfig* m_Config;
		nxINetworkManager* m_NetworkManager;
		Mix_Music *m_Music;
	private:
};

#endif   // NXGAMEAPP_H
