// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_POINTLIGHT_HPP
#define OPENLIMA_GRAPHICS_POINTLIGHT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/ILight.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A point light.
		 *
		 * @see ILight
		 */
		class PointLight : public ILight {
		public:

			/** The source position of this light. */
			openlima::util::Vector3f position;

			/** The ambient color of this light. */
			openlima::util::Color ambient;

			/** The diffuse color of this light. */
			openlima::util::Color diffuse;

			/** The specular color of this light. */
			openlima::util::Color specular;

			
			/**
			 * Creates a new pointlight.
			 *
			 * @param position	The source position of this light.
			 * @param ambient	The ambient color of this light.
			 * @param diffuse	The diffuse color of this light.
			 * @param specular	The specular color of this light.
			 */
			OPENLIMA_DLL PointLight(
				openlima::util::Vector3f position,
				openlima::util::Color ambient,
				openlima::util::Color diffuse,
				openlima::util::Color specular);
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~PointLight();

			
			/**
			 * Defines the properties of the light with the given index.
			 *
			 * @param index	The index of this light.
			 */
			OPENLIMA_DLL virtual void setLight(openlima::util::u32 index);

		};
		
	}
}

#endif /* OPENLIMA_GRAPHICS_POINTLIGHT_HPP */