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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fabreezy/Documents/Projects/helib_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fabreezy/Documents/Projects/helib_demo

# Include any dependencies generated for this target.
include CMakeFiles/helibdemo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helibdemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helibdemo.dir/flags.make

CMakeFiles/helibdemo.dir/helib_func.cpp.o: CMakeFiles/helibdemo.dir/flags.make
CMakeFiles/helibdemo.dir/helib_func.cpp.o: helib_func.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabreezy/Documents/Projects/helib_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/helibdemo.dir/helib_func.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helibdemo.dir/helib_func.cpp.o -c /home/fabreezy/Documents/Projects/helib_demo/helib_func.cpp

CMakeFiles/helibdemo.dir/helib_func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helibdemo.dir/helib_func.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabreezy/Documents/Projects/helib_demo/helib_func.cpp > CMakeFiles/helibdemo.dir/helib_func.cpp.i

CMakeFiles/helibdemo.dir/helib_func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helibdemo.dir/helib_func.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabreezy/Documents/Projects/helib_demo/helib_func.cpp -o CMakeFiles/helibdemo.dir/helib_func.cpp.s

# Object files for target helibdemo
helibdemo_OBJECTS = \
"CMakeFiles/helibdemo.dir/helib_func.cpp.o"

# External object files for target helibdemo
helibdemo_EXTERNAL_OBJECTS =

helibdemo: CMakeFiles/helibdemo.dir/helib_func.cpp.o
helibdemo: CMakeFiles/helibdemo.dir/build.make
helibdemo: /usr/local/helib_pack/lib/libhelib.a
helibdemo: /usr/local/helib_pack/lib/libntl.so
helibdemo: /usr/local/helib_pack/lib/libgmp.so
helibdemo: CMakeFiles/helibdemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fabreezy/Documents/Projects/helib_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable helibdemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helibdemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helibdemo.dir/build: helibdemo

.PHONY : CMakeFiles/helibdemo.dir/build

CMakeFiles/helibdemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/helibdemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/helibdemo.dir/clean

CMakeFiles/helibdemo.dir/depend:
	cd /home/fabreezy/Documents/Projects/helib_demo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fabreezy/Documents/Projects/helib_demo /home/fabreezy/Documents/Projects/helib_demo /home/fabreezy/Documents/Projects/helib_demo /home/fabreezy/Documents/Projects/helib_demo /home/fabreezy/Documents/Projects/helib_demo/CMakeFiles/helibdemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helibdemo.dir/depend

