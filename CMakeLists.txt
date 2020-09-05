cmake_minimum_required(VERSION 3.17)
project(svpeditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(ImageMagick REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

include_directories("/usr/include/libopenshot-audio")
include_directories("/usr/include/libopenshot")

add_executable(svpeditor main.cpp editor.h editor.cpp data/file.cpp data/file.h data/video_file.cpp data/video_file.h data/image_file.cpp data/image_file.h parser.cpp parser.h renderer.cpp renderer.h data/files.h data/audio_file.cpp data/audio_file.h widgets/text_edit.cpp widgets/text_edit.h widgets/video.cpp widgets/video.h data/text.cpp data/text.h)

target_link_libraries(svpeditor Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets yaml-cpp openshot-audio openshot)
