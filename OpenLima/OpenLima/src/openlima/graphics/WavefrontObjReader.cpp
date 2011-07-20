#include <iostream>
#include <fstream>
#include <vector>

#include "../util/Vector3.hpp"
#include "WavefrontObjReader.hpp"
#include "StaticMesh.hpp"


using namespace std;
using namespace openlima::util;

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
			vector<Vector3f> normals;
			vector<Vector3i> vertexIndices;
			vector<Vector3i> normalIndices;

			float x, y, z;
			int v1, v2, v3, n1, n2, n3;

			while(in.good()) {
				in.getline(linebuffer, LINEBUFFER_SIZE);
				switch(linebuffer[0]) {
				case 'v':
					switch(linebuffer[1]) {
					case 'n':
						sscanf_s(linebuffer, "vn %f %f %f", &x, &y, &z);
						normals.push_back(Vector3f(x, y, z));
						break;
					default:
						sscanf_s(linebuffer, "v %f %f %f", &x, &y, &z);
						vertices.push_back(Vector3f(x, y, z));
						break;
					}
					break;
				case 'f':
					sscanf_s(linebuffer, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
					vertexIndices.push_back(Vector3i(v1, v2, v3));
					normalIndices.push_back(Vector3i(n1, n2, n3));
					break;
				}
			}

			Vector3f* pVertices = new Vector3f[vertices.size()];
			for(size_t i = 0; i < vertices.size(); i++)
				pVertices[i] = vertices.at(i);

			Vector3f* pNormals = new Vector3f[normals.size()];
			for(size_t i = 0; i < normals.size(); i++)
				pNormals[i] = normals.at(i);

			Vector3i* pVertexIndices = new Vector3i[vertexIndices.size()];
			for(size_t i = 0; i < vertexIndices.size(); i++)
				pVertexIndices[i] = vertexIndices.at(i);

			Vector3i* pNormalIndices = new Vector3i[normalIndices.size()];
			for(size_t i = 0; i < normalIndices.size(); i++)
				pNormalIndices[i] = normalIndices.at(i);

			return new StaticMesh(pVertices, vertices.size(), pNormals, normals.size(),
				pVertexIndices, vertexIndices.size(), pNormalIndices, normalIndices.size());
		}

	}
}