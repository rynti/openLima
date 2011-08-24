// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/algorithm/string.hpp>

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

		bool WavefrontObjReader::isLegal(const std::string& name) {
			return boost::algorithm::ends_with(name, std::string(".obj"));
		}

		boost::shared_ptr<StaticMesh> WavefrontObjReader::readResource(std::istream &in) {
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
					readFace(in, vertexIndices, normalIndices, vertices, normals);
				} else {
					std::getline(in, commandType);
				}
				commandType.clear();
			}

			for(size_t i = 0; i < vertexIndices.size(); i++) {
				if(normalIndices[i].x == -1) {
					// Generate normal
					Vector3f surfaceNormal = Vector3f::computeSurfaceNormal(
						vertices[vertexIndices[i].x],
						vertices[vertexIndices[i].y],
						vertices[vertexIndices[i].z]);

					std::cout << "Surface: (" <<
						surfaceNormal.x << " | " <<
						surfaceNormal.y << " | " <<
						surfaceNormal.z << ")" << std::endl;

					std::cout << "  p1: (" <<
						vertices[vertexIndices[i].x].x << " | " <<
						vertices[vertexIndices[i].x].y << " | " <<
						vertices[vertexIndices[i].x].z << ")" << std::endl;

					std::cout << "  p2: (" <<
						vertices[vertexIndices[i].y].x << " | " <<
						vertices[vertexIndices[i].y].y << " | " <<
						vertices[vertexIndices[i].y].z << ")" << std::endl;

					std::cout << "  p3: (" <<
						vertices[vertexIndices[i].z].x << " | " <<
						vertices[vertexIndices[i].z].y << " | " <<
						vertices[vertexIndices[i].z].z << ")" << std::endl;

					std::cout << std::endl;

					// Check if this normal already exists
					int normalIndex = -1;
					for(size_t j = 0; j < normals.size(); j++) {
						if(normals[j] == surfaceNormal) {
							normalIndex = j;
							break;
						}
					}
					if(normalIndex < 0) {
						// If not, create it
						normalIndex = normals.size();
						normals.push_back(surfaceNormal);
					}

					normalIndices[i].x = normalIndex;
					normalIndices[i].y = normalIndex;
					normalIndices[i].z = normalIndex;
				}
			}

			return boost::make_shared<StaticMesh>(vertices, normals, vertexIndices, normalIndices);
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
				std::vector<Vector3i>& normalIndices, std::vector<Vector3f>& vertices,
				std::vector<Vector3f>& normals) {
			int v1, v2, v3, n1, n2, n3, temp;
			int num = readFacePart(in, v1, temp, n1);
			readFacePart(in, v2, temp, n2);
			readFacePart(in, v3, temp, n3);

			vertexIndices.push_back(Vector3i(--v1, --v2, --v3));
			if((num & 1) != 0) {
				// Texture index
			}
			if((num & 2) != 0) {
				// Normal index
				normalIndices.push_back(Vector3i(--n1, --n2, --n3));
			} else {
				// Missing normal
				normalIndices.push_back(Vector3i(-1, -1, -1));
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
