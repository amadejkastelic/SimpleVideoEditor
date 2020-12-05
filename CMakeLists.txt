cmake_minimum_required(VERSION 3.14)
project(svpeditor LANGUAGES CXX VERSION 1.0.0)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
#set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_LINK_LIBRARY_SUFFIX ".a")
set(CMAKE_AUTOSTATICPLUGINS ON)

#include(GNUInstallDirs)

#set(Qt5_DIR "/opt/qt-5.15.1")

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Multimedia
        MultimediaWidgets
        QuickControls2)
#find_package(Qt5 QUIET COMPONENTS QmlWorkerScript)
find_package(ImageMagick REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(svpeditor main.cpp editor.h editor.cpp data/file.cpp data/file.h data/video_file.cpp data/video_file.h data/image_file.cpp data/image_file.h parser.cpp parser.h renderer.cpp renderer.h data/files.h data/audio_file.cpp data/audio_file.h widgets/text_edit.cpp widgets/text_edit.h widgets/video.cpp widgets/video.h data/text.cpp data/text.h widgets/settings.cpp widgets/settings.h widgets/video_render_widget.cpp widgets/video_render_widget.h widgets/video_renderer.h widgets/video_renderer.cpp widgets/highlighter.cpp widgets/highlighter.h)

target_compile_features(svpeditor PUBLIC cxx_std_14)
set_target_properties(svpeditor PROPERTIES AUTORCC TRUE)
set_target_properties(svpeditor PROPERTIES AUTOMOC TRUE)

target_include_directories(svpeditor PUBLIC
        $<BUILD_INTERFACE:/usr/include/libopenshot-audio>
        $<INSTALL_INTERFACE:/usr/include/libopenshot-audio>)
target_include_directories(svpeditor PUBLIC
        $<BUILD_INTERFACE:/usr/include/libopenshot>
        $<INSTALL_INTERFACE:/usr/include/libopenshot>)
target_link_libraries(svpeditor PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        Qt5::QuickControls2)
target_link_libraries(svpeditor PRIVATE openshot-audio openshot yaml-cpp)

get_target_property(QT_TARGET_TYPE Qt5::Core TYPE)
if (${QT_TARGET_TYPE} STREQUAL "STATIC_LIBRARY")
    include(QtStaticCMake.cmake)
endif()

install(TARGETS svpeditor DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR TGZ)
set(CPACK_SET_DESTDIR ON)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5gui5 libjsoncpp-dev qtbase5-dev qtmultimedia5-dev libzmqpp-dev libavcodec-dev libavformat-dev libswscale-dev libqt5multimedia5 libopenshot-dev libopenshot-audio-dev libyaml-cpp-dev libqt5multimediawidgets5 imagemagick")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Amadej Kastelic")
set(CPACK_PACKAGE_NAME "SimpleVideoEditor")
set(CPACK_PACKAGE_VENDOR "AmadejKastelic")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
include(CPack)
