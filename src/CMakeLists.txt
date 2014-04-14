rock_library(octomap_wrapper
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp
    		OctomapWrapper.hpp
    		conversion.hpp
    DEPS_CMAKE octomap)

rock_executable(octomap_wrapper_bin Main.cpp
    DEPS octomap_wrapper)

