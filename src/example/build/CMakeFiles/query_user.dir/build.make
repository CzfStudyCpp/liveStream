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
include CMakeFiles/query_user.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/query_user.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/query_user.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/query_user.dir/flags.make

CMakeFiles/query_user.dir/src/QueryUser.cpp.o: CMakeFiles/query_user.dir/flags.make
CMakeFiles/query_user.dir/src/QueryUser.cpp.o: ../src/QueryUser.cpp
CMakeFiles/query_user.dir/src/QueryUser.cpp.o: CMakeFiles/query_user.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/query_user.dir/src/QueryUser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/query_user.dir/src/QueryUser.cpp.o -MF CMakeFiles/query_user.dir/src/QueryUser.cpp.o.d -o CMakeFiles/query_user.dir/src/QueryUser.cpp.o -c /home/czf/liveStream/src/example/src/QueryUser.cpp

CMakeFiles/query_user.dir/src/QueryUser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/query_user.dir/src/QueryUser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/QueryUser.cpp > CMakeFiles/query_user.dir/src/QueryUser.cpp.i

CMakeFiles/query_user.dir/src/QueryUser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/query_user.dir/src/QueryUser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/QueryUser.cpp -o CMakeFiles/query_user.dir/src/QueryUser.cpp.s

CMakeFiles/query_user.dir/src/user.pb.cc.o: CMakeFiles/query_user.dir/flags.make
CMakeFiles/query_user.dir/src/user.pb.cc.o: ../src/user.pb.cc
CMakeFiles/query_user.dir/src/user.pb.cc.o: CMakeFiles/query_user.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/query_user.dir/src/user.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/query_user.dir/src/user.pb.cc.o -MF CMakeFiles/query_user.dir/src/user.pb.cc.o.d -o CMakeFiles/query_user.dir/src/user.pb.cc.o -c /home/czf/liveStream/src/example/src/user.pb.cc

CMakeFiles/query_user.dir/src/user.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/query_user.dir/src/user.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/user.pb.cc > CMakeFiles/query_user.dir/src/user.pb.cc.i

CMakeFiles/query_user.dir/src/user.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/query_user.dir/src/user.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/user.pb.cc -o CMakeFiles/query_user.dir/src/user.pb.cc.s

CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o: CMakeFiles/query_user.dir/flags.make
CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o: ../src/user.grpc.pb.cc
CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o: CMakeFiles/query_user.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o -MF CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o.d -o CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o -c /home/czf/liveStream/src/example/src/user.grpc.pb.cc

CMakeFiles/query_user.dir/src/user.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/query_user.dir/src/user.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/czf/liveStream/src/example/src/user.grpc.pb.cc > CMakeFiles/query_user.dir/src/user.grpc.pb.cc.i

CMakeFiles/query_user.dir/src/user.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/query_user.dir/src/user.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/czf/liveStream/src/example/src/user.grpc.pb.cc -o CMakeFiles/query_user.dir/src/user.grpc.pb.cc.s

# Object files for target query_user
query_user_OBJECTS = \
"CMakeFiles/query_user.dir/src/QueryUser.cpp.o" \
"CMakeFiles/query_user.dir/src/user.pb.cc.o" \
"CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o"

# External object files for target query_user
query_user_EXTERNAL_OBJECTS =

query_user: CMakeFiles/query_user.dir/src/QueryUser.cpp.o
query_user: CMakeFiles/query_user.dir/src/user.pb.cc.o
query_user: CMakeFiles/query_user.dir/src/user.grpc.pb.cc.o
query_user: CMakeFiles/query_user.dir/build.make
query_user: CMakeFiles/query_user.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/czf/liveStream/src/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable query_user"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/query_user.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/query_user.dir/build: query_user
.PHONY : CMakeFiles/query_user.dir/build

CMakeFiles/query_user.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/query_user.dir/cmake_clean.cmake
.PHONY : CMakeFiles/query_user.dir/clean

CMakeFiles/query_user.dir/depend:
	cd /home/czf/liveStream/src/example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/czf/liveStream/src/example /home/czf/liveStream/src/example /home/czf/liveStream/src/example/build /home/czf/liveStream/src/example/build /home/czf/liveStream/src/example/build/CMakeFiles/query_user.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/query_user.dir/depend

