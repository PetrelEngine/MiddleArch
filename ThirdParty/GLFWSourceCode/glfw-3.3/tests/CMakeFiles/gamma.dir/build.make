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
include tests/CMakeFiles/gamma.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/gamma.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/gamma.dir/flags.make

tests/CMakeFiles/gamma.dir/gamma.c.o: tests/CMakeFiles/gamma.dir/flags.make
tests/CMakeFiles/gamma.dir/gamma.c.o: tests/gamma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/gamma.dir/gamma.c.o"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/gamma.c.o   -c /Users/liuqian8/Desktop/glfw-3.3/tests/gamma.c

tests/CMakeFiles/gamma.dir/gamma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/gamma.c.i"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/liuqian8/Desktop/glfw-3.3/tests/gamma.c > CMakeFiles/gamma.dir/gamma.c.i

tests/CMakeFiles/gamma.dir/gamma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/gamma.c.s"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/liuqian8/Desktop/glfw-3.3/tests/gamma.c -o CMakeFiles/gamma.dir/gamma.c.s

tests/CMakeFiles/gamma.dir/gamma.c.o.requires:

.PHONY : tests/CMakeFiles/gamma.dir/gamma.c.o.requires

tests/CMakeFiles/gamma.dir/gamma.c.o.provides: tests/CMakeFiles/gamma.dir/gamma.c.o.requires
	$(MAKE) -f tests/CMakeFiles/gamma.dir/build.make tests/CMakeFiles/gamma.dir/gamma.c.o.provides.build
.PHONY : tests/CMakeFiles/gamma.dir/gamma.c.o.provides

tests/CMakeFiles/gamma.dir/gamma.c.o.provides.build: tests/CMakeFiles/gamma.dir/gamma.c.o


tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/gamma.dir/flags.make
tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/__/deps/glad_gl.c.o   -c /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/__/deps/glad_gl.c.i"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c > CMakeFiles/gamma.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/__/deps/glad_gl.c.s"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/liuqian8/Desktop/glfw-3.3/deps/glad_gl.c -o CMakeFiles/gamma.dir/__/deps/glad_gl.c.s

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.requires:

.PHONY : tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.requires

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.provides: tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.requires
	$(MAKE) -f tests/CMakeFiles/gamma.dir/build.make tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.provides.build
.PHONY : tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.provides

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.provides.build: tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o


# Object files for target gamma
gamma_OBJECTS = \
"CMakeFiles/gamma.dir/gamma.c.o" \
"CMakeFiles/gamma.dir/__/deps/glad_gl.c.o"

# External object files for target gamma
gamma_EXTERNAL_OBJECTS =

tests/gamma.app/Contents/MacOS/gamma: tests/CMakeFiles/gamma.dir/gamma.c.o
tests/gamma.app/Contents/MacOS/gamma: tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o
tests/gamma.app/Contents/MacOS/gamma: tests/CMakeFiles/gamma.dir/build.make
tests/gamma.app/Contents/MacOS/gamma: src/libglfw.3.3.dylib
tests/gamma.app/Contents/MacOS/gamma: tests/CMakeFiles/gamma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liuqian8/Desktop/glfw-3.3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gamma.app/Contents/MacOS/gamma"
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gamma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/gamma.dir/build: tests/gamma.app/Contents/MacOS/gamma

.PHONY : tests/CMakeFiles/gamma.dir/build

tests/CMakeFiles/gamma.dir/requires: tests/CMakeFiles/gamma.dir/gamma.c.o.requires
tests/CMakeFiles/gamma.dir/requires: tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o.requires

.PHONY : tests/CMakeFiles/gamma.dir/requires

tests/CMakeFiles/gamma.dir/clean:
	cd /Users/liuqian8/Desktop/glfw-3.3/tests && $(CMAKE_COMMAND) -P CMakeFiles/gamma.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/gamma.dir/clean

tests/CMakeFiles/gamma.dir/depend:
	cd /Users/liuqian8/Desktop/glfw-3.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuqian8/Desktop/glfw-3.3 /Users/liuqian8/Desktop/glfw-3.3/tests /Users/liuqian8/Desktop/glfw-3.3 /Users/liuqian8/Desktop/glfw-3.3/tests /Users/liuqian8/Desktop/glfw-3.3/tests/CMakeFiles/gamma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/gamma.dir/depend
