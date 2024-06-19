# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/mehmet/Codes/opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mehmet/Codes/opengl/build

# Include any dependencies generated for this target.
include lib/shader/CMakeFiles/shader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/shader/CMakeFiles/shader.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/shader/CMakeFiles/shader.dir/progress.make

# Include the compile flags for this target's objects.
include lib/shader/CMakeFiles/shader.dir/flags.make

lib/shader/CMakeFiles/shader.dir/shader.cpp.o: lib/shader/CMakeFiles/shader.dir/flags.make
lib/shader/CMakeFiles/shader.dir/shader.cpp.o: ../lib/shader/shader.cpp
lib/shader/CMakeFiles/shader.dir/shader.cpp.o: lib/shader/CMakeFiles/shader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mehmet/Codes/opengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/shader/CMakeFiles/shader.dir/shader.cpp.o"
	cd /home/mehmet/Codes/opengl/build/lib/shader && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/shader/CMakeFiles/shader.dir/shader.cpp.o -MF CMakeFiles/shader.dir/shader.cpp.o.d -o CMakeFiles/shader.dir/shader.cpp.o -c /home/mehmet/Codes/opengl/lib/shader/shader.cpp

lib/shader/CMakeFiles/shader.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shader.dir/shader.cpp.i"
	cd /home/mehmet/Codes/opengl/build/lib/shader && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mehmet/Codes/opengl/lib/shader/shader.cpp > CMakeFiles/shader.dir/shader.cpp.i

lib/shader/CMakeFiles/shader.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shader.dir/shader.cpp.s"
	cd /home/mehmet/Codes/opengl/build/lib/shader && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mehmet/Codes/opengl/lib/shader/shader.cpp -o CMakeFiles/shader.dir/shader.cpp.s

# Object files for target shader
shader_OBJECTS = \
"CMakeFiles/shader.dir/shader.cpp.o"

# External object files for target shader
shader_EXTERNAL_OBJECTS =

lib/shader/libshader.a: lib/shader/CMakeFiles/shader.dir/shader.cpp.o
lib/shader/libshader.a: lib/shader/CMakeFiles/shader.dir/build.make
lib/shader/libshader.a: lib/shader/CMakeFiles/shader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mehmet/Codes/opengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libshader.a"
	cd /home/mehmet/Codes/opengl/build/lib/shader && $(CMAKE_COMMAND) -P CMakeFiles/shader.dir/cmake_clean_target.cmake
	cd /home/mehmet/Codes/opengl/build/lib/shader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/shader/CMakeFiles/shader.dir/build: lib/shader/libshader.a
.PHONY : lib/shader/CMakeFiles/shader.dir/build

lib/shader/CMakeFiles/shader.dir/clean:
	cd /home/mehmet/Codes/opengl/build/lib/shader && $(CMAKE_COMMAND) -P CMakeFiles/shader.dir/cmake_clean.cmake
.PHONY : lib/shader/CMakeFiles/shader.dir/clean

lib/shader/CMakeFiles/shader.dir/depend:
	cd /home/mehmet/Codes/opengl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mehmet/Codes/opengl /home/mehmet/Codes/opengl/lib/shader /home/mehmet/Codes/opengl/build /home/mehmet/Codes/opengl/build/lib/shader /home/mehmet/Codes/opengl/build/lib/shader/CMakeFiles/shader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/shader/CMakeFiles/shader.dir/depend

