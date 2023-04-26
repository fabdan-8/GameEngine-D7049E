cmake_minimum_required (VERSION 3.10)
# project(GameEngine-D7049E)

# 11 required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME 0_main)
set(SDL2STUFF SDL2 SDL2_image SDL2_mixer SDL2main SDL2_net)

if (WIN32)
    include_directories(libraries/include)
    find_library(libraries/lib  ${SDL2STUFF})
    link_directories(libraries/lib)
endif()
# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)
# find_package(SDL2 REQUIRED)
 
# add the source files as usual
add_executable(${PROJECT_NAME} "src/main.cpp" "src/Game.cpp" "src/Scene.cpp" "src/Entity.cpp" "src/Map.cpp" "src/Chunk.cpp" "src/Player.cpp" "src/UI.cpp" "src/Global.h")
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(${PROJECT_NAME} OgreMain OgreBites OgreRTShaderSystem OgreMeshLodGenerator OgreOverlay ${SDL2STUFF})

if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            C:/projects/ogre-bsrh7/build/sdk/bin
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/dll/
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/sound/
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/mesh/
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/mesh)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.cfg
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/ogre.cfg
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#add_executable(1_FirstScene BasicTutorial1.cpp)
#target_link_libraries(1_FirstScene OgreBites)

