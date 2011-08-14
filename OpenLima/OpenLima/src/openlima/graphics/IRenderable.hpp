#ifndef OPENLIMA_GRAPHICS_IRENDERABLE_HPP
#define OPENLIMA_GRAPHICS_IRENDERABLE_HPP


#include "../util/macros.hpp"



namespace openlima {
	namespace graphics {

		class IRenderable {
		protected:
			OPENLIMA_DLL IRenderable() {}

		public:
			OPENLIMA_DLL virtual ~IRenderable() {}
			OPENLIMA_DLL virtual void render() = 0;

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_IRENDERABLE_HPP */