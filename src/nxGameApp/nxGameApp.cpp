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
#include "nxGameApp.hpp"

#include <nxProcess/nxProcessManager.hpp>
#include <nxProcess/nxWaitProcess.hpp>
#include <nxProcess/nxDebugProcess.hpp>

nxGameApp::nxGameApp()
{
	m_CapFrameRate = true;
	m_IsFinished = false;
}

nxGameApp::~nxGameApp()
{
	NX_SAFE_DELETE(m_GameLogic)

	NX_SAFE_DELETE(m_Gui);
	NX_SAFE_DELETE(m_ImageLoader);
	NX_SAFE_DELETE(m_Input);
	NX_SAFE_DELETE(m_Graphics);
	NX_SAFE_DELETE(m_Config);

	Mix_FreeMusic( m_Music );

	SDL_Quit();
}

bool nxGameApp::Init()
{
	m_Config = NX_NEW nxConfig(std::string(NX_CONFIG_PATH));
	m_Config->ParseOptions(m_Argc, m_Argv);

	if (! CreateWindow(NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, 32, false, "neXteroids"))
	{
		return false;
	}
	CreateInput();

	CreateGUI();

	m_FpsTimer.Start();

	VCreateGameLogicAndGameView();

	VCreateNetworkManager();

	CreateAudio();

	return true;
}

void nxGameApp::CreateAudio()
{
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
	{ 
		assert(0 && "Couldn't init audio");
	}
	m_Music = Mix_LoadMUS( "../../media/sounds/beat.wav" ); 
}

bool nxGameApp::CreateWindow(int width, int height, int bpp, bool fullscreen, const std::string& title)
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//all values are "at least"!
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set the title.
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	// Flags tell SDL about the type of window we are creating.
	int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWSURFACE | SDL_OPENGLBLIT | SDL_HWPALETTE;

	if(fullscreen)
	{
		flags |= SDL_FULLSCREEN;
	}

	// Create the window
	m_pScreen = SDL_SetVideoMode( width, height, bpp, flags );

    if ( m_pScreen == NULL )
	{
        fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",width,height,bpp,SDL_GetError());
        exit(1);
    }

    SDL_FillRect(m_pScreen, NULL, SDL_MapRGBA(m_pScreen->format,0,0,0,0));

	//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = width;
	resizeEvent.resize.h = height;

	SDL_PushEvent(&resizeEvent);
	return true;
}

void nxGameApp::CreateGUI()
{
	try
	{
		m_ImageLoader = new gcn::OpenGLSDLImageLoader();
		gcn::Image::setImageLoader(m_ImageLoader);

		m_Font = new gcn::ImageFont(NX_FONT_PATH, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");
		gcn::Widget::setGlobalFont(m_Font);
		m_Graphics = new gcn::OpenGLGraphics();
		// We need to tell the OpenGL Graphics object how big the screen is.
		m_Graphics->setTargetPlane(NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT);

		m_Gui = new gcn::Gui();

		m_Gui->setGraphics(m_Graphics);
		m_Gui->setInput(m_Input);
		m_TopContainer = new gcn::Container();    
		m_TopContainer->setDimension(gcn::Rectangle(0, 0, NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT));
		m_Gui->setTop(m_TopContainer);

	}
	catch(gcn::Exception e)
	{
		cerr<<"Gui exception on init:"<<e.getMessage()<<endl;
		cerr<<"Filename:"<<e.getFilename()<<endl;
		cerr<<"Line:"<<e.getLine()<<endl;
	}
}


void nxGameApp::CreateInput()
{
	// We want unicode for the SDLInput object to function properly.
	SDL_EnableUNICODE(1);
	// We also want to enable key repeat.
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	m_Input = new gcn::SDLInput();
}

void nxGameApp::VOnRender()
{
    nxBaseGameLogic *pGame = m_GameLogic;
    for(nxGameViewList::iterator i=pGame->GetGameViews().begin(),end=pGame->GetGameViews().end(); i!=end; ++i)
    {
        (*i)->VOnRender();
    }
}

void nxGameApp::MainLoop()
{
    while( ! m_IsFinished)
    {
		m_FpsTimer.Start();
		m_NetworkManager->VTick();
		nxEventManager::GetInstance().VTick(200);
		m_GameLogic->VOnUpdate(m_FpsTimer.GetTicks());
		VOnRender();

		if( ( NX_CAPFPS == true ) && ( m_FpsTimer.GetTicks() < 1000 / NX_FRAMES_PER_SECOND ) ) 
		{ 
			//Sleep the remaining frame time 
			SDL_Delay( ( 1000 / NX_FRAMES_PER_SECOND ) - m_FpsTimer.GetTicks() ); 
		}
    }
}
