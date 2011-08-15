// Copyright (C) 2011 Robert Böhm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
			vector<Vector3f> vertices;
			vector<Vector3f> normals;
			vector<Vector3i> vertexIndices;
			vector<Vector3i> normalIndices;

			std::string commandType;

			while(in.good()) {
				in >> commandType;
				if(commandType == "v") {
					readVertex(in, vertices);
				} else if(commandType == "vn") {
					readNormal(in, normals);
				} else if(commandType == "f") {
					readFace(in, vertexIndices, normalIndices);
				} else {
					std::getline(in, commandType);
				}
				commandType.clear();
			}

			return new StaticMesh(vertices, normals, vertexIndices, normalIndices);
		}

		void WavefrontObjReader::readVertex(std::istream &in, std::vector<Vector3f>& vertices) {
			float x, y, z;
			in >> x >> y >> z;
			vertices.push_back(Vector3f(x, y, z));
		}

		void WavefrontObjReader::readNormal(std::istream &in, std::vector<Vector3f>& normals) {
			float x, y, z;
			in >> x >> y >> z;
			normals.push_back(Vector3f(x, y, z));
		}

		void WavefrontObjReader::readFace(std::istream &in, std::vector<Vector3i>& vertexIndices,
				std::vector<Vector3i>& normalIndices) {
			int v1, v2, v3, n1, n2, n3, temp;
			int num = readFacePart(in, v1, temp, n1);
			readFacePart(in, v2, temp, n2);
			readFacePart(in, v3, temp, n3);
			vertexIndices.push_back(Vector3i(v1, v2, v3));
			if((num & 1) != 0) {
				// Texture index
			}
			if((num & 2) != 0) {
				normalIndices.push_back(Vector3i(n1, n2, n3));
			}
		}

		int WavefrontObjReader::readFacePart(std::istream &in,
				int& vertex, int& texture, int& normal) {
			in >> vertex;
			if(in.get() == '/') {
				if(in.peek() == '/') {
					in.get();
					in >> normal;
					return 2;
				} else {
					in >> texture;
					if(in.get() == '/') {
						in >> normal;
						return 3;
					} else {
						return 2;
					}
				}
			} else {
				return 0;
			}
		}

	}
}