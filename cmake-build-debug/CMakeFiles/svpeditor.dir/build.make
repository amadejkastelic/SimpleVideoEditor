# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/projects/svpeditor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/projects/svpeditor/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/svpeditor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/svpeditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/svpeditor.dir/flags.make

CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o: svpeditor_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o -c /opt/projects/svpeditor/cmake-build-debug/svpeditor_autogen/mocs_compilation.cpp

CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/cmake-build-debug/svpeditor_autogen/mocs_compilation.cpp > CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.i

CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/cmake-build-debug/svpeditor_autogen/mocs_compilation.cpp -o CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.s

CMakeFiles/svpeditor.dir/main.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/svpeditor.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/main.cpp.o -c /opt/projects/svpeditor/main.cpp

CMakeFiles/svpeditor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/main.cpp > CMakeFiles/svpeditor.dir/main.cpp.i

CMakeFiles/svpeditor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/main.cpp -o CMakeFiles/svpeditor.dir/main.cpp.s

CMakeFiles/svpeditor.dir/editor.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/editor.cpp.o: ../editor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/svpeditor.dir/editor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/editor.cpp.o -c /opt/projects/svpeditor/editor.cpp

CMakeFiles/svpeditor.dir/editor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/editor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/editor.cpp > CMakeFiles/svpeditor.dir/editor.cpp.i

CMakeFiles/svpeditor.dir/editor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/editor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/editor.cpp -o CMakeFiles/svpeditor.dir/editor.cpp.s

CMakeFiles/svpeditor.dir/data/file.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/data/file.cpp.o: ../data/file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/svpeditor.dir/data/file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/data/file.cpp.o -c /opt/projects/svpeditor/data/file.cpp

CMakeFiles/svpeditor.dir/data/file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/data/file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/data/file.cpp > CMakeFiles/svpeditor.dir/data/file.cpp.i

CMakeFiles/svpeditor.dir/data/file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/data/file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/data/file.cpp -o CMakeFiles/svpeditor.dir/data/file.cpp.s

CMakeFiles/svpeditor.dir/data/video_file.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/data/video_file.cpp.o: ../data/video_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/svpeditor.dir/data/video_file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/data/video_file.cpp.o -c /opt/projects/svpeditor/data/video_file.cpp

CMakeFiles/svpeditor.dir/data/video_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/data/video_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/data/video_file.cpp > CMakeFiles/svpeditor.dir/data/video_file.cpp.i

CMakeFiles/svpeditor.dir/data/video_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/data/video_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/data/video_file.cpp -o CMakeFiles/svpeditor.dir/data/video_file.cpp.s

CMakeFiles/svpeditor.dir/data/image_file.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/data/image_file.cpp.o: ../data/image_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/svpeditor.dir/data/image_file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/data/image_file.cpp.o -c /opt/projects/svpeditor/data/image_file.cpp

CMakeFiles/svpeditor.dir/data/image_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/data/image_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/data/image_file.cpp > CMakeFiles/svpeditor.dir/data/image_file.cpp.i

CMakeFiles/svpeditor.dir/data/image_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/data/image_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/data/image_file.cpp -o CMakeFiles/svpeditor.dir/data/image_file.cpp.s

CMakeFiles/svpeditor.dir/parser.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/svpeditor.dir/parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/parser.cpp.o -c /opt/projects/svpeditor/parser.cpp

CMakeFiles/svpeditor.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/parser.cpp > CMakeFiles/svpeditor.dir/parser.cpp.i

CMakeFiles/svpeditor.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/parser.cpp -o CMakeFiles/svpeditor.dir/parser.cpp.s

CMakeFiles/svpeditor.dir/renderer.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/renderer.cpp.o: ../renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/svpeditor.dir/renderer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/renderer.cpp.o -c /opt/projects/svpeditor/renderer.cpp

CMakeFiles/svpeditor.dir/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/renderer.cpp > CMakeFiles/svpeditor.dir/renderer.cpp.i

CMakeFiles/svpeditor.dir/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/renderer.cpp -o CMakeFiles/svpeditor.dir/renderer.cpp.s

CMakeFiles/svpeditor.dir/data/audio_file.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/data/audio_file.cpp.o: ../data/audio_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/svpeditor.dir/data/audio_file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/data/audio_file.cpp.o -c /opt/projects/svpeditor/data/audio_file.cpp

CMakeFiles/svpeditor.dir/data/audio_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/data/audio_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/data/audio_file.cpp > CMakeFiles/svpeditor.dir/data/audio_file.cpp.i

CMakeFiles/svpeditor.dir/data/audio_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/data/audio_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/data/audio_file.cpp -o CMakeFiles/svpeditor.dir/data/audio_file.cpp.s

CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o: ../widgets/text_edit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o -c /opt/projects/svpeditor/widgets/text_edit.cpp

CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/widgets/text_edit.cpp > CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.i

CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/widgets/text_edit.cpp -o CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.s

CMakeFiles/svpeditor.dir/widgets/video.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/widgets/video.cpp.o: ../widgets/video.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/svpeditor.dir/widgets/video.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/widgets/video.cpp.o -c /opt/projects/svpeditor/widgets/video.cpp

CMakeFiles/svpeditor.dir/widgets/video.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/widgets/video.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/widgets/video.cpp > CMakeFiles/svpeditor.dir/widgets/video.cpp.i

CMakeFiles/svpeditor.dir/widgets/video.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/widgets/video.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/widgets/video.cpp -o CMakeFiles/svpeditor.dir/widgets/video.cpp.s

CMakeFiles/svpeditor.dir/data/text.cpp.o: CMakeFiles/svpeditor.dir/flags.make
CMakeFiles/svpeditor.dir/data/text.cpp.o: ../data/text.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/svpeditor.dir/data/text.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/svpeditor.dir/data/text.cpp.o -c /opt/projects/svpeditor/data/text.cpp

CMakeFiles/svpeditor.dir/data/text.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/svpeditor.dir/data/text.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/projects/svpeditor/data/text.cpp > CMakeFiles/svpeditor.dir/data/text.cpp.i

CMakeFiles/svpeditor.dir/data/text.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/svpeditor.dir/data/text.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/projects/svpeditor/data/text.cpp -o CMakeFiles/svpeditor.dir/data/text.cpp.s

# Object files for target svpeditor
svpeditor_OBJECTS = \
"CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/svpeditor.dir/main.cpp.o" \
"CMakeFiles/svpeditor.dir/editor.cpp.o" \
"CMakeFiles/svpeditor.dir/data/file.cpp.o" \
"CMakeFiles/svpeditor.dir/data/video_file.cpp.o" \
"CMakeFiles/svpeditor.dir/data/image_file.cpp.o" \
"CMakeFiles/svpeditor.dir/parser.cpp.o" \
"CMakeFiles/svpeditor.dir/renderer.cpp.o" \
"CMakeFiles/svpeditor.dir/data/audio_file.cpp.o" \
"CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o" \
"CMakeFiles/svpeditor.dir/widgets/video.cpp.o" \
"CMakeFiles/svpeditor.dir/data/text.cpp.o"

# External object files for target svpeditor
svpeditor_EXTERNAL_OBJECTS =

svpeditor: CMakeFiles/svpeditor.dir/svpeditor_autogen/mocs_compilation.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/main.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/editor.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/data/file.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/data/video_file.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/data/image_file.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/parser.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/renderer.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/data/audio_file.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/widgets/text_edit.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/widgets/video.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/data/text.cpp.o
svpeditor: CMakeFiles/svpeditor.dir/build.make
svpeditor: /usr/lib/libQt5MultimediaWidgets.so.5.15.0
svpeditor: /usr/lib/libyaml-cpp.so.0.6.3
svpeditor: /usr/lib/libQt5Widgets.so.5.15.0
svpeditor: /usr/lib/libQt5Multimedia.so.5.15.0
svpeditor: /usr/lib/libQt5Network.so.5.15.0
svpeditor: /usr/lib/libQt5Gui.so.5.15.0
svpeditor: /usr/lib/libQt5Core.so.5.15.0
svpeditor: CMakeFiles/svpeditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/projects/svpeditor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable svpeditor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/svpeditor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/svpeditor.dir/build: svpeditor

.PHONY : CMakeFiles/svpeditor.dir/build

CMakeFiles/svpeditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/svpeditor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/svpeditor.dir/clean

CMakeFiles/svpeditor.dir/depend:
	cd /opt/projects/svpeditor/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/projects/svpeditor /opt/projects/svpeditor /opt/projects/svpeditor/cmake-build-debug /opt/projects/svpeditor/cmake-build-debug /opt/projects/svpeditor/cmake-build-debug/CMakeFiles/svpeditor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/svpeditor.dir/depend

