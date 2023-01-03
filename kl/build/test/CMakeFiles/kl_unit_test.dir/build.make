# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rscuber/ProgramDesign/ICBench/algorithm/KL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build

# Include any dependencies generated for this target.
include test/CMakeFiles/kl_unit_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/kl_unit_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/kl_unit_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/kl_unit_test.dir/flags.make

test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o: test/CMakeFiles/kl_unit_test.dir/flags.make
test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o: ../test/kl_unittest.cpp
test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o: test/CMakeFiles/kl_unit_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o"
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o -MF CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o.d -o CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o -c /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test/kl_unittest.cpp

test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.i"
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test/kl_unittest.cpp > CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.i

test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.s"
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test/kl_unittest.cpp -o CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.s

# Object files for target kl_unit_test
kl_unit_test_OBJECTS = \
"CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o"

# External object files for target kl_unit_test
kl_unit_test_EXTERNAL_OBJECTS =

test/kl_unit_test: test/CMakeFiles/kl_unit_test.dir/kl_unittest.cpp.o
test/kl_unit_test: test/CMakeFiles/kl_unit_test.dir/build.make
test/kl_unit_test: src/libkl.a
test/kl_unit_test: _deps/googletest-build/googlemock/gtest/libgtest_main.a
test/kl_unit_test: _deps/googletest-build/googlemock/gtest/libgtest.a
test/kl_unit_test: test/CMakeFiles/kl_unit_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kl_unit_test"
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kl_unit_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/kl_unit_test.dir/build: test/kl_unit_test
.PHONY : test/CMakeFiles/kl_unit_test.dir/build

test/CMakeFiles/kl_unit_test.dir/clean:
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test && $(CMAKE_COMMAND) -P CMakeFiles/kl_unit_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/kl_unit_test.dir/clean

test/CMakeFiles/kl_unit_test.dir/depend:
	cd /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rscuber/ProgramDesign/ICBench/algorithm/KL /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/test /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test /Users/rscuber/ProgramDesign/ICBench/algorithm/KL/build/test/CMakeFiles/kl_unit_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/kl_unit_test.dir/depend
