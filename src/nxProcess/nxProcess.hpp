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
#ifndef  NXPROCESS_H
#define  NXPROCESS_H

#include <boost/noncopyable.hpp>

#include <nxCore/nxCore.hpp>

enum NX_PROCESS_TYPE
{
	NX_PROC_NONE
	, NX_PROC_WAIT
	, NX_PROC_DEBUG
};

class nxProcess : boost::noncopyable
{
	//TODO:Remove this friend def?
	//friend class nxProcessManager;

	public:
		nxProcess(int ntype);

		virtual ~nxProcess();

		// Overloadables
		virtual void VOnUpdate( const int deltaMilliseconds );

		virtual void VOnInit() { };

		virtual void VKill() { m_bIsDead = true; };

		virtual void VTogglePause() { m_bIsPaused = !m_bIsPaused; };

		/*-----------------------------------------------------------------------------
		 *  Getters and Setters
		 *-----------------------------------------------------------------------------*/
		bool IsDead(void) const { return(m_bIsDead); };

		int GetType(void) const { return(m_iType); };

		void SetType(const int val) { m_iType = val; };

		bool IsActive(void) const { return m_bIsActive; };

		void SetActive(const bool b) { m_bIsActive = b; };

		bool IsAttached() const { return m_bIsAttached; };

		void SetAttached(const bool wantAttached) { m_bIsAttached = wantAttached; };

		bool IsPaused(void) const { return m_bIsPaused; };

		bool IsInit() const { return m_bIsInit; };

		shared_ptr<nxProcess> const GetNext(void) const { return(m_pNext); };

		void SetNext( shared_ptr<nxProcess> next ) { m_pNext = next; };

	protected:
		int	m_iType; // type of process running
		bool m_bIsDead; // tells manager to kill and remove
		bool m_bIsActive;
		bool m_bIsPaused;
		bool m_bIsInit;
		bool m_bIsAttached;
		shared_ptr<nxProcess> m_pNext; // dependant process

	private:
		//TODO : Remove this?
		//unsigned int m_uProcessFlags;
};

#endif   // NXPROCESS_H
