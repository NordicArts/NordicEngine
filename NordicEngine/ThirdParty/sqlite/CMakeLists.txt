# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(SQLite)

# Output Dir
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../../../Build/Lib)

# Set Source/Headers
set(Lib_Headers ${PROJECT_SOURCE_DIR}/sqlite3.h)
set(Lib_Source ${PROJECT_SOURCE_DIR}/sqlite3.c)

# Add Source/Headers
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/sqlite3ext.h)

# Link dirs
link_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# Library Build
add_library(SQLite SHARED ${Lib_Source} ${Lib_Headers})
set_target_properties(SQLite PROPERTIES LINKER_LANGUAGE C)
set_target_properties(SQLite PROPERTIES OUTPUT_NAME "SQLite")

# Boost
find_package(Boost COMPONENTS locale REQUIRED)
include_directories(${Boost_INCLUDES})

# Linker
if (WIN32)
    target_link_libraries(SQLite ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(SQLite "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(SQLite ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

target_link_libraries(SQLite ${Boost_LOCALE_LIBRARY})
