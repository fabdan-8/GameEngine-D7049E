cmake_minimum_required (VERSION 3.10)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 11)

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
 
# add the source files as usual
add_executable(0_main src/main.cpp)
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(0_main OgreBites)

#add_executable(1_FirstScene BasicTutorial1.cpp)
#target_link_libraries(1_FirstScene OgreBites)

