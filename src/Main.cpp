#include <iostream>
#include <octomap_wrapper/OctomapWrapper.hpp>
#include <octomap_wrapper/conversion.hpp>
#include <octomap/math/Utils.h>

using namespace std;
using namespace octomap;

void print_query_info(point3d query, OcTreeNode* node) {
	if (node != NULL) {
		cout << "occupancy probability at " << query << ":\t "
				<< node->getOccupancy() << endl;
	} else
		cout << "occupancy probability at " << query << ":\t is unknown"
				<< endl;
}

int main(int argc, char** argv) {
	OcTree control_tree_bt(0.1);
	OcTree control_tree_oc(0.1);
	octomap_wrapper::OctomapWrapper* wrapper_base =
			new octomap_wrapper::OctomapWrapper();
	octomap_wrapper::OctomapWrapper* wrapper_base2 =
			new octomap_wrapper::OctomapWrapper();
	// insert some measurements of occupied cells

/*	for (int x = -20; x < 20; x++) {
		for (int y = -20; y < 20; y++) {
			for (int z = -20; z < 20; z++) {
				point3d endpoint((float) x * 0.05f, (float) y * 0.05f,
						(float) z * 0.05f);
				control_tree_bt.updateNode(endpoint, true); // integrate 'occupied' measurement
			}
		}
	}

	// insert some measurements of free cells

	for (int x = -30; x < 30; x++) {
		for (int y = -30; y < 30; y++) {
			for (int z = -30; z < 30; z++) {
				point3d endpoint((float) x * 0.02f - 1.0f,
						(float) y * 0.02f - 1.0f, (float) z * 0.02f - 1.0f);
				control_tree_bt.updateNode(endpoint, false); // integrate 'free' measurement
			}
		}
	}*/

	octomap::point3d origin(0.01f, 0.01f, 0.02f);
	octomap::point3d point_on_surface(2.01f, 0.01f, 0.01f);

	cout << "generating sphere at " << origin << " ..." << endl;

	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 120; j++) {
			cout << i << endl;
			if (!control_tree_bt.insertRay(origin, origin + point_on_surface)) {
				cout << "ERROR while inserting ray from " << origin << " to "
						<< point_on_surface << endl;
			}
			point_on_surface.rotate_IP(0, 0, DEG2RAD(1.));
		}
		point_on_surface.rotate_IP(0,0,DEG2RAD(-120.));
		point_on_surface.rotate_IP(0, DEG2RAD(1.), 0);
	}


	int num_beams = 17;
		float beamLength = 3.0f;
		octomap::point3d single_origin(-6.0f, 0.45f, 0.45f);
		octomap::point3d single_endpoint(beamLength, 0.0f, 0.0f);

		for (int i = 0; i < num_beams; i++) {
			if (!control_tree_bt.insertRay(single_origin,
					single_origin + single_endpoint)) {
				std::cout << "ERROR while inserting ray from " << single_origin << " to "
						<< single_endpoint << std::endl;
			}
			single_endpoint.rotate_IP(0, 0, DEG2RAD(360.0 / num_beams));
		}


	cout << "done." << endl;

	cout << endl;
	cout << "control queries:" << endl;

	point3d query(0., 0., 0.);
	OcTreeNode* result = control_tree_bt.search(query);
	print_query_info(query, result);

	query = point3d(-1., -1., -1.);
	result = control_tree_bt.search(query);
	print_query_info(query, result);

	query = point3d(1., 1., 1.);
	result = control_tree_bt.search(query);
	print_query_info(query, result);

	cout << endl;
	control_tree_bt.writeBinary("control_tree.bt");
	cout << "wrote control file control_tree.bt" << endl << endl;
	cout << "now you can use octovis to visualize: octovis simple_tree.bt"
			<< endl;
	cout << "Hint: hit 'F'-key in viewer to see the freespace" << endl << endl;

	octomap_wrapper::binaryMapToMsg < OcTree > (control_tree_bt, *wrapper_base);

	if (wrapper_base->binary)
		cout << "binary!!!" << endl;

	OcTree* new_tree = octomap_wrapper::binaryMsgToMap(*wrapper_base);

	new_tree->writeBinary("new_tree.bt");

	return 0;
}
