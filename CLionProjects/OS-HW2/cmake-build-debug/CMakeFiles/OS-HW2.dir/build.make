# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = "E:\programs\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\programs\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\MyPC\CLionProjects\OS-HW2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OS-HW2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OS-HW2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS-HW2.dir/flags.make

CMakeFiles/OS-HW2.dir/concurrent_list.c.obj: CMakeFiles/OS-HW2.dir/flags.make
CMakeFiles/OS-HW2.dir/concurrent_list.c.obj: ../concurrent_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OS-HW2.dir/concurrent_list.c.obj"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\OS-HW2.dir\concurrent_list.c.obj -c C:\Users\MyPC\CLionProjects\OS-HW2\concurrent_list.c

CMakeFiles/OS-HW2.dir/concurrent_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS-HW2.dir/concurrent_list.c.i"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\MyPC\CLionProjects\OS-HW2\concurrent_list.c > CMakeFiles\OS-HW2.dir\concurrent_list.c.i

CMakeFiles/OS-HW2.dir/concurrent_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS-HW2.dir/concurrent_list.c.s"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\MyPC\CLionProjects\OS-HW2\concurrent_list.c -o CMakeFiles\OS-HW2.dir\concurrent_list.c.s

CMakeFiles/OS-HW2.dir/main.c.obj: CMakeFiles/OS-HW2.dir/flags.make
CMakeFiles/OS-HW2.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OS-HW2.dir/main.c.obj"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\OS-HW2.dir\main.c.obj -c C:\Users\MyPC\CLionProjects\OS-HW2\main.c

CMakeFiles/OS-HW2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS-HW2.dir/main.c.i"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\MyPC\CLionProjects\OS-HW2\main.c > CMakeFiles\OS-HW2.dir\main.c.i

CMakeFiles/OS-HW2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS-HW2.dir/main.c.s"
	E:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\MyPC\CLionProjects\OS-HW2\main.c -o CMakeFiles\OS-HW2.dir\main.c.s

# Object files for target OS-HW2
OS__HW2_OBJECTS = \
"CMakeFiles/OS-HW2.dir/concurrent_list.c.obj" \
"CMakeFiles/OS-HW2.dir/main.c.obj"

# External object files for target OS-HW2
OS__HW2_EXTERNAL_OBJECTS =

OS-HW2.exe: CMakeFiles/OS-HW2.dir/concurrent_list.c.obj
OS-HW2.exe: CMakeFiles/OS-HW2.dir/main.c.obj
OS-HW2.exe: CMakeFiles/OS-HW2.dir/build.make
OS-HW2.exe: CMakeFiles/OS-HW2.dir/linklibs.rsp
OS-HW2.exe: CMakeFiles/OS-HW2.dir/objects1.rsp
OS-HW2.exe: CMakeFiles/OS-HW2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable OS-HW2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OS-HW2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS-HW2.dir/build: OS-HW2.exe

.PHONY : CMakeFiles/OS-HW2.dir/build

CMakeFiles/OS-HW2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OS-HW2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OS-HW2.dir/clean

CMakeFiles/OS-HW2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\MyPC\CLionProjects\OS-HW2 C:\Users\MyPC\CLionProjects\OS-HW2 C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug C:\Users\MyPC\CLionProjects\OS-HW2\cmake-build-debug\CMakeFiles\OS-HW2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OS-HW2.dir/depend

