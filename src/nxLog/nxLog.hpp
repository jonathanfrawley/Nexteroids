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
#ifndef  NXLOG_H
#define  NXLOG_H

#include <iostream>
#include <strstream>
using namespace std;

//#define DEBUG
//#define ERROR

enum NX_LOG_LEVEL
{
	NX_LOG_DEBUG
	, NX_LOG_WARN
	, NX_LOG_ERROR
};

inline void log(NX_LOG_LEVEL logLevel, std::string str)
{
	switch(logLevel)
	{
		case NX_LOG_DEBUG:
		{
#ifdef DEBUG
			cout<<"DEBUG:"<<str<<endl;	
			cout.flush();
#endif   //DEBUG

			break;
		}
		case NX_LOG_ERROR:
		{
#ifdef ERROR
			cout<<"ERROR:"<<str<<endl;	
			cout.flush();
#endif   //ERROR
			break;
		}

	}
}

#endif   // NXLOG_H
