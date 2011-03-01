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
#include "jfFPSTimer.hpp"

jfFPSTimer::jfFPSTimer()
	:
		m_StartTicks(0),
		m_PausedTicks(0),
		m_IsPaused(false),
		m_IsStarted(false)
{
}

jfFPSTimer::~jfFPSTimer()
{
}


void jfFPSTimer::Start()
{
	m_IsStarted = true;
	m_IsPaused = false;
	m_StartTicks = SDL_GetTicks();
}

void jfFPSTimer::Stop()
{
	m_IsStarted = false;
	m_IsPaused = false;
}

void jfFPSTimer::Pause()
{
	if(m_IsStarted &&
			(!m_IsPaused))
	{
		m_IsPaused = true;
		m_PausedTicks = SDL_GetTicks() - m_StartTicks;
	}
}

void jfFPSTimer::UnPause()
{
}

int jfFPSTimer::GetTicks()
{
	if(m_IsStarted)
	{
		if(m_IsPaused)
		{
			return m_PausedTicks;
		}
		else
		{
			return SDL_GetTicks() - m_StartTicks;
		}
	}
	else
	{
		return 0;
	}
}
