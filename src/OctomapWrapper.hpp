#ifndef OCTOMAP_WRAPPER_HEADER_FILE_H
#define OCTOMAP_WRAPPER_HEADER_FILE_H

#include <base/Time.hpp>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>

/** Adaptation of the original file from octomap_msgs from ROS*/

namespace octomap_wrapper {

class OctomapWrapper {
public:

        OctomapWrapper() {};
        ~OctomapWrapper(){};

        // Timestamp for this octomap
        //
        // This is the timestamp of the data that got added last in the map
        base::Time time;

        // Flag to denote a binary (only free/occupied) or full occupancy octree (.bt/.ot file)
        bool binary;

        // Class id of the contained octree
        std::string id;

        // Resolution (in m) of the smallest octree nodes
        double resolution;

        // binary serialization of octree, use Conversion.hpp to read and write octrees
        std::vector<boost::int8_t> data;
};

}
#endif
