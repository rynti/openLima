// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <GL/freeglut.h>

#include "StaticMesh.hpp"


using namespace std;
using namespace openlima::util;

namespace openlima {
	namespace graphics {

		StaticMesh::StaticMesh(vector<openlima::util::Vector3f> vertices,
			vector<openlima::util::Vector3f> normals,
			vector<openlima::util::Vector3i> vertexIndices,
			vector<openlima::util::Vector3i> normalIndices) {
			this->vertices = vertices;
			this->normals = normals;
			this->vertexIndices = vertexIndices;
			this->normalIndices = normalIndices;
		}

		void StaticMesh::render() {

			glBegin(GL_TRIANGLES);

			Vector3i* faceVertex;
			Vector3i* faceNormal;
			Vector3f* vertex;
			Vector3f* normal;
			for(size_t i = 0; i < vertexIndices.size(); i++) {

				faceVertex = &this->vertexIndices.at(i);
				faceNormal = &this->normalIndices.at(i);

				vertex = &this->vertices.at(faceVertex->x - 1);
				normal = &this->normals.at(faceNormal->x - 1);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->y - 1);
				normal = &this->normals.at(faceNormal->y - 1);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->z - 1);
				normal = &this->normals.at(faceNormal->y - 1);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

			}

			glEnd();

		}

	}
}