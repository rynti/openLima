#ifndef OPENLIMA_GRAPHICS_MESH_HPP
#define OPENLIMA_GRAPHICS_MESH_HPP


#include "../util/macros.hpp"
#include "IRenderable.hpp"



namespace openlima {
	namespace graphics {

		class Mesh : public IRenderable {
		protected:
			L_DLL Mesh() {}

		public:
			L_DLL virtual ~Mesh() {}
			L_DLL virtual void render() = 0;
			//TODO: Modifier

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_MESH_HPP */