rock_library(octomap_wrapper
	SOURCES OctomapWrapper.cpp
    HEADERS OctomapWrapper.hpp
    		conversion.hpp
    DEPS_CMAKE octomap
    DEPS_PKGCONFIG base-types )


