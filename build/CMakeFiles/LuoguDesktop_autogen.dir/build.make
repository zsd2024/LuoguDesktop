# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/zyk/.tmp/LuoguDesktop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyk/.tmp/LuoguDesktop/build

# Utility rule file for LuoguDesktop_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/LuoguDesktop_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LuoguDesktop_autogen.dir/progress.make

CMakeFiles/LuoguDesktop_autogen: LuoguDesktop_autogen/timestamp

LuoguDesktop_autogen/timestamp: /home/zyk/.tmp/Qt/5.15.2/gcc_64/bin/moc
LuoguDesktop_autogen/timestamp: /home/zyk/.tmp/Qt/5.15.2/gcc_64/bin/uic
LuoguDesktop_autogen/timestamp: CMakeFiles/LuoguDesktop_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/zyk/.tmp/LuoguDesktop/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target LuoguDesktop"
	/usr/bin/cmake -E cmake_autogen /home/zyk/.tmp/LuoguDesktop/build/CMakeFiles/LuoguDesktop_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/zyk/.tmp/LuoguDesktop/build/LuoguDesktop_autogen/timestamp

LuoguDesktop_autogen: CMakeFiles/LuoguDesktop_autogen
LuoguDesktop_autogen: LuoguDesktop_autogen/timestamp
LuoguDesktop_autogen: CMakeFiles/LuoguDesktop_autogen.dir/build.make
.PHONY : LuoguDesktop_autogen

# Rule to build all files generated by this target.
CMakeFiles/LuoguDesktop_autogen.dir/build: LuoguDesktop_autogen
.PHONY : CMakeFiles/LuoguDesktop_autogen.dir/build

CMakeFiles/LuoguDesktop_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LuoguDesktop_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LuoguDesktop_autogen.dir/clean

CMakeFiles/LuoguDesktop_autogen.dir/depend:
	cd /home/zyk/.tmp/LuoguDesktop/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyk/.tmp/LuoguDesktop /home/zyk/.tmp/LuoguDesktop /home/zyk/.tmp/LuoguDesktop/build /home/zyk/.tmp/LuoguDesktop/build /home/zyk/.tmp/LuoguDesktop/build/CMakeFiles/LuoguDesktop_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/LuoguDesktop_autogen.dir/depend

