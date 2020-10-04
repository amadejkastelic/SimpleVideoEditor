cmake_minimum_required(VERSION 3.17)
project(svpeditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(GNUInstallDirs)

find_package(ImageMagick REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

add_executable(svpeditor main.cpp editor.h editor.cpp data/file.cpp data/file.h data/video_file.cpp data/video_file.h data/image_file.cpp data/image_file.h parser.cpp parser.h renderer.cpp renderer.h data/files.h data/audio_file.cpp data/audio_file.h widgets/text_edit.cpp widgets/text_edit.h widgets/video.cpp widgets/video.h data/text.cpp data/text.h widgets/settings.cpp widgets/settings.h)

target_include_directories(svpeditor PUBLIC
        $<BUILD_INTERFACE:/usr/include/libopenshot-audio>
        $<INSTALL_INTERFACE:/usr/include/libopenshot-audio>)
target_include_directories(svpeditor PUBLIC
        $<BUILD_INTERFACE:/usr/include/libopenshot>
        $<INSTALL_INTERFACE:/usr/include/libopenshot>)
target_link_libraries(svpeditor PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets yaml-cpp openshot-audio openshot)

install(TARGETS svpeditor DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5gui5 libopenshot-dev libopenshot-audio-dev libyaml-cpp-dev libqt5multimediawidgets5")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Amadej Kastelic")
set(CPACK_PACKAGE_NAME "SimpleVideoEditor")
set(CPACK_PACKAGE_VENDOR "AmadejKastelic")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
include(CPack)
