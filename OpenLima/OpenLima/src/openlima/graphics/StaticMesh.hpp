#ifndef OPENLIMA_GRAPHICS_STATICMESH_HPP
#define OPENLIMA_GRAPHICS_STATICMESH_HPP


#include "../util/macros.hpp"
#include "../util/Vector3.hpp"
#include "../util/Vector3i.hpp"
#include "../util/Vector3f.hpp"
#include "Mesh.hpp"


namespace openlima {
	namespace graphics {

		class StaticMesh : public Mesh {
		public:
			openlima::util::Vector3f* pVertices;
			size_t nVertices;

			openlima::util::Vector3f* pNormals;
			size_t nNormals;

			openlima::util::Vector3i* pVertexIndices;
			size_t nVertexIndices;

			openlima::util::Vector3i* pNormalIndices;
			size_t nNormalIndices;

			L_DLL StaticMesh(openlima::util::Vector3f* pVertices, size_t nVertices, openlima::util::Vector3f* pNormals, size_t nNormals,
				openlima::util::Vector3i* pVertexIndices, size_t nVertexIndices, openlima::util::Vector3i* pNormalIndices, size_t nNormalIndices);

			L_DLL virtual void render();

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_STATICMESH_HPP */