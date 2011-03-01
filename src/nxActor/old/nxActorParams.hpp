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
#ifndef  NXACTORPARAMS_H
#define  NXACTORPARAMS_H

#include <strstream>

#include <jfpx/x86/jfVector3_x86.h>

#include <nxActor/nxIActor.hpp>
#include <nxCore/nxTypes.hpp>
#include <nxCore/nxCore.hpp>
#include <nxGameLogic/nxBaseGameLogic.hpp>

class nxActorParams
{
    public:
        nxActorParams(); 

        virtual ~nxActorParams() { }

		//To be overloaded by subclasses
//        virtual shared_ptr<nxIActor> VCreate(nxBaseGameLogic *logic) = 0;
        virtual shared_ptr<nxIActor> VCreate(nxBaseGameLogic *logic) = 0;

        virtual bool VInit(std::istrstream &in);

        virtual void VSerialize(std::ostrstream &out) const;

        //XXX: Why is this needed?
        //typedef std::deque< std::string > TErrorMessageList;
		
	private:
        /*-----------------------------------------------------------------------------
         *  Member data
         *-----------------------------------------------------------------------------*/
        int m_Size; //Size of struct
        nxActorId m_Id;
        jfVector3_x86 m_Pos;
        nxActorType m_Type;
        nxColour m_Colour;



	//TODO:Scenenode stuff	
//	virtual shared_ptr<SceneNode> VCreateSceneNode(shared_ptr<Scene> pScene) { shared_ptr<SceneNode> p; return p; }

	/* TODO : Remove unless going to use Lua
	static const int sk_MaxFuncName = 64;
	char m_OnCreateLuaFunctionName[ sk_MaxFuncName ];	//Lua function name to call for this actor, upon creation.
	char m_OnDestroyLuaFunctionName[ sk_MaxFuncName ];	//As above, but on destruction.
	virtual bool VInit( LuaObject srcData, TErrorMessageList & errorMessages );
	static ActorParams *CreateFromStream(std::istrstream &in);
	static ActorParams *CreateFromLuaObj( LuaObject srcData );
	*/


};

#endif   // NXACTORPARAMS_H
