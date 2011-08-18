// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_IRENDERABLE_HPP
#define OPENLIMA_GRAPHICS_IRENDERABLE_HPP

#include "../util/macros.hpp"


namespace openlima {
	namespace graphics {

		/**
		 * Marks a class renderable, which means it can be rendered on the screen.
		 */
		class IRenderable {
		protected:

			/**
			 * Makes this class not instanceable, use specializations instead.
			 */
			OPENLIMA_DLL IRenderable() {}

		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~IRenderable() {}


			/**
			 * Renders this object.
			 */
			OPENLIMA_DLL virtual void render() = 0;

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_IRENDERABLE_HPP */
