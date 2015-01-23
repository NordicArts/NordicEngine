# CMake Version
cmake_minimum_required(VERSION 2.8)
include(CMakeDependentOption)

# Project Name
project(NordicEngine)

# OSX RPATH
set(CMAKE_MACOSX_RPATH 0)

# Options
option(NordicEngine_OSOnly "OS Only" OFF)
option(NordicEngine_UnitTest "Unit Tests" OFF)
option(NordicEngine_FullEngine "Full Engine" OFF)

# NOS Files
set(NE ${PROJECT_SOURCE_DIR}/NordicEngine)
set(LibHeaders ${NE}/Engine.hpp)
set(LibSources ${NE}/Engine.cpp)

# Set Third Party Directory
set(NET ${PROJECT_SOURCE_DIR}/NordicEngine/ThirdParty)

# NOS Includes
list(APPEND LibHeaders ${NE}/Includes.hpp)

# link path
link_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

################################################################
########################### OS STUFF ###########################
################################################################

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

        # Apple Libs
        link_directories(/usr/local/include)
        include_directories(/usr/local/include)
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

####################################################################
########################### ALL COMPILES ###########################
####################################################################

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
link_directories(${NE}/Exception)
include_directories(${NE}/Exception)
list(APPEND LibHeaders ${NE}/Exception/Exception.hpp)
list(APPEND LibSources ${NE}/Exception/Exception.cpp)

# Files
link_directories(${NE}/Files)
include_directories(${NE}/Files)
list(APPEND LibHeaders ${NE}/Files/Loader.hpp)
list(APPEND LibSources ${NE}/Files/Loader.cpp)
list(APPEND LibHeaders ${NE}/Files/Handler.hpp)
list(APPEND LibSources ${NE}/Files/Handler.cpp)
list(APPEND LibHeaders ${NE}/Files/Utils.hpp)
list(APPEND LibSources ${NE}/Files/Utils.cpp)

# TextFile
link_directories(${NE}/Files/Format/TextFile)
include_directories(${NE}/Files/Format/TextFile)
list(APPEND LibHeaders ${NE}/Files/Format/TextFile/Writer.hpp)
list(APPEND LibSources ${NE}/Files/Format/TextFile/Writer.cpp)
list(APPEND LibHeaders ${NE}/Files/Format/TextFile/Reader.hpp)
list(APPEND LibSources ${NE}/Files/Format/TextFile/Reader.cpp)

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

# Color
link_directories(${NE}/Color)
include_directories(${NE}/Color)
list(APPEND LibHeaders ${NE}/Color/Color.hpp)
list(APPEND LibSources ${NE}/Color/Color.cpp)

# Lua
link_directories(${NE}/Files/Format/Lua)
include_directories(${NE}/Files/Format/Lua)
list(APPEND LibHeaders ${NE}/Files/Format/Lua/Lua.hpp)
list(APPEND LibSources ${NE}/Files/Format/Lua/Lua.cpp)

#########################################################################
########################### FULL ENGINE STUFF ###########################
#########################################################################

if (NordicEngine_FullEngine)
    # OpenGL Header
    list(APPEND LibHeaders ${NE}/OS/OpenGL.hpp)

    # Shaders
    link_directories(${NE}/Render/Shaders)
    include_directories(${NE}/Render/Shaders)
    list(APPEND LibHeaders ${NE}/Render/Shaders/Shader.hpp)
    list(APPEND LibSources ${NE}/Render/Shaders/Shader.cpp)
    list(APPEND LibHeaders ${NE}/Render/Shaders/Program.hpp)
    list(APPEND LibSources ${NE}/Render/Shaders/Program.cpp)
    list(APPEND LibHeaders ${NE}/Render/Shaders/Loader.hpp)
    list(APPEND LibSources ${NE}/Render/Shaders/Loader.cpp)

    # BitMap
    link_directories(${NE}/Files/Format/BitMap)
    include_directories(${NE}/Files/Format/BitMap)
    list(APPEND LibHeaders ${NE}/Files/Format/BitMap/BitMap.hpp)
    list(APPEND LibSources ${NE}/Files/Format/BitMap/BitMap.cpp)

    # DDS
    link_directories(${NE}/Files/Format/DDS)
    include_directories(${NE}/Files/Format/DDS)
    list(APPEND LibHeaders ${NE}/Files/Format/DDS/DDS.hpp)
    list(APPEND LibSources ${NE}/Files/Format/DDS/DDS.cpp)

    # Texture
    link_directories(${NE}/Files/Texture)
    include_directories(${NE}/Files/Texture)
    list(APPEND LibHeaders ${NE}/Files/Texture/Texture.hpp)
    list(APPEND LibSources ${NE}/Files/Texture/Texture.cpp)

    # Obj
    link_directories(${NE}/Files/Format/Obj)
    include_directories(${NE}/Files/Format/Obj)
    list(APPEND LibHeaders ${NE}/Files/Format/Obj/Obj.hpp)
    list(APPEND LibSources ${NE}/Files/Format/Obj/Obj.cpp)

    # Window    
    link_directories(${NE}/Window)
    include_directories(${NE}/Window)
    list(APPEND LibHeaders ${NE}/Window/Window.hpp)
    list(APPEND LibSources ${NE}/Window/Window.cpp)

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
    list(APPEND LibHeaders ${NE}/Shaders/Simple.hpp)
    list(APPEND LibSources ${NE}/Shaders/Simple.cpp)

    #list(APPEND LibHeaders ${NE}/Shaders/Shaders.hpp)
    #list(APPEND LibHeaders ${NE}/Shaders/Shaders.inl)
    #list(APPEND LibSources ${NE}/Shaders/Shaders.cpp)
    #list(APPEND LibHeaders ${NE}/Shaders/Program.hpp)
    #list(APPEND LibSources ${NE}/Shaders/Program.cpp)

    # Camera
    link_directories(${NE}/Camera)
    include_directories(${NE}/Camera)
    list(APPEND LibHeaders ${NE}/Camera/Camera.hpp)
    list(APPEND LibSources ${NE}/Camera/Camera.cpp)

    # Model
    link_directories(${NE}/Model)
    include_directories(${NE}/Model)
    list(APPEND LibHeaders ${NE}/Model/Model.hpp)
    list(APPEND LibSources ${NE}/Model/Model.cpp)

    # Light
    link_directories(${NE}/Light)
    include_directories(${NE}/Light)
    list(APPEND LibHeaders ${NE}/Light/Light.hpp)
    list(APPEND LibSources ${NE}/Light/Light.cpp)

    # Settings
    link_directories(${NE}/Settings)
    include_directories(${NE}/Settings)
    list(APPEND LibHeaders ${NE}/Settings/Settings.hpp)
    list(APPEND LibSources ${NE}/Settings/Settings.cpp)

    # 2D Text
    link_directories(${NE}/Render/Text)
    include_directories(${NE}/Render/Text)
    list(APPEND LibHeaders ${NE}/Render/Text/Text.hpp)
    list(APPEND LibSources ${NE}/Render/Text/Text.cpp)
endif()

########################################################################
########################### THIRD PARTY BITS ###########################
########################################################################

# SQLite
link_directories(${NET}/sqlite)
include_directories(${NET}/sqlite)
add_subdirectory(${NET}/sqlite)

# Boost
find_package(Boost COMPONENTS locale REQUIRED)
include_directories(${Boost_INCLUDES})

if (NordicEngine_FullEngine)
    # GLFW
    link_directories(${NET}/glfw)
    include_directories(${NET}/glfw/include)
    add_subdirectory(${NET}/glfw)
endif()

if (NordicEngine_FullEngine)
    # GLEW
    find_package(GLEW REQUIRED)
    link_directories(${GLEW_INCLUDES})
    include_directories(${GLEW_INCLUDES})
endif()

# GLM
link_directories(${NET}/glm)
include_directories(${NET}/glm)
#add_subdirectory(${NET}/glm)

# STB
link_directories(${NET}/stb)
include_directories(${NET}/stb)
#add_subdirectory(${NET}/stb)

# Lua
add_subdirectory(${NET}/lua)
link_directories(${NET}/lua)
include_directories(${NET}/lua)
link_directories(${NET}/lua/lua)
include_directories(${NET}/lua/lua)

# Lua Bridge
link_directories(${NET}/LuaBridge/Source/LuaBridge)
include_directories(${NET}/LuaBridge/Source/LuaBridge)
list(APPEND LibHeaders ${NET}/LuaBridge/Source/LuaBridge/LuaBridge.h)

# ZLib
link_directories(${NET}/miniz)
include_directories(${NET}/miniz)
add_subdirectory(${NET}/miniz)

#########################################################################
########################### BUILD THE LIBRARY ###########################
#########################################################################

# Build Number
string(TIMESTAMP buildNumber "9%j%y%H%M")
file(WRITE ${NE}/buildNumber.hpp "#ifndef NORDICENGINE_BUILDNUMBER\n#define NORDICENGINE_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${NE}/buildNumber.hpp)

# Generate Library
add_library(NordicEngine SHARED ${LibSources} ${LibHeaders})
set_target_properties(NordicEngine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicEngine PROPERTIES OUTPUT_NAME "NordicEngine")

########################################################################
########################### LINK THE LIBRARY ###########################
########################################################################

# System Linker
if(NordicEngine_FullEngine)
    if (WIN32)
        target_link_libraries(NordicEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    elseif (APPLE)
        target_link_libraries(NordicEngine "-framework OpenGL -framework OpenAL -framework GameKit -framework GLKit -framework CoreVideo")
    else()
        target_link_libraries(NordicEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    endif()
endif()

# Universal ones
if (WIN32)
    target_link_libraries(NordicEngine winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(NordicEngine "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework CoreFoundation" c++abi)
else()
    target_link_libraries(NordicEngine ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

# Library Linker
if (NordicEngine_FullEngine)
    target_link_libraries(NordicEngine glfw ${GLFW_LIBRARIES})
    target_link_libraries(NordicEngine ${GLEW_LIBRARIES})
endif()

# Universal links
target_link_libraries(NordicEngine SQLite)
target_link_libraries(NordicEngine ${Boost_LIBRARIES})
target_link_libraries(NordicEngine liblua ${LUA_LIBRARIES})
target_link_libraries(NordicEngine MiniZ)

##################################################################
########################### UNIT TESTS ###########################
##################################################################

# Unit Tests
if (NordicEngine_UnitTest)
    project(UnitTests)    
    SET(UT ${PROJECT_SOURCE_DIR}/Tests)

    link_directories(${UT})
    include_directories(${UT})
    set(TestHeaders ${UT}/Main.hpp)

    if (NordicEngine_OSOnly)
        set(TestSources ${UT}/OSTests.cpp)
    elseif (NordicEngine_FullEngine)
        set(TestSources ${UT}/FullTests.cpp)
    else()
        set(TestSources ${UT}/Tests.cpp)
    endif()

    # Test Framework
    link_directories(${UT}/Catch)
    include_directories(${UT}/Catch)    
    list(APPEND TestHeaders ${UT}/Catch/catch.hpp)

    # Build Test Binary
    add_executable(UnitTests ${TestSources} ${TestHeaders})
    set_target_properties(UnitTests PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(UnitTests PROPERTIES OUTPUT_NAME "UnitTests.app")
    
    # Link Unit Tests to which ever NordicEngine was build
    target_link_libraries(UnitTests NordicEngine)
endif()
