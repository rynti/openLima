// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/StaticMesh.hpp>

using namespace std;
using namespace openlima::util;


namespace openlima {
	namespace graphics {

		StaticMesh::StaticMesh(vector<openlima::util::Vector3f> vertices,
			vector<openlima::util::Vector3f> normals,
			vector<openlima::util::Vector3i> vertexIndices,
			vector<openlima::util::Vector3i> normalIndices,
			bool smoothShading/* = true*/)
			: vertices(vertices), normals(normals), vertexIndices(vertexIndices),
			  normalIndices(normalIndices), smoothShading(smoothShading) {
		}

		void StaticMesh::render() {
			glBegin(GL_TRIANGLES);

			if(vertices.size() != 0) {
				if(normals.size() != 0) {
					// Render with vertices and normals
					renderVerticesAndNormals();
				} else {
					// Render only with vertices
					renderVertices();
				}
			}

			glEnd();
		}

		void StaticMesh::renderVertices() {
			const Vector3i* faceVertex;
			const Vector3f* vertex;
			for(size_t i = 0; i < vertexIndices.size(); i++) {

				faceVertex = &this->vertexIndices.at(i);

#ifdef OPENLIMA_PRECISE_REAL
				vertex = &this->vertices.at(faceVertex->x);
				glVertex3d(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->y);
				glVertex3d(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->z);
				glVertex3d(vertex->x, vertex->y, vertex->z);
#else
				vertex = &this->vertices.at(faceVertex->x);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->y);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);
#endif

			}
		}

		void StaticMesh::renderVerticesAndNormals() {
			const Vector3i* faceVertex;
			const Vector3i* faceNormal;
			const Vector3f* vertex;
			const Vector3f* normal;
			for(size_t i = 0; i < vertexIndices.size(); i++) {

				faceVertex = &this->vertexIndices.at(i);
				faceNormal = &this->normalIndices.at(i);

#ifdef OPENLIMA_PRECISE_REAL

				vertex = &this->vertices.at(faceVertex->x);
				normal = &this->normals.at(faceNormal->x);
				glNormal3d(normal->x, normal->y, normal->z);
				glVertex3d(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->y);
				normal = &this->normals.at(faceNormal->y);
				glNormal3d(normal->x, normal->y, normal->z);
				glVertex3d(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->z);
				normal = &this->normals.at(faceNormal->z);
				glNormal3d(normal->x, normal->y, normal->z);
				glVertex3d(vertex->x, vertex->y, vertex->z);

#else

				vertex = &this->vertices.at(faceVertex->x);
				normal = &this->normals.at(faceNormal->x);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->y);
				normal = &this->normals.at(faceNormal->y);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->vertices.at(faceVertex->z);
				normal = &this->normals.at(faceNormal->z);
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

#endif

			}
		}

	}
}
