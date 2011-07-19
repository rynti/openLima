#include <GL/freeglut.h>

#include "StaticMesh.hpp"


namespace openlima {
	namespace graphics {

		StaticMesh::StaticMesh(Vector3f* pVertices, size_t nVertices, Vector3i* pFaces, size_t nFaces) {
			this->pVertices = pVertices;
			this->nVertices = nVertices;
			this->pFaces = pFaces;
			this->nFaces = nFaces;
		}

		void StaticMesh::render() {

			glBegin(GL_TRIANGLES);

			Vector3i* face;
			Vector3f* vertex;
			for(size_t i = 0; i < nFaces; i++) {

				face = &this->pFaces[i];
				vertex = &this->pVertices[face->x - 1];
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->pVertices[face->y - 1];
				glVertex3f(vertex->x, vertex->y, vertex->z);

				vertex = &this->pVertices[face->z - 1];
				glVertex3f(vertex->x, vertex->y, vertex->z);

			}

			glEnd();

		}

	}
}