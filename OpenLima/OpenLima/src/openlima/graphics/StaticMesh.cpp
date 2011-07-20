#include <GL/freeglut.h>

#include "StaticMesh.hpp"


using namespace openlima::util;

namespace openlima {
	namespace graphics {

		StaticMesh::StaticMesh(Vector3f* pVertices, size_t nVertices, Vector3f* pNormals, size_t nNormals,
				Vector3i* pVertexIndices, size_t nVertexIndices, Vector3i* pNormalIndices, size_t nNormalIndices) {
			this->pVertices = pVertices;
			this->nVertices = nVertices;
			this->pNormals = pNormals;
			this->nNormals = nNormals;
			this->pVertexIndices = pVertexIndices;
			this->nVertexIndices = nVertexIndices;
			this->pNormalIndices = pNormalIndices;
			this->nNormalIndices = nNormalIndices;
		}

		void StaticMesh::render() {

			glBegin(GL_TRIANGLES);

			Vector3i* faceVertex;
			Vector3i* faceNormal;
			Vector3f* vertex;
			Vector3f* normal;
			for(size_t i = 0; i < nVertexIndices; i++) {

				faceVertex = &this->pVertexIndices[i];
				faceNormal = &this->pNormalIndices[i];

				vertex = &this->pVertices[faceVertex->x - 1];
				normal = &this->pNormals[faceNormal->x - 1];
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->pVertices[faceVertex->y - 1];
				normal = &this->pNormals[faceNormal->y - 1];
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->pVertices[faceVertex->z - 1];
				normal = &this->pNormals[faceNormal->y - 1];
				glNormal3f(normal->x, normal->y, normal->z);
				glVertex3f(vertex->x, vertex->y, vertex->z);

			}

			glEnd();

		}

	}
}