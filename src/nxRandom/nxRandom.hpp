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

#ifndef  NXRANDOM_H
#define  NXRANDOM_H

#include <time.h>
#include <stdlib.h>

/*
 * =====================================================================================
 *        Class: nxRandom
 *  Description: LCG based on https://secure.wikimedia.org/wikipedia/en/wiki/Linear_congruential_generator
 * =====================================================================================
 */
class nxRandom
{
	public:
		nxRandom();

		~nxRandom();

		void Randomize() 
		{ 
			m_Xn = time(NULL);
		};

		unsigned int NextRandom() 
		{ 
			return rand();
			/*
			m_Xn = (((m_A * m_Xn) + m_C) % m_M);
			return m_Xn;
			*/
		}

		float NextRandomFloat(float maximumN) 
		{ 
			//Get a number between 0 and 1 and then scale to be between 0 and maximumN
			return ((float)rand()/(float)RAND_MAX * maximumN);//((float)NextRandom() / (float) m_M) * maximumN;
		}

	protected:
		unsigned int m_Xn;
		unsigned int m_A;
		unsigned int m_M;
		unsigned int m_C;

	private:
};


#endif   // NXRANDOM_H
