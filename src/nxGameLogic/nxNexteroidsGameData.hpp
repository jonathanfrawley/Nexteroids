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
#ifndef  NXNEXTEROIDSGAMEDATA_H
#define  NXNEXTEROIDSGAMEDATA_H

/*
 * =====================================================================================
 *        Class: nxNexteroidsGameData
 *  Description: Data stored for game.
 * =====================================================================================
 */
class nxNexteroidsGameData
{
	public:
		nxNexteroidsGameData()
		{
		}

		virtual ~nxNexteroidsGameData()
		{
		}

		int GetScore(nxActorId id)
		{
			return m_ActorScores[id];
		}

		void UpdateScore(nxActorId id, int score)
		{
			m_ActorScores[id] = score;
		}


	protected:
		map<nxActorId, int> m_ActorScores;
	private:
};

#endif   // NXNEXTEROIDSGAMEDATA_H
