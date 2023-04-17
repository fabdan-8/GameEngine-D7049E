cmake_minimum_required (VERSION 3.10)
# project(GameEngine-D7049E)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 11)

set(SDL2STUFF SDL2 SDL2_image SDL2_mixer SDL2main SDL2_net)

if (WIN32)
    include_directories(libraries/include)
    find_library(libraries/lib  ${SDL2STUFF})
    link_directories(libraries/lib)
endif()
# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)
find_package(SDL2)
 
# add the source files as usual
add_executable(0_main src/main.cpp src/Game.cpp)
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(0_main OgreMain OgreBites OgreRTShaderSystem OgreMeshLodGenerator OgreOverlay ${SDL2STUFF})

#add_executable(1_FirstScene BasicTutorial1.cpp)
#target_link_libraries(1_FirstScene OgreBites)

