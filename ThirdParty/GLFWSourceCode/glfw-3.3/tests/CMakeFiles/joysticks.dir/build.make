# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuqian8/Desktop/glfw-3.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuqian8/Desktop/glfw-3.3

# Include any dependencies generated for this target.
include tests/CMakeFiles/joysticks.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/joysticks.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/joysticks.dir/flags.make

tests/CMakeFiles/joysticks.dir/joysticks.c.o: tests/CMakeFiles/joysticks.dir/flags.make
tests/CMakeFiles/joysticks.dir/joysticks.c.o: tests/joysticks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/joysticks.dir/joysticks.c.o"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/joysticks.dir/joysticks.c.o   -c /Users/liuqian8/Desktop/glfw-3.3/tests/joysticks.c

tests/CMakeFiles/joysticks.dir/joysticks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/joysticks.c.i"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/liuqian8/Desktop/glfw-3.3/tests/joysticks.c > CMakeFiles/joysticks.dir/joysticks.c.i

tests/CMakeFiles/joysticks.dir/joysticks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/joysticks.c.s"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/liuqian8/Desktop/glfw-3.3/tests/joysticks.c -o CMakeFiles/joysticks.dir/joysticks.c.s

tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires:

.PHONY : tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires

tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides: tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires
	$(MAKE) -f tests/CMakeFiles/joysticks.dir/build.make tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides.build
.PHONY : tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides

tests/CMakeFiles/joysticks.dir/joysticks.c.o.provides.build: tests/CMakeFiles/joysticks.dir/joysticks.c.o


tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/joysticks.dir/flags.make
tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o   -c /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c

tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/__/deps/glad_gl.c.i"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c > CMakeFiles/joysticks.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/__/deps/glad_gl.c.s"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c -o CMakeFiles/joysticks.dir/__/deps/glad_gl.c.s

tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.requires:

.PHONY : tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.requires

tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.provides: tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.requires
	$(MAKE) -f tests/CMakeFiles/joysticks.dir/build.make tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.provides.build
.PHONY : tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.provides

tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.provides.build: tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o


# Object files for target joysticks
joysticks_OBJECTS = \
"CMakeFiles/joysticks.dir/joysticks.c.o" \
"CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o"

# External object files for target joysticks
joysticks_EXTERNAL_OBJECTS =

tests/joysticks.app/Contents/MacOS/joysticks: tests/CMakeFiles/joysticks.dir/joysticks.c.o
tests/joysticks.app/Contents/MacOS/joysticks: tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o
tests/joysticks.app/Contents/MacOS/joysticks: tests/CMakeFiles/joysticks.dir/build.make
tests/joysticks.app/Contents/MacOS/joysticks: src/libglfw.3.3.dylib
tests/joysticks.app/Contents/MacOS/joysticks: tests/CMakeFiles/joysticks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable joysticks.app/Contents/MacOS/joysticks"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joysticks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/joysticks.dir/build: tests/joysticks.app/Contents/MacOS/joysticks

.PHONY : tests/CMakeFiles/joysticks.dir/build

tests/CMakeFiles/joysticks.dir/requires: tests/CMakeFiles/joysticks.dir/joysticks.c.o.requires
tests/CMakeFiles/joysticks.dir/requires: tests/CMakeFiles/joysticks.dir/__/deps/glad_gl.c.o.requires

.PHONY : tests/CMakeFiles/joysticks.dir/requires

tests/CMakeFiles/joysticks.dir/clean:
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && $(CMAKE_COMMAND) -P CMakeFiles/joysticks.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/joysticks.dir/clean

tests/CMakeFiles/joysticks.dir/depend:
	cd /Users/liuqian8/Desktop/glfw-3.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuqian8/Desktop/glfw-3.3 /Users/liuqian8/Desktop/glfw-3.3/tests /Users/liuqian8/Desktop/glfw-3.3 /Users/liuqian8/Desktop/glfw-3.3/tests /Users/liuqian8/Desktop/glfw-3.3/tests/CMakeFiles/joysticks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/joysticks.dir/depend

