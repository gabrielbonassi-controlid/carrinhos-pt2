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

# Include any dependencies generated for this target.
include CMakeFiles/camclient2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/camclient2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camclient2.dir/flags.make

CMakeFiles/camclient2.dir/src/source/device.cpp.o: CMakeFiles/camclient2.dir/flags.make
CMakeFiles/camclient2.dir/src/source/device.cpp.o: ../src/source/device.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camclient2.dir/src/source/device.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/camclient2.dir/src/source/device.cpp.o -c /home/orangepi/carrinhos-pt2/aula-3/src/source/device.cpp

CMakeFiles/camclient2.dir/src/source/device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camclient2.dir/src/source/device.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/carrinhos-pt2/aula-3/src/source/device.cpp > CMakeFiles/camclient2.dir/src/source/device.cpp.i

CMakeFiles/camclient2.dir/src/source/device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camclient2.dir/src/source/device.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/carrinhos-pt2/aula-3/src/source/device.cpp -o CMakeFiles/camclient2.dir/src/source/device.cpp.s

CMakeFiles/camclient2.dir/src/source/client.cpp.o: CMakeFiles/camclient2.dir/flags.make
CMakeFiles/camclient2.dir/src/source/client.cpp.o: ../src/source/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/camclient2.dir/src/source/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/camclient2.dir/src/source/client.cpp.o -c /home/orangepi/carrinhos-pt2/aula-3/src/source/client.cpp

CMakeFiles/camclient2.dir/src/source/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camclient2.dir/src/source/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/carrinhos-pt2/aula-3/src/source/client.cpp > CMakeFiles/camclient2.dir/src/source/client.cpp.i

CMakeFiles/camclient2.dir/src/source/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camclient2.dir/src/source/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/carrinhos-pt2/aula-3/src/source/client.cpp -o CMakeFiles/camclient2.dir/src/source/client.cpp.s

CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o: CMakeFiles/camclient2.dir/flags.make
CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o: ../src/source/camclient2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o -c /home/orangepi/carrinhos-pt2/aula-3/src/source/camclient2.cpp

CMakeFiles/camclient2.dir/src/source/camclient2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camclient2.dir/src/source/camclient2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orangepi/carrinhos-pt2/aula-3/src/source/camclient2.cpp > CMakeFiles/camclient2.dir/src/source/camclient2.cpp.i

CMakeFiles/camclient2.dir/src/source/camclient2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camclient2.dir/src/source/camclient2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orangepi/carrinhos-pt2/aula-3/src/source/camclient2.cpp -o CMakeFiles/camclient2.dir/src/source/camclient2.cpp.s

# Object files for target camclient2
camclient2_OBJECTS = \
"CMakeFiles/camclient2.dir/src/source/device.cpp.o" \
"CMakeFiles/camclient2.dir/src/source/client.cpp.o" \
"CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o"

# External object files for target camclient2
camclient2_EXTERNAL_OBJECTS =

camclient2: CMakeFiles/camclient2.dir/src/source/device.cpp.o
camclient2: CMakeFiles/camclient2.dir/src/source/client.cpp.o
camclient2: CMakeFiles/camclient2.dir/src/source/camclient2.cpp.o
camclient2: CMakeFiles/camclient2.dir/build.make
camclient2: CMakeFiles/camclient2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable camclient2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camclient2.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/orangepi/carrinhos-pt2/aula-3/build/camclient2 /home/orangepi/carrinhos-pt2/aula-3/src/source/camclient2

# Rule to build all files generated by this target.
CMakeFiles/camclient2.dir/build: camclient2

.PHONY : CMakeFiles/camclient2.dir/build

CMakeFiles/camclient2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camclient2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camclient2.dir/clean

CMakeFiles/camclient2.dir/depend:
	cd /home/orangepi/carrinhos-pt2/aula-3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/carrinhos-pt2/aula-3 /home/orangepi/carrinhos-pt2/aula-3 /home/orangepi/carrinhos-pt2/aula-3/build /home/orangepi/carrinhos-pt2/aula-3/build /home/orangepi/carrinhos-pt2/aula-3/build/CMakeFiles/camclient2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camclient2.dir/depend

