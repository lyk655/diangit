# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\diangit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\diangit\cmake-build-debug

# Include any dependencies generated for this target.
include zlib-1.3.1/CMakeFiles/example64.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zlib-1.3.1/CMakeFiles/example64.dir/compiler_depend.make

# Include the progress variables for this target.
include zlib-1.3.1/CMakeFiles/example64.dir/progress.make

# Include the compile flags for this target's objects.
include zlib-1.3.1/CMakeFiles/example64.dir/flags.make

zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj: zlib-1.3.1/CMakeFiles/example64.dir/flags.make
zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj: zlib-1.3.1/CMakeFiles/example64.dir/includes_C.rsp
zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj: E:/diangit/zlib-1.3.1/test/example.c
zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj: zlib-1.3.1/CMakeFiles/example64.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\diangit\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj"
	cd /d E:\diangit\cmake-build-debug\zlib-1.3.1 && "D:\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj -MF CMakeFiles\example64.dir\test\example.c.obj.d -o CMakeFiles\example64.dir\test\example.c.obj -c E:\diangit\zlib-1.3.1\test\example.c

zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/example64.dir/test/example.c.i"
	cd /d E:\diangit\cmake-build-debug\zlib-1.3.1 && "D:\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\diangit\zlib-1.3.1\test\example.c > CMakeFiles\example64.dir\test\example.c.i

zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/example64.dir/test/example.c.s"
	cd /d E:\diangit\cmake-build-debug\zlib-1.3.1 && "D:\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\diangit\zlib-1.3.1\test\example.c -o CMakeFiles\example64.dir\test\example.c.s

# Object files for target example64
example64_OBJECTS = \
"CMakeFiles/example64.dir/test/example.c.obj"

# External object files for target example64
example64_EXTERNAL_OBJECTS =

zlib-1.3.1/example64.exe: zlib-1.3.1/CMakeFiles/example64.dir/test/example.c.obj
zlib-1.3.1/example64.exe: zlib-1.3.1/CMakeFiles/example64.dir/build.make
zlib-1.3.1/example64.exe: zlib-1.3.1/libzlib.dll.a
zlib-1.3.1/example64.exe: zlib-1.3.1/CMakeFiles/example64.dir/linkLibs.rsp
zlib-1.3.1/example64.exe: zlib-1.3.1/CMakeFiles/example64.dir/objects1.rsp
zlib-1.3.1/example64.exe: zlib-1.3.1/CMakeFiles/example64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\diangit\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable example64.exe"
	cd /d E:\diangit\cmake-build-debug\zlib-1.3.1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\example64.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zlib-1.3.1/CMakeFiles/example64.dir/build: zlib-1.3.1/example64.exe
.PHONY : zlib-1.3.1/CMakeFiles/example64.dir/build

zlib-1.3.1/CMakeFiles/example64.dir/clean:
	cd /d E:\diangit\cmake-build-debug\zlib-1.3.1 && $(CMAKE_COMMAND) -P CMakeFiles\example64.dir\cmake_clean.cmake
.PHONY : zlib-1.3.1/CMakeFiles/example64.dir/clean

zlib-1.3.1/CMakeFiles/example64.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\diangit E:\diangit\zlib-1.3.1 E:\diangit\cmake-build-debug E:\diangit\cmake-build-debug\zlib-1.3.1 E:\diangit\cmake-build-debug\zlib-1.3.1\CMakeFiles\example64.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : zlib-1.3.1/CMakeFiles/example64.dir/depend

