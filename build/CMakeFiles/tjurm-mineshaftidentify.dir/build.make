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
CMAKE_SOURCE_DIR = /home/calbee/robomaster/TJURM-MineShaftIdentify

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/calbee/robomaster/TJURM-MineShaftIdentify/build

# Include any dependencies generated for this target.
include CMakeFiles/tjurm-mineshaftidentify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tjurm-mineshaftidentify.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tjurm-mineshaftidentify.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tjurm-mineshaftidentify.dir/flags.make

CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o: CMakeFiles/tjurm-mineshaftidentify.dir/flags.make
CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o: /home/calbee/robomaster/TJURM-MineShaftIdentify/main.cpp
CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o: CMakeFiles/tjurm-mineshaftidentify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/calbee/robomaster/TJURM-MineShaftIdentify/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o -MF CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o.d -o CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o -c /home/calbee/robomaster/TJURM-MineShaftIdentify/main.cpp

CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calbee/robomaster/TJURM-MineShaftIdentify/main.cpp > CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.i

CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calbee/robomaster/TJURM-MineShaftIdentify/main.cpp -o CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.s

# Object files for target tjurm-mineshaftidentify
tjurm__mineshaftidentify_OBJECTS = \
"CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o"

# External object files for target tjurm-mineshaftidentify
tjurm__mineshaftidentify_EXTERNAL_OBJECTS =

tjurm-mineshaftidentify: CMakeFiles/tjurm-mineshaftidentify.dir/main.cpp.o
tjurm-mineshaftidentify: CMakeFiles/tjurm-mineshaftidentify.dir/build.make
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_gapi.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_highgui.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_ml.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_objdetect.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_photo.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_stitching.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_video.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_videoio.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_imgcodecs.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_dnn.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_calib3d.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_features2d.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_flann.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_imgproc.so.4.10.0
tjurm-mineshaftidentify: /usr/local/opencv/lib/libopencv_core.so.4.10.0
tjurm-mineshaftidentify: CMakeFiles/tjurm-mineshaftidentify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/calbee/robomaster/TJURM-MineShaftIdentify/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tjurm-mineshaftidentify"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tjurm-mineshaftidentify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tjurm-mineshaftidentify.dir/build: tjurm-mineshaftidentify
.PHONY : CMakeFiles/tjurm-mineshaftidentify.dir/build

CMakeFiles/tjurm-mineshaftidentify.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tjurm-mineshaftidentify.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tjurm-mineshaftidentify.dir/clean

CMakeFiles/tjurm-mineshaftidentify.dir/depend:
	cd /home/calbee/robomaster/TJURM-MineShaftIdentify/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calbee/robomaster/TJURM-MineShaftIdentify /home/calbee/robomaster/TJURM-MineShaftIdentify /home/calbee/robomaster/TJURM-MineShaftIdentify/build /home/calbee/robomaster/TJURM-MineShaftIdentify/build /home/calbee/robomaster/TJURM-MineShaftIdentify/build/CMakeFiles/tjurm-mineshaftidentify.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tjurm-mineshaftidentify.dir/depend

