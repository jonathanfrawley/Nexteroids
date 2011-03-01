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
#ifndef  NXCORE_H
#define  NXCORE_H

#include <list>

#include <boost/shared_ptr.hpp>

#include <nxLog/nxLog.hpp>

//#define NX_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#define NX_NEW new
#define NX_SAFE_DELETE(x) if(x) delete x; x=NULL;
#define NX_SAFE_DELETE_ARRAY(x) if (x) delete [] x; x=NULL; 

#define NX_NULL 0

using boost::shared_ptr;

#endif   // NXCORE_H
