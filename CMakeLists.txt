cmake_minimum_required(VERSION 3.19)
project(Block_Game)

# GlUT: https://www.cs.uregina.ca/Links/class-info/315/WWW/Lab1/GLUT/windows.html
# Configuration:
#   https://stackoverflow.com/questions/44335620/cmake-cant-find-freeglut-3-0-0
#   https://stackoverflow.com/a/9469349/12347616

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# Suppress ZERO_CHECK files
#   https://stackoverflow.com/a/27175822/12347616
set(CMAKE_SUPPRESS_REGENERATION true)

add_executable(${PROJECT_NAME} src/main.cpp src/utils/PrintUtils.h src/game/Board.cpp src/game/Board.h src/game/Config.cpp src/game/Config.h src/game/Block.cpp src/game/Block.h src/utils/MathUtils.cpp src/utils/MathUtils.h src/game/DrawColor.cpp src/game/DrawColor.h src/game/Shapes.cpp src/game/Shapes.h src/game/State.h src/utils/tga.cpp src/utils/tga.h src/game/Logo.cpp src/game/Logo.h src/game/MyTexture.cpp src/game/MyTexture.h)
set(OPENGL_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/dependencies/freeglut/lib/x64)
#set(GLUT_glut_LIBRARY ${PROJECT_SOURCE_DIR}/dependencies/freeglut/lib/x64)
set(GLUT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/freeglut/bin/x64)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#include_directories(dependencies)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/freeglut/include)
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT)

# Copy dll to output directory
#    https://stackoverflow.com/a/10672739/12347616
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/dependencies/freeglut/bin/x64/freeglut.dll" ${CMAKE_BINARY_DIR})
#Copy Images to output
#https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/myimages ${CMAKE_BINARY_DIR})