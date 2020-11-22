cmake_minimum_required(VERSION 3.10)


set(CMAKE_C_COMPILER clang)
project(uchat_server)
find_path(GLIB_INCLUDE_DIR NAMES glib.h PATH_SUFFIXES glib)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
add_link_options(`pkg-config --cflags gtk+-3.0` -rdynamic `pkg-config --cflags --libs gtk+-3.0` -L/usr/local/opt/openssl/lib)

add_executable(uchat_server src/main.c inc/server.h)

set_property(TARGET uchat_server PROPERTY C_STANDARD 11)