# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

CMakeFiles/tests.dir/sources/source.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/sources/source.cpp.o: ../sources/source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tests.dir/sources/source.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/sources/source.cpp.o -c /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/sources/source.cpp

CMakeFiles/tests.dir/sources/source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/sources/source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/sources/source.cpp > CMakeFiles/tests.dir/sources/source.cpp.i

CMakeFiles/tests.dir/sources/source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/sources/source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/sources/source.cpp -o CMakeFiles/tests.dir/sources/source.cpp.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/sources/source.cpp.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests.dir/sources/source.cpp.o
tests: CMakeFiles/tests.dir/build.make
tests: /home/mihailus/.hunter/_Base/70287b1/3ed7151/b8f46c4/Install/lib/libgtest.a
tests: /home/mihailus/.hunter/_Base/70287b1/3ed7151/b8f46c4/Install/lib/libgtest_main.a
tests: libAnalyseCache.a
tests: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests

.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend:
	cd /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release /home/mihailus/Mihailus2000/MGTU_2_1_АЯ/lab-02-cache/cmake-build-release/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests.dir/depend

