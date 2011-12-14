// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_ILIGHT_HPP
#define OPENLIMA_GRAPHICS_ILIGHT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/graphics/IRenderable.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * An interface for lights. Has a setLight(int)-method that should be called to setup the
		 * lightning properties.
		 */
		class ILight {
		public:

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~ILight() {}

			
			/**
			 * Defines the properties of the light with the given index.
			 *
			 * @param index	The index of this light.
			 */
			OPENLIMA_DLL virtual void setLight(openlima::util::u32 index) = 0;

		};
		
	}
}

#endif /* OPENLIMA_GRAPHICS_ILIGHT_HPP */