# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/haoyin/Documents/GitHub/ccplayer/ccmedia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build

# Include any dependencies generated for this target.
include CMakeFiles/ccmedia.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ccmedia.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ccmedia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ccmedia.dir/flags.make

CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/encoder.cpp
CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/encoder.cpp

CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/encoder.cpp > CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/encoder.cpp -o CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/writer.cpp
CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/writer.cpp

CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/writer.cpp > CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/encoder/writer.cpp -o CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/ios/CCPlayer.mm
CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building OBJCXX object CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) -x objective-c++ $(OBJCXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o -MF CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o.d -o CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/ios/CCPlayer.mm

CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing OBJCXX source to CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) $(OBJCXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/ios/CCPlayer.mm > CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.i

CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling OBJCXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(OBJCXX_DEFINES) $(OBJCXX_INCLUDES) $(OBJCXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/ios/CCPlayer.mm -o CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.s

CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/format.cpp
CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/format.cpp

CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/format.cpp > CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/format.cpp -o CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/player.cpp
CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/player.cpp

CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/player.cpp > CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/player/player.cpp -o CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/audio.cpp
CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/audio.cpp

CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/audio.cpp > CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/audio.cpp -o CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/render.cpp
CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/render.cpp

CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/render.cpp > CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/render.cpp -o CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.s

CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/shader_import.c
CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o -MF CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o.d -o CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/shader_import.c

CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/shader_import.c > CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.i

CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/shader_import.c -o CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.s

CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o: CMakeFiles/ccmedia.dir/flags.make
CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o: /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/video.cpp
CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o: CMakeFiles/ccmedia.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o -MF CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o.d -o CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o -c /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/video.cpp

CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/video.cpp > CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.i

CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/ccmedia/render/video.cpp -o CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.s

# Object files for target ccmedia
ccmedia_OBJECTS = \
"CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o" \
"CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o" \
"CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o" \
"CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o"

# External object files for target ccmedia
ccmedia_EXTERNAL_OBJECTS =

libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/encoder/encoder.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/encoder/writer.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/ios/CCPlayer.mm.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/player/format.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/player/player.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/render/audio.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/render/render.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/render/shader_import.c.o
libccmedia.a: CMakeFiles/ccmedia.dir/ccmedia/render/video.cpp.o
libccmedia.a: CMakeFiles/ccmedia.dir/build.make
libccmedia.a: CMakeFiles/ccmedia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libccmedia.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ccmedia.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ccmedia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ccmedia.dir/build: libccmedia.a
.PHONY : CMakeFiles/ccmedia.dir/build

CMakeFiles/ccmedia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ccmedia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ccmedia.dir/clean

CMakeFiles/ccmedia.dir/depend:
	cd /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/haoyin/Documents/GitHub/ccplayer/ccmedia /Users/haoyin/Documents/GitHub/ccplayer/ccmedia /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build /Users/haoyin/Documents/GitHub/ccplayer/ccmedia/build/CMakeFiles/ccmedia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ccmedia.dir/depend
