cmake_minimum_required(VERSION 2.8)

Project ( Nexteroids )

set(CMAKE_CXX_FLAGS "-g -Wall")

### Set include dirs
if(WIN32)
	INCLUDE_DIRECTORIES(./ ../lib/SDL/include)
	LINK_DIRECTORIES(../lib/SDL/lib)
else()
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	INCLUDE_DIRECTORIES(./)
	INCLUDE_DIRECTORIES(/usr/include/SDL)
endif()

if(WIN32)
	SET(jf_common_client_lib sdl sdlmain sdl_net)
else()
	SET(jf_common_client_lib SDL SDL_net GL GLU)
endif()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(/usr/include/freetype2)

#FIND_PACKAGE(Boost COMPONENTS program_options unit_test_framework system filesystem thread REQUIRED)
FIND_PACKAGE(Boost COMPONENTS program_options system filesystem thread REQUIRED)
FIND_PACKAGE ( SDL REQUIRED )

SET(libNxThirdParty ftgl Box2D zmq guichan_sdl guichan_opengl guichan GL GLU SDL_image SDL_mixer ${SDL_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY}  ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} )

#Make Libraries
FILE(GLOB nxActor_cpp "./nxActor/*.cpp")
FILE(GLOB nxGameApp_cpp "./nxGameApp/*.cpp")
FILE(GLOB nxGameLogic_cpp "./nxGameLogic/*.cpp")
FILE(GLOB nxGameView_cpp "./nxGameView/*.cpp")
FILE(GLOB nxEvent_cpp "./nxEvent/*.cpp")
FILE(GLOB nxNet_cpp "./nxNet/*.cpp")
FILE(GLOB nxProcess_cpp "./nxProcess/*.cpp")
FILE(GLOB nxRandom_cpp "./nxRandom/*.cpp")
FILE(GLOB nxConfig_cpp "./nxConfig/*.cpp")
FILE(GLOB nxGeom_cpp "./nxGeom/*.cpp")
FILE(GLOB nxPhysics_cpp "./nxPhysics/*.cpp")
FILE(GLOB jfTimer_cpp "./jfTimer/*.cpp")

ADD_LIBRARY(libNxCore ${nxPhysics_cpp} ${nxActor_cpp} ${nxGeom_cpp} ${nxConfig_cpp} ${nxGameView_cpp} ${nxGameApp_cpp} ${nxProcess_cpp} ${nxGameLogic_cpp} ${nxEvent_cpp} ${nxNet_cpp} ${nxRandom_cpp} ${jfTimer_cpp})
TARGET_LINK_LIBRARIES(libNxCore ${libNxThirdParty})

FILE(GLOB nxMain_cpp "nxClient/nxMain/*.cpp")
ADD_EXECUTABLE(nxMain ${nxMain_cpp})
TARGET_LINK_LIBRARIES(nxMain libNxCore ${libNxThirdParty})
