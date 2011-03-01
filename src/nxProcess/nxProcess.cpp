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
#include "nxProcess.hpp"

nxProcess::nxProcess(int ntype) :
	m_iType(ntype)
	, m_bIsDead( false )
	, m_bIsActive( true )
	, m_bIsPaused( false )
	, m_bIsInit( false )
	, m_pNext(shared_ptr<nxProcess>((nxProcess *)NULL))
{
}

nxProcess::~nxProcess()
{
}

void nxProcess::VOnUpdate( const int deltaMilliseconds )
{
	if ( ! m_bIsInit )
	{
		VOnInit();
		m_bIsInit = true;
	}
}
