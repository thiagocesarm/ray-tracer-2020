# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build

# Include any dependencies generated for this target.
include CMakeFiles/basic_rt3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic_rt3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic_rt3.dir/flags.make

CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o: ../src/cameras/orthographic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/orthographic.cpp

CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/orthographic.cpp > CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.i

CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/orthographic.cpp -o CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.s

CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o: ../src/cameras/perspective.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/perspective.cpp

CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/perspective.cpp > CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.i

CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/cameras/perspective.cpp -o CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.s

CMakeFiles/basic_rt3.dir/src/core/api.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/api.cpp.o: ../src/core/api.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/api.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/api.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/api.cpp

CMakeFiles/basic_rt3.dir/src/core/api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/api.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/api.cpp > CMakeFiles/basic_rt3.dir/src/core/api.cpp.i

CMakeFiles/basic_rt3.dir/src/core/api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/api.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/api.cpp -o CMakeFiles/basic_rt3.dir/src/core/api.cpp.s

CMakeFiles/basic_rt3.dir/src/core/background.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/background.cpp.o: ../src/core/background.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/background.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/background.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/background.cpp

CMakeFiles/basic_rt3.dir/src/core/background.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/background.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/background.cpp > CMakeFiles/basic_rt3.dir/src/core/background.cpp.i

CMakeFiles/basic_rt3.dir/src/core/background.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/background.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/background.cpp -o CMakeFiles/basic_rt3.dir/src/core/background.cpp.s

CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o: ../src/core/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/camera.cpp

CMakeFiles/basic_rt3.dir/src/core/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/camera.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/camera.cpp > CMakeFiles/basic_rt3.dir/src/core/camera.cpp.i

CMakeFiles/basic_rt3.dir/src/core/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/camera.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/camera.cpp -o CMakeFiles/basic_rt3.dir/src/core/camera.cpp.s

CMakeFiles/basic_rt3.dir/src/core/error.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/error.cpp.o: ../src/core/error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/error.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/error.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/error.cpp

CMakeFiles/basic_rt3.dir/src/core/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/error.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/error.cpp > CMakeFiles/basic_rt3.dir/src/core/error.cpp.i

CMakeFiles/basic_rt3.dir/src/core/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/error.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/error.cpp -o CMakeFiles/basic_rt3.dir/src/core/error.cpp.s

CMakeFiles/basic_rt3.dir/src/core/film.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/film.cpp.o: ../src/core/film.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/film.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/film.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/film.cpp

CMakeFiles/basic_rt3.dir/src/core/film.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/film.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/film.cpp > CMakeFiles/basic_rt3.dir/src/core/film.cpp.i

CMakeFiles/basic_rt3.dir/src/core/film.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/film.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/film.cpp -o CMakeFiles/basic_rt3.dir/src/core/film.cpp.s

CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o: ../src/core/image_io.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/image_io.cpp

CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/image_io.cpp > CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.i

CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/image_io.cpp -o CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.s

CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o: ../src/core/integrator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/integrator.cpp

CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/integrator.cpp > CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.i

CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/integrator.cpp -o CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.s

CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o: ../src/core/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/parser.cpp

CMakeFiles/basic_rt3.dir/src/core/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/parser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/parser.cpp > CMakeFiles/basic_rt3.dir/src/core/parser.cpp.i

CMakeFiles/basic_rt3.dir/src/core/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/parser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/parser.cpp -o CMakeFiles/basic_rt3.dir/src/core/parser.cpp.s

CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o: ../src/core/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/scene.cpp

CMakeFiles/basic_rt3.dir/src/core/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/core/scene.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/scene.cpp > CMakeFiles/basic_rt3.dir/src/core/scene.cpp.i

CMakeFiles/basic_rt3.dir/src/core/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/core/scene.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/core/scene.cpp -o CMakeFiles/basic_rt3.dir/src/core/scene.cpp.s

CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o: ../src/ext/lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/ext/lodepng.cpp

CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/ext/lodepng.cpp > CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.i

CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/ext/lodepng.cpp -o CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.s

CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o: ../src/integrators/flat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/integrators/flat.cpp

CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/integrators/flat.cpp > CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.i

CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/integrators/flat.cpp -o CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.s

CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o: CMakeFiles/basic_rt3.dir/flags.make
CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o: ../src/main/rt3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o -c /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/main/rt3.cpp

CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/main/rt3.cpp > CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.i

CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/src/main/rt3.cpp -o CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.s

# Object files for target basic_rt3
basic_rt3_OBJECTS = \
"CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/api.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/background.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/error.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/film.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o" \
"CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o"

# External object files for target basic_rt3
basic_rt3_EXTERNAL_OBJECTS =

basic_rt3: CMakeFiles/basic_rt3.dir/src/cameras/orthographic.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/cameras/perspective.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/api.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/background.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/camera.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/error.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/film.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/image_io.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/integrator.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/parser.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/core/scene.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/ext/lodepng.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/integrators/flat.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/src/main/rt3.cpp.o
basic_rt3: CMakeFiles/basic_rt3.dir/build.make
basic_rt3: CMakeFiles/basic_rt3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable basic_rt3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic_rt3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic_rt3.dir/build: basic_rt3

.PHONY : CMakeFiles/basic_rt3.dir/build

CMakeFiles/basic_rt3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic_rt3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic_rt3.dir/clean

CMakeFiles/basic_rt3.dir/depend:
	cd /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03 /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03 /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build /Users/lairene.g/Documents/UFRN/CG/ray-tracer-2020/project03/build/CMakeFiles/basic_rt3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic_rt3.dir/depend

