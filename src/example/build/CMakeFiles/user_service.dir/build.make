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
CMAKE_SOURCE_DIR = /home/czf/liveStream/src/example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/czf/liveStream/src/example/build

# Include any dependencies generated for this target.
include CMakeFiles/user_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/user_service.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/user_service.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/user_service.dir/flags.make

CMakeFiles/user_service.dir/src/UserService.cpp.o: CMakeFiles/user_service.dir/flags.make
CMakeFiles/user_service.dir/src/UserService.cpp.o: ../src/UserService.cpp
CMakeFiles/user_service.dir/src/UserService.cpp.o: CMakeFiles/user_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/user_service.dir/src/UserService.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/user_service.dir/src/UserService.cpp.o -MF CMakeFiles/user_service.dir/src/UserService.cpp.o.d -o CMakeFiles/user_service.dir/src/UserService.cpp.o -c /home/czf/liveStream/src/example/src/UserService.cpp

CMakeFiles/user_service.dir/src/UserService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/user_service.dir/src/UserService.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/UserService.cpp > CMakeFiles/user_service.dir/src/UserService.cpp.i

CMakeFiles/user_service.dir/src/UserService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/user_service.dir/src/UserService.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/UserService.cpp -o CMakeFiles/user_service.dir/src/UserService.cpp.s

CMakeFiles/user_service.dir/src/user.pb.cc.o: CMakeFiles/user_service.dir/flags.make
CMakeFiles/user_service.dir/src/user.pb.cc.o: ../src/user.pb.cc
CMakeFiles/user_service.dir/src/user.pb.cc.o: CMakeFiles/user_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/user_service.dir/src/user.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/user_service.dir/src/user.pb.cc.o -MF CMakeFiles/user_service.dir/src/user.pb.cc.o.d -o CMakeFiles/user_service.dir/src/user.pb.cc.o -c /home/czf/liveStream/src/example/src/user.pb.cc

CMakeFiles/user_service.dir/src/user.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/user_service.dir/src/user.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/user.pb.cc > CMakeFiles/user_service.dir/src/user.pb.cc.i

CMakeFiles/user_service.dir/src/user.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/user_service.dir/src/user.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/user.pb.cc -o CMakeFiles/user_service.dir/src/user.pb.cc.s

CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o: CMakeFiles/user_service.dir/flags.make
CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o: ../src/user.grpc.pb.cc
CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o: CMakeFiles/user_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o -MF CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o.d -o CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o -c /home/czf/liveStream/src/example/src/user.grpc.pb.cc

CMakeFiles/user_service.dir/src/user.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/user_service.dir/src/user.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/user.grpc.pb.cc > CMakeFiles/user_service.dir/src/user.grpc.pb.cc.i

CMakeFiles/user_service.dir/src/user.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/user_service.dir/src/user.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/user.grpc.pb.cc -o CMakeFiles/user_service.dir/src/user.grpc.pb.cc.s

# Object files for target user_service
user_service_OBJECTS = \
"CMakeFiles/user_service.dir/src/UserService.cpp.o" \
"CMakeFiles/user_service.dir/src/user.pb.cc.o" \
"CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o"

# External object files for target user_service
user_service_EXTERNAL_OBJECTS =

user_service: CMakeFiles/user_service.dir/src/UserService.cpp.o
user_service: CMakeFiles/user_service.dir/src/user.pb.cc.o
user_service: CMakeFiles/user_service.dir/src/user.grpc.pb.cc.o
user_service: CMakeFiles/user_service.dir/build.make
user_service: CMakeFiles/user_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable user_service"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/user_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/user_service.dir/build: user_service
.PHONY : CMakeFiles/user_service.dir/build

CMakeFiles/user_service.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/user_service.dir/cmake_clean.cmake
.PHONY : CMakeFiles/user_service.dir/clean

CMakeFiles/user_service.dir/depend:
	cd /home/czf/liveStream/src/example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/czf/liveStream/src/example /home/czf/liveStream/src/example /home/czf/liveStream/src/example/build /home/czf/liveStream/src/example/build /home/czf/liveStream/src/example/build/CMakeFiles/user_service.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/user_service.dir/depend

