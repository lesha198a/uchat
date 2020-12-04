cmake_minimum_required(VERSION 3.17)
project(uchat C)

set(CMAKE_C_STANDARD 11)
add_link_options()

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(headers_inc inc/client.h inc/db.h inc/lib.h inc/replies.h inc/server.h)
AUX_SOURCE_DIRECTORY(src/lib lib_src)
AUX_SOURCE_DIRECTORY(src/client client_src)
AUX_SOURCE_DIRECTORY(src/server server_src)
AUX_SOURCE_DIRECTORY(src/server/db server_src)
AUX_SOURCE_DIRECTORY(src/server/command server_src)
AUX_SOURCE_DIRECTORY(src/server/replies server_src)
add_executable(uchat ${client_src} ${lib_src} ${headers_inc})
add_executable(uchat_server ${server_src} ${lib_src} ${headers_inc})

#target_link_libraries(uchat_server ${CMAKE_SOURCE_DIR}/libraries/sqlite3/libsqlite3.a)
# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(uchat ${GTK3_LIBRARIES})
target_link_libraries(uchat ${CURSES_LIBRARIES})