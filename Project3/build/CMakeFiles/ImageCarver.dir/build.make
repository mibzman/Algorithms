# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/mibzman/S4/Algorithms/Project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mibzman/S4/Algorithms/Project3/build

# Include any dependencies generated for this target.
include CMakeFiles/ImageCarver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ImageCarver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ImageCarver.dir/flags.make

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o: CMakeFiles/ImageCarver.dir/flags.make
CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o: ../SeamCarveImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mibzman/S4/Algorithms/Project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o -c /home/mibzman/S4/Algorithms/Project3/SeamCarveImage.cpp

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mibzman/S4/Algorithms/Project3/SeamCarveImage.cpp > CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.i

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mibzman/S4/Algorithms/Project3/SeamCarveImage.cpp -o CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.s

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.requires:

.PHONY : CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.requires

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.provides: CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.requires
	$(MAKE) -f CMakeFiles/ImageCarver.dir/build.make CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.provides.build
.PHONY : CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.provides

CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.provides.build: CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o


# Object files for target ImageCarver
ImageCarver_OBJECTS = \
"CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o"

# External object files for target ImageCarver
ImageCarver_EXTERNAL_OBJECTS =

ImageCarver: CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o
ImageCarver: CMakeFiles/ImageCarver.dir/build.make
ImageCarver: CMakeFiles/ImageCarver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mibzman/S4/Algorithms/Project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ImageCarver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImageCarver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ImageCarver.dir/build: ImageCarver

.PHONY : CMakeFiles/ImageCarver.dir/build

CMakeFiles/ImageCarver.dir/requires: CMakeFiles/ImageCarver.dir/SeamCarveImage.cpp.o.requires

.PHONY : CMakeFiles/ImageCarver.dir/requires

CMakeFiles/ImageCarver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ImageCarver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ImageCarver.dir/clean

CMakeFiles/ImageCarver.dir/depend:
	cd /home/mibzman/S4/Algorithms/Project3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mibzman/S4/Algorithms/Project3 /home/mibzman/S4/Algorithms/Project3 /home/mibzman/S4/Algorithms/Project3/build /home/mibzman/S4/Algorithms/Project3/build /home/mibzman/S4/Algorithms/Project3/build/CMakeFiles/ImageCarver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ImageCarver.dir/depend

