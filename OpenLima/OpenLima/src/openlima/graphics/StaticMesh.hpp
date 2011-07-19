#ifndef OPENLIMA_GRAPHICS_STATICMESH_HPP
#define OPENLIMA_GRAPHICS_STATICMESH_HPP


#include "../util/macros.hpp"
#include "../util/Vector3.hpp"
#include "../util/Vector3i.hpp"
#include "../util/Vector3f.hpp"
#include "../util/IReader.hpp"
#include "Mesh.hpp"



namespace openlima {
	namespace graphics {

		class StaticMesh : public Mesh {
			friend class IReader<StaticMesh>;
		
		//private:
			
		public:
			Vector3f* pVertices;
			size_t nVertices;

			Vector3i* pFaces;
			size_t nFaces;

			L_DLL StaticMesh(Vector3f* pVertices, size_t nVertices, Vector3i* pFaces, size_t nFaces);

			L_DLL virtual void render();

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_STATICMESH_HPP */