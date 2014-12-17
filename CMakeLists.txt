# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(NordicEngine)

# OSX RPATH
set(CMAKE_MACOSX_RPATH 0)

# NOS Files
set(NE ${PROJECT_SOURCE_DIR}/NordicEngine)
set(LibHeaders ${NE}/Engine.hpp)
set(LibSources ${NE}/Engine.cpp)

# NOS Includes
list(APPEND LibHeaders ${NE}/Includes.hpp)

# link path
link_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# OS Specific Classes
if (WIN32)
    link_directories(${NE}/OS/Windows)
    include_directories(${NE}/OS/Windows)
    list(APPEND LibHeaders ${NE}/OS/Windows/Windows.hpp)
    list(APPEND LibSources ${NE}/OS/Windows/Windows.cpp)
else()
    # nonWindows
    link_directories(${NE}/OS/nonWindows)
    include_directories(${NE}/OS/nonWindows)
    list(APPEND LibHeaders ${NE}/OS/nonWindows/nonWindows.hpp)
    
    if (APPLE)
        # C++11
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
        set(EXTRA_FLAGS " -x objective-c++")
        link_directories(${NE}/OS/nonWindows/OSX)
        include_directories(${NE}/OS/nonWindows/OSX)
        list(APPEND LibHeaders ${NE}/OS/nonWindows/OSX/OSX.hpp)
        list(APPEND LibHeaders ${NE}/OS/nonWindows/OSX/OSX.mm)
    elseif (UNIX)
        # C++11
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -m64")
        set(EXTRA_FLAGS "")
        link_directories(${NE}/OS/nonWindows/Linux)
        include_directories(${NE}/OS/nonWindows/Linux)
        list(APPEND LibHeaders ${NE}/OS/nonWindows/Linux/Linux.hpp)
        list(APPEND LibSources ${NE}/OS/nonWindows/Linux/Linux.cpp)
    endif()
endif()

# String
link_directories(${NE}/String)
include_directories(${NE}/String)
list(APPEND LibHeaders ${NE}/String/String.hpp)
list(APPEND LibHeaders ${NE}/String/String.inl)
list(APPEND LibSources ${NE}/String/String.cpp)

# Time
link_directories(${NE}/Time)
include_directories(${NE}/Time)
list(APPEND LibHeaders ${NE}/Time/Time.hpp)
list(APPEND LibSources ${NE}/Time/Time.cpp)

# Logger
link_directories(${NE}/Logger)
include_directories(${NE}/Logger)
list(APPEND LibHeaders ${NE}/Logger/Logger.hpp)
list(APPEND LibSources ${NE}/Logger/Logger.cpp)

# Exceptions
link_directories(${NE}/Exceptions)
include_directories(${NE}/Exceptions)
list(APPEND LibHeaders ${NE}/Exceptions/Exceptions.hpp)
list(APPEND LibSources ${NE}/Exceptions/Exceptions.cpp)

# Files
link_directories(${NE}/Files)
include_directories(${NE}/Files)
list(APPEND LibHeaders ${NE}/Files/Files.hpp)
list(APPEND LibSources ${NE}/Files/Files.cpp)

# File Utils
list(APPEND LibHeaders ${NE}/Files/Utils.hpp)
list(APPEND LibSources ${NE}/Files/Utils.cpp)

# File Handler
link_directories(${NE}/Files/Handler)
include_directories(${NE}/Files/Handler)
list(APPEND LibHeaders ${NE}/Files/Handler/Handler.hpp)
list(APPEND LibSources ${NE}/Files/Handler/Handler.cpp)

# TextFile
link_directories(${NE}/Files/Handler/TextFile)
include_directories(${NE}/Files/Handler/TextFile)
list(APPEND LibHeaders ${NE}/Files/Handler/TextFile/Writer.hpp)
list(APPEND LibSources ${NE}/Files/Handler/TextFile/Writer.cpp)
list(APPEND LibHeaders ${NE}/Files/Handler/TextFile/Reader.hpp)
list(APPEND LibSources ${NE}/Files/Handler/TextFile/Reader.cpp)

# Threads
link_directories(${NE}/Threading/Threads)
include_directories(${NE}/Threading/Threads)
list(APPEND LibHeaders ${NE}/Threading/Threads/Threads.hpp)
list(APPEND LibSources ${NE}/Threading/Threads/Threads.cpp)

# Singleton
link_directories(${NE}/Threading/Singleton)
include_directories(${NE}/Threading/Singleton)
list(APPEND LibHeaders ${NE}/Threading/Singleton/Singleton.hpp)
list(APPEND LibSources ${NE}/Threading/Singleton/Singleton.cpp)

# Noise
link_directories(${NE}/Noise)
include_directories(${NE}/Noise)
list(APPEND LibHeaders ${NE}/Noise/Simplex.hpp)
list(APPEND LibSources ${NE}/Noise/Simplex.cpp)

# Storage
link_directories(${NE}/Storage)
include_directories(${NE}/Storage)
list(APPEND LibHeaders ${NE}/Storage/Storage.hpp)
list(APPEND LibSources ${NE}/Storage/Storage.cpp)

# Utilitys
link_directories(${NE}/Utility)
include_directories(${NE}/Utility)
list(APPEND LibHeaders ${NE}/Utility/Utility.hpp)
list(APPEND LibSources ${NE}/Utility/Utility.cpp)

# Window 
link_directories(${NE}/Window)
include_directories(${NE}/Window)
list(APPEND LibHeaders ${NE}/Window/Window.hpp)
list(APPEND LibSources ${NE}/Window/Window.cpp)

# Color
link_directories(${NE}/Color)
include_directories(${NE}/Color)
list(APPEND LibHeaders ${NE}/Color/Color.hpp)
list(APPEND LibSources ${NE}/Color/Color.cpp)

# Player
link_directories(${NE}/Player)
include_directorieS(${NE}/Player)
list(APPEND LibHeaders ${NE}/Player/Player.hpp)
list(APPEND LibSources ${NE}/Player/Player.cpp)

# Input
link_directories(${NE}/Input)
include_directories(${NE}/Input)
list(APPEND LibHeaders ${NE}/Input/Definitions.hpp)
list(APPEND LibHeaders ${NE}/Input/Input.hpp)
list(APPEND LibSources ${NE}/Input/Input.cpp)

# Renderer
link_directories(${NE}/Renderer)
include_directories(${NE}/Renderer)
list(APPEND LibHeaders ${NE}/Renderer/Renderer.hpp)
list(APPEND LibSources ${NE}/Renderer/Renderer.cpp)

# Shaders
link_directories(${NE}/Shaders)
include_directories(${NE}/Shaders)
list(APPEND LibHeaders ${NE}/Shaders/Shaders.hpp)
list(APPEND LibSources ${NE}/Shaders/Shaders.cpp)

# SQLite
link_directories(${NE}/sqlite)
include_directories(${NE}/sqlite)
add_subdirectory(${NE}/sqlite)

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${NE}/buildNumber.hpp "#ifndef NORDICENGINE_BUILDNUMBER\n#define NORDICENGINE_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${NE}/buildNumber.hpp)

# Generate Library
add_library(NordicEngine SHARED ${LibSources} ${LibHeaders})
set_target_properties(NordicEngine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicEngine PROPERTIES OUTPUT_NAME "NordicEngine")

# Boost
find_package(Boost COMPONENTS locale REQUIRED)
include_directories(${Boost_INCLUDES})

# GLFW
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
link_directories(${NE}/glfw)
include_directories(${NE}/glfw/include)
add_subdirectory(${NE}/glfw)

# GLEW
find_package(GLEW REQUIRED)
link_directories(${GLEW_INCLUDES})
include_directories(${GLEW_INCLUDES})

# GLM
link_directories(${NE}/glm)
include_directories(${NE}/glm)
#add_subdirectory(${NE}/glm)

# STB
link_directories(${NE}/stb)
include_directories(${NE}/stb)
#add_subdirectory(${NE}/stb)

# System Linker
if (WIN32)
    target_link_libraries(NordicEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(NordicEngine "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
else()
    target_link_libraries(NordicEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

# Library Linker
target_link_libraries(NordicEngine SQLite)
target_link_libraries(NordicEngine ${Boost_LIBRARIES})
target_link_libraries(NordicEngine glfw ${GLFW_LIBRARIES})
target_link_libraries(NordicEngine glew ${GLEW_LIBRARIES})
