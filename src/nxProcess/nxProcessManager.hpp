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
#ifndef  NXPROCESSMANAGER_H
#define  NXPROCESSMANAGER_H

#include <nxCore/nxCore.hpp>
#include <nxProcess/nxProcess.hpp>
#include <nxLog/nxLog.hpp>

// nxProcessList is a list of smart nxProcess pointers.
typedef std::list< shared_ptr<nxProcess> > nxProcessList;

/*
 * =====================================================================================
 *        Class: nxProcessManager
 *  Description:
 * =====================================================================================
 */
class nxProcessManager
{
	public:
		nxProcessManager();

		virtual ~nxProcessManager();

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  Attach
		 *  Description:  Call this to attach a process to the process manager.
		 * =====================================================================================
		 */
		void Attach( shared_ptr<nxProcess> pProcess );

		bool HasProcesses();

		bool IsProcessActive( int nType );

		void UpdateProcesses(int iDelta);

	protected:
		nxProcessList m_ProcessList;

	private:
		void Detach( shared_ptr<nxProcess> pProcess );
};

#endif   // NXPROCESSMANAGER_H
