# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/samox/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/samox/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/samox/gitlab/cpp/notifire

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samox/gitlab/cpp/notifire/cmake-build-debug

# Include any dependencies generated for this target.
include lib/xpp/CMakeFiles/xpp.dir/depend.make

# Include the progress variables for this target.
include lib/xpp/CMakeFiles/xpp.dir/progress.make

# Include the compile flags for this target's objects.
include lib/xpp/CMakeFiles/xpp.dir/flags.make

lib/xpp/generated-sources/include/xpp/proto/composite.hpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/samox/gitlab/cpp/notifire/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating generated-sources/include/xpp/proto/composite.hpp"
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && /usr/bin/python3 /home/samox/gitlab/cpp/notifire/lib/xpp/generators/cpp_client.py -p /usr/lib/python3.9/site-packages //usr/share/xcb/composite.xml > /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp/generated-sources/include/xpp/proto/composite.hpp

lib/xpp/generated-sources/include/xpp/proto/randr.hpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/samox/gitlab/cpp/notifire/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating generated-sources/include/xpp/proto/randr.hpp"
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && /usr/bin/python3 /home/samox/gitlab/cpp/notifire/lib/xpp/generators/cpp_client.py -p /usr/lib/python3.9/site-packages //usr/share/xcb/randr.xml > /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp/generated-sources/include/xpp/proto/randr.hpp

lib/xpp/generated-sources/include/xpp/proto/xkb.hpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/samox/gitlab/cpp/notifire/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating generated-sources/include/xpp/proto/xkb.hpp"
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && /usr/bin/python3 /home/samox/gitlab/cpp/notifire/lib/xpp/generators/cpp_client.py -p /usr/lib/python3.9/site-packages //usr/share/xcb/xkb.xml > /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp/generated-sources/include/xpp/proto/xkb.hpp

lib/xpp/generated-sources/include/xpp/proto/x.hpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/samox/gitlab/cpp/notifire/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating generated-sources/include/xpp/proto/x.hpp"
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && /usr/bin/python3 /home/samox/gitlab/cpp/notifire/lib/xpp/generators/cpp_client.py -p /usr/lib/python3.9/site-packages //usr/share/xcb/xproto.xml > /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp/generated-sources/include/xpp/proto/x.hpp

# Object files for target xpp
xpp_OBJECTS =

# External object files for target xpp
xpp_EXTERNAL_OBJECTS =

lib/xpp/libxpp.a: lib/xpp/CMakeFiles/xpp.dir/build.make
lib/xpp/libxpp.a: lib/xpp/CMakeFiles/xpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/samox/gitlab/cpp/notifire/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libxpp.a"
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && $(CMAKE_COMMAND) -P CMakeFiles/xpp.dir/cmake_clean_target.cmake
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/xpp/CMakeFiles/xpp.dir/build: lib/xpp/libxpp.a

.PHONY : lib/xpp/CMakeFiles/xpp.dir/build

lib/xpp/CMakeFiles/xpp.dir/clean:
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp && $(CMAKE_COMMAND) -P CMakeFiles/xpp.dir/cmake_clean.cmake
.PHONY : lib/xpp/CMakeFiles/xpp.dir/clean

lib/xpp/CMakeFiles/xpp.dir/depend: lib/xpp/generated-sources/include/xpp/proto/composite.hpp
lib/xpp/CMakeFiles/xpp.dir/depend: lib/xpp/generated-sources/include/xpp/proto/randr.hpp
lib/xpp/CMakeFiles/xpp.dir/depend: lib/xpp/generated-sources/include/xpp/proto/xkb.hpp
lib/xpp/CMakeFiles/xpp.dir/depend: lib/xpp/generated-sources/include/xpp/proto/x.hpp
	cd /home/samox/gitlab/cpp/notifire/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samox/gitlab/cpp/notifire /home/samox/gitlab/cpp/notifire/lib/xpp /home/samox/gitlab/cpp/notifire/cmake-build-debug /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp /home/samox/gitlab/cpp/notifire/cmake-build-debug/lib/xpp/CMakeFiles/xpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/xpp/CMakeFiles/xpp.dir/depend

