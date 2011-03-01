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
#ifndef  NXGAMESTATEEVENTDATA_H
#define  NXGAMESTATEEVENTDATA_H

#include <nxGameLogic/nxGameState.hpp>
#include <nxEvent/nxBaseEventData.hpp>
#include <nxEvent/nxEventType.hpp>

/*
 * =====================================================================================
 *        Class: nxGameStateEventData
 *  Description: Change in game state.
 * =====================================================================================
 */
class nxGameStateEventData : public nxBaseEventData
{
	public:
		nxGameStateEventData(nxGameState state)
			:
				nxBaseEventData()
		{
            m_EventType = NX_EVENT_GameState;
			m_State = state;
		}

		virtual ~nxGameStateEventData()
		{
		}

		nxGameStateEventData(stringstream& in)
			:
				nxBaseEventData()
		{
			m_EventType = NX_EVENT_GameState;
			int stateInt;
			in >> stateInt;
			m_State = (nxGameState)stateInt;
		}

		virtual void VSerialize(stringstream &out) const
		{
			out << (int)m_State;
		}

		nxGameState GetState()
		{
			return m_State;
		}

		virtual void Serialize(std::ostrstream out) const
		{
			out<<m_State;
		}


	protected:
		nxGameState m_State;
	private:
};


#endif   // NXGAMESTATEEVENTDATA_H
