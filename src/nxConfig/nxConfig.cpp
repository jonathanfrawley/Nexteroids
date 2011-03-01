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
#include "nxConfig.hpp"

nxConfig::nxConfig(std::string filename)
{
	m_Filename = filename;
}

nxConfig::~nxConfig()
{
}

void nxConfig::ParseOptions(int argc, char** argv)
{
	namespace po = boost::program_options;

	po::options_description desc;
	desc.add_options()
		("help", "produce help message")
		("clientOrServer", po::value<string>(), "\'c\' for client, \'s\' for server.")
		("nNetPlayers", po::value<int>(), "Number of network players")
		("myIp", po::value<string>(), "Client IP Address")
		("clientListenAddr", po::value<string>(), "Local listen address for clients.")
		("clientServerAddr", po::value<string>(), "Address for server client to connect to.")
		("serverClientIps", po::value<vector<string> >(), "IPs of clients to connect to for incoming events.")
		("serverListenAddr", po::value<string>(), "Address for clients to connect to.")
		;

	po::variables_map vm;
	std::ifstream inputFile( m_Filename.c_str() ); 
	if ( !inputFile )
	{
		cout << "Error:  Cannot open file " << m_Filename << endl;
		exit( 1 );
	} 
	store(po::parse_config_file(inputFile, desc), vm);
	notify(vm);

	log(NX_LOG_ERROR,std::string("clientOrServer"));
	if (vm.count("clientOrServer"))
	{
		log(NX_LOG_DEBUG,std::string("clientOrServer"));
		cout << "clientOrServer: "
			<< vm["clientOrServer"].as< string >() << "\n";
		if(vm["clientOrServer"].as< string >().c_str()[0] == 'c')
		{
			m_IsClient = true;
		}
		else
		{
			m_IsClient = false;
		}
	}

	if(vm.count("nNetPlayers"))
	{
		m_NNetPlayers = vm["nNetPlayers"].as< int >();
		cout<<"m_NNetPlayers is " << m_NNetPlayers<<endl;
	}

	if(vm.count("myIp"))
	{
		m_Ip = vm["myIp"].as< string >();
	}

	if(vm.count("clientListenAddr"))
	{
		m_ClientListenAddr = vm["clientListenAddr"].as< string >();
	}

	if(vm.count("clientServerAddr"))
	{
		m_ClientServerAddr = vm["clientServerAddr"].as< string >();
	}

	if(vm.count("serverClientIps"))
	{
		m_ServerClientIps = vm["serverClientIps"].as< vector<string> >();
	}

	if(vm.count("serverListenAddr"))
	{
		m_ServerListenAddr = vm["serverListenAddr"].as< string >();
	}

	//Now command line options override config file
	po::variables_map vmCmdLine;
	store(po::parse_command_line(argc, argv, desc), vmCmdLine);
	if (vmCmdLine.count("clientOrServer"))
	{
		log(NX_LOG_DEBUG,std::string("clientOrServer"));
		cout << "clientOrServer: "
			<< vmCmdLine["clientOrServer"].as< string >() << "\n";
		if(vmCmdLine["clientOrServer"].as< string >().c_str()[0] == 'c')
		{
			m_IsClient = true;
		}
		else
		{
			m_IsClient = false;
		}
	}
}

string nxConfig::GetString(nxConfigEntryType entryType)
{
	switch(entryType)
	{
		case NX_CONFIG_MY_IP:
			return m_Ip;
		case NX_CONFIG_CLIENT_LISTEN_ADDR:
			return m_ClientListenAddr;
		case NX_CONFIG_CLIENT_SERVER_ADDR:
			return m_ClientServerAddr;
		case NX_CONFIG_SERVER_LISTEN_ADDR:
			return m_ServerListenAddr;
		default:
			assert(0 && "No entry type");
	}
}
		
vector<string> nxConfig::GetVector(nxConfigEntryType entryType)
{
	switch(entryType)
	{
		case NX_CONFIG_SERVER_CLIENT_IPS:
			return m_ServerClientIps;
		default:
			assert(0 && "No entry type");
	}
}

bool nxConfig::GetBool(nxConfigEntryType entryType)
{
	switch(entryType)
	{
		case NX_CONFIG_IS_CLIENT:
			return m_IsClient;
		default:
			assert(0 && "No entry type");
	}
}

int nxConfig::GetInt(nxConfigEntryType entryType)
{
	switch(entryType)
	{
		case NX_CONFIG_N_NET_PLAYERS:
			return m_NNetPlayers;
		default:
			assert(0 && "No entry type");
	}
}
