#include <iostream>
#include <fstream>
#include <vector>

#include "../util/Vector3.hpp"
#include "WavefrontObjReader.hpp"
#include "StaticMesh.hpp"


using namespace std;

namespace openlima {
	namespace graphics {

		StaticMesh* WavefrontObjReader::readStatic(char* filename) {
			ifstream ifs(filename, ifstream::in);
			StaticMesh* mesh = readStatic(ifs);
			ifs.close();
			return mesh;
		}

		StaticMesh* WavefrontObjReader::readStatic(std::istream &in) {
			char* linebuffer = new char[LINEBUFFER_SIZE];

			vector<Vector3f> vertices;
			vector<Vector3i> faces;

			while(in.good()) {
				in.getline(linebuffer, LINEBUFFER_SIZE);
				switch(linebuffer[0]) {
				case 'v':
					float x, y, z;
					sscanf_s(linebuffer, "v %f %f %f", &x, &y, &z);
					vertices.push_back(Vector3f(x, y, z));
					break;
				case 'f':
					int v1, v2, v3;
					sscanf_s(linebuffer, "f %d %d %d", &v1, &v2, &v3);
					faces.push_back(Vector3i(v1, v2, v3));
					break;
				}
			}

			Vector3f* pVertices = new Vector3f[vertices.size()];
			for(size_t i = 0; i < vertices.size(); i++)
				pVertices[i] = vertices.at(i);

			Vector3i* pFaces = new Vector3i[faces.size()];
			for(size_t i = 0; i < faces.size(); i++)
				pFaces[i] = faces.at(i);

			return new StaticMesh(pVertices, vertices.size(), pFaces, faces.size());
		}

	}
}