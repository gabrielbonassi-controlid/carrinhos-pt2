# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/orangepi/carrinhos-pt2/aula-3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orangepi/carrinhos-pt2/aula-3/build

# Utility rule file for client.

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

CMakeFiles/client: camclient1
CMakeFiles/client: camclient2


client: CMakeFiles/client
client: CMakeFiles/client.dir/build.make

.PHONY : client

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/orangepi/carrinhos-pt2/aula-3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/carrinhos-pt2/aula-3 /home/orangepi/carrinhos-pt2/aula-3 /home/orangepi/carrinhos-pt2/aula-3/build /home/orangepi/carrinhos-pt2/aula-3/build /home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

