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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jaclynpalmer/CLionProjects/236Lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/236Lab1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/236Lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/236Lab1.dir/flags.make

CMakeFiles/236Lab1.dir/main.cpp.o: CMakeFiles/236Lab1.dir/flags.make
CMakeFiles/236Lab1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/236Lab1.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/236Lab1.dir/main.cpp.o -c /Users/jaclynpalmer/CLionProjects/236Lab1/main.cpp

CMakeFiles/236Lab1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/236Lab1.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jaclynpalmer/CLionProjects/236Lab1/main.cpp > CMakeFiles/236Lab1.dir/main.cpp.i

CMakeFiles/236Lab1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/236Lab1.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jaclynpalmer/CLionProjects/236Lab1/main.cpp -o CMakeFiles/236Lab1.dir/main.cpp.s

# Object files for target 236Lab1
236Lab1_OBJECTS = \
"CMakeFiles/236Lab1.dir/main.cpp.o"

# External object files for target 236Lab1
236Lab1_EXTERNAL_OBJECTS =

236Lab1: CMakeFiles/236Lab1.dir/main.cpp.o
236Lab1: CMakeFiles/236Lab1.dir/build.make
236Lab1: CMakeFiles/236Lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 236Lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/236Lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/236Lab1.dir/build: 236Lab1

.PHONY : CMakeFiles/236Lab1.dir/build

CMakeFiles/236Lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/236Lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/236Lab1.dir/clean

CMakeFiles/236Lab1.dir/depend:
	cd /Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jaclynpalmer/CLionProjects/236Lab1 /Users/jaclynpalmer/CLionProjects/236Lab1 /Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug /Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug /Users/jaclynpalmer/CLionProjects/236Lab1/cmake-build-debug/CMakeFiles/236Lab1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/236Lab1.dir/depend

