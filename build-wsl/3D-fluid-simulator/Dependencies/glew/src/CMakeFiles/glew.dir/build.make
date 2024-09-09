# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl

# Include any dependencies generated for this target.
include 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/depend.make

# Include the progress variables for this target.
include 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/progress.make

# Include the compile flags for this target's objects.
include 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/flags.make

3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.o: 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/flags.make
3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.o: ../3D-fluid-simulator/Dependencies/glew/src/glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.o"
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glew.dir/glew.c.o   -c /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/3D-fluid-simulator/Dependencies/glew/src/glew.c

3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glew.dir/glew.c.i"
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/3D-fluid-simulator/Dependencies/glew/src/glew.c > CMakeFiles/glew.dir/glew.c.i

3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glew.dir/glew.c.s"
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/3D-fluid-simulator/Dependencies/glew/src/glew.c -o CMakeFiles/glew.dir/glew.c.s

# Object files for target glew
glew_OBJECTS = \
"CMakeFiles/glew.dir/glew.c.o"

# External object files for target glew
glew_EXTERNAL_OBJECTS =

3D-fluid-simulator/Dependencies/glew/src/libglew.a: 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/glew.c.o
3D-fluid-simulator/Dependencies/glew/src/libglew.a: 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/build.make
3D-fluid-simulator/Dependencies/glew/src/libglew.a: 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglew.a"
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && $(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean_target.cmake
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glew.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/build: 3D-fluid-simulator/Dependencies/glew/src/libglew.a

.PHONY : 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/build

3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/clean:
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src && $(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean.cmake
.PHONY : 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/clean

3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/depend:
	cd /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/3D-fluid-simulator/Dependencies/glew/src /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src /mnt/d/Programming/C++/Home/Projects/3D-fluid-simulator/build-wsl/3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3D-fluid-simulator/Dependencies/glew/src/CMakeFiles/glew.dir/depend
