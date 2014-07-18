#ifndef OCTOMAP_WRAPPER_CONVERT_MSGS_H
#define OCTOMAP_WRAPPER_CONVERT_MSGS_H

#include "octomap/OcTree.h"
#include "octomap/AbstractOcTree.h"
#include <octomap_wrapper/OctomapWrapper.hpp>
#include <sstream>
#include <stdint.h>
#include <vector>

/**
 * Adaptation from conversion.h from octomap_msg
 */

// new conversion functions
namespace octomap_wrapper {
// Note: fullMsgDataToMap() deleted, potentially causes confusion
// and (silent) errors in deserialization

/**
 * @brief Creates a new octree by deserializing from a message that contains the
 * full map information (i.e., binary is false) and returns an AbstractOcTree*
 * to it. You will need to free the memory when you're done.
 */
static inline octomap::AbstractOcTree* fullMsgToMap(
		const OctomapWrapper& wrapper) {
	octomap::AbstractOcTree* tree = octomap::AbstractOcTree::createTree(
			wrapper.id, wrapper.resolution);
	if (tree) {
		std::stringstream datastream;
		assert(wrapper.data.size() > 0);
		datastream.write((const char*) &wrapper.data[0], wrapper.data.size());
		tree->readData(datastream);
	}

	return tree;
}

/**
 * @brief Creates a new octree by deserializing from msg,
 * e.g. from a message or service (binary: only free and occupied .bt file format).
 * This creates a new OcTree object and returns a pointer to it.
 * You will need to free the memory when you're done.
 */
static inline octomap::OcTree* binaryMsgToMap(const OctomapWrapper& wrapper) {
	if (wrapper.id != "OcTree" || !wrapper.binary)
		return NULL;

	octomap::OcTree* octree = new octomap::OcTree(wrapper.resolution);
	std::stringstream datastream;
	assert(wrapper.data.size() > 0);
	datastream.write((const char*) &wrapper.data[0], wrapper.data.size());
	octree->readBinaryData(datastream);

	return octree;
}

// Note: binaryMsgDataToMap() deleted, potentially causes confusion
// and (silent) errors in deserialization

/**
 * \brief Convert an octomap representation to a new octree (full probabilities
 * or binary). You will need to free the memory. Return NULL on error.
 **/
static inline octomap::AbstractOcTree* msgToMap(const OctomapWrapper& wrapper) {
	if (wrapper.binary)
		return binaryMsgToMap(wrapper);
	else
		return fullMsgToMap(wrapper);
}

// conversions via stringstream

// TODO: read directly into buffer? see
// http://stackoverflow.com/questions/132358/how-to-read-file-content-into-istringstream

/**
 * @brief Serialization of an octree into binary data e.g. for messages and services.
 * Compact binary version (stores only max-likelihood free or occupied, .bt file format).
 * The data will be much smaller if you call octomap.toMaxLikelihood() and octomap.prune()
 * before.
 * @return success of serialization
 */
template<class OctomapT>
static inline bool binaryMapToMsgData(const OctomapT& octomap,
		std::vector<int8_t>& mapData) {
	std::stringstream datastream;
	if (!octomap.writeBinaryConst(datastream))
		return false;

	std::string datastring = datastream.str();
	mapData = std::vector < int8_t > (datastring.begin(), datastring.end());
	return true;
}

/**
 * @brief Serialization of an octree into binary data e.g. for messages and services.
 * Full probability version (stores complete state of tree, .ot file format).
 * The data will be much smaller if you call octomap.toMaxLikelihood() and octomap.prune()
 * before.
 * @return success of serialization
 */
template<class OctomapT>
static inline bool fullMapToMsgData(const OctomapT& octomap,
		std::vector<int8_t>& mapData) {
	std::stringstream datastream;
	if (!octomap.write(datastream))
		return false;

	std::string datastring = datastream.str();
	mapData = std::vector < int8_t > (datastring.begin(), datastring.end());
	return true;
}

/**
 * @brief Serialization of an octree into binary data e.g. for messages and services.
 * Compact binary version (stores only max-likelihood free or occupied, .bt file format).
 * The data will be much smaller if you call octomap.toMaxLikelihood() and octomap.prune()
 * before.
 * @return success of serialization
 */
template<class OctomapT>
static inline bool binaryMapToMsg(const OctomapT& octomap,
		OctomapWrapper& wrapper) {
	wrapper.resolution = octomap.getResolution();
	wrapper.id = octomap.getTreeType();
	wrapper.binary = true;

	std::stringstream datastream;
	if (!octomap.writeBinaryData(datastream))
		return false;

	std::string datastring = datastream.str();
	wrapper.data = std::vector < int8_t
			> (datastring.begin(), datastring.end());
	return true;
}

/**
 * @brief Serialization of an octree into binary data e.g. for messages and services.
 * Full probability version (stores complete state of tree, .ot file format).
 * The data will be much smaller if you call octomap.toMaxLikelihood() and octomap.prune()
 * before.
 * @return success of serialization
 */
template<class OctomapT>
static inline bool fullMapToMsg(const OctomapT& octomap,
		OctomapWrapper& wrapper) {
	wrapper.resolution = octomap.getResolution();
	wrapper.id = octomap.getTreeType();
	wrapper.binary = false;

	std::stringstream datastream;
	if (!octomap.writeData(datastream))
		return false;

	std::string datastring = datastream.str();
	wrapper.data = std::vector < int8_t
			> (datastring.begin(), datastring.end());
	return true;
}

}

#endif
