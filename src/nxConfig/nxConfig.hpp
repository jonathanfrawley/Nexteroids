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
#ifndef  NXCONFIG_H
#define  NXCONFIG_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

#include <nxCore/nxCore.hpp>

using namespace std;


enum nxConfigEntryType
{
	NX_CONFIG_IS_CLIENT,
	NX_CONFIG_N_NET_PLAYERS,
	NX_CONFIG_MY_IP,
	NX_CONFIG_CLIENT_LISTEN_ADDR,
	NX_CONFIG_CLIENT_SERVER_ADDR,
	NX_CONFIG_SERVER_CLIENT_IPS,
	NX_CONFIG_SERVER_LISTEN_ADDR
};

/*
 * =====================================================================================
 *        Class: nxConfig
 *  Description: Encapsulates configuration information.
 * =====================================================================================
 */
class nxConfig
{
	public:
		nxConfig(std::string filename);

		virtual ~nxConfig();

		bool GetBool(nxConfigEntryType entryType);

		int GetInt(nxConfigEntryType entryType);

		string GetString(nxConfigEntryType entryType);

		vector<string> GetVector(nxConfigEntryType entryType);

		/* 
		 * ===  FUNCTION  ======================================================================
		 *         Name:  ParseOptions
		 *  Description:  Parses options from both config file and command line.
		 * =====================================================================================
		 */
		void ParseOptions(int ac, char** argv);
		
	protected:
		std::string m_Filename;
		std::string m_ClientListenAddr;
		std::string m_ClientServerAddr;
		vector<string> m_ServerClientIps;
		std::string m_ServerListenAddr;
		bool m_IsClient;
		int m_NNetPlayers;
		string m_Ip;
	private:
};


#endif   // NXCONFIG_H
