#ifndef OPENLIMA_GRAPHICS_IRENDERABLE_HPP
#define OPENLIMA_GRAPHICS_IRENDERABLE_HPP


#include "../util/macros.hpp"



namespace openlima {
	namespace graphics {

		class IRenderable {
		protected:
			L_DLL IRenderable() {}

		public:
			L_DLL virtual ~IRenderable() {}
			L_DLL virtual void render() = 0;

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_IRENDERABLE_HPP */