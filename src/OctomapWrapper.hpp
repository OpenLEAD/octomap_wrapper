
#ifndef OCTOMAP_WRAPPER_HEADER_FILE_H
#define OCTOMAP_WRAPPER_HEADER_FILE_H

#include <string>
#include <vector>
#include <stdint.h>
//#include <base/pose.h>

/** Adaptation of the original file from octomap_msgs from ROS*/

namespace octomap_wrapper {

class OctomapWrapper {
public:

 OctomapWrapper(){

 };

 ~OctomapWrapper(){};

 //Origin (in m) of the map


// Flag to denote a binary (only free/occupied) or full occupancy octree (.bt/.ot file)
	bool binary;

// Class id of the contained octree
	std::string id;

//Resolution (in m) of the smallest octree nodes
	double resolution;

//binary serialization of octree, use conversions.h to read and write octrees
	std::vector<int8_t> data;
};

}
#endif
