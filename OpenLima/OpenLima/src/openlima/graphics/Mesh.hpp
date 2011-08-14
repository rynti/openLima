#ifndef OPENLIMA_GRAPHICS_MESH_HPP
#define OPENLIMA_GRAPHICS_MESH_HPP


#include "../util/macros.hpp"
#include "IRenderable.hpp"



namespace openlima {
	namespace graphics {

		class Mesh : public IRenderable {
		protected:
			OPENLIMA_DLL Mesh() {}

		public:
			OPENLIMA_DLL virtual ~Mesh() {}
			OPENLIMA_DLL virtual void render() = 0;
			//TODO: Modifier

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_MESH_HPP */