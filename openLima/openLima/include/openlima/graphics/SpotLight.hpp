// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_SPOTLIGHT_HPP
#define OPENLIMA_GRAPHICS_SPOTLIGHT_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/ILight.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * A spot light.
		 *
		 * @see ILight
		 */
		class SpotLight : public ILight {
		public:

			/** The source position of this light. */
			openlima::util::Vector3f position;

			/** The direction of this light. */
			openlima::util::Vector3f direction;

			/** A focus exponent, the higher the more focused this spot light is. */
			openlima::util::Real focus;

			/** The angle of this light. */
			openlima::util::Real cutoff;

			/** The ambient color of this light. */
			openlima::util::Color ambient;

			/** The diffuse color of this light. */
			openlima::util::Color diffuse;

			/** The specular color of this light. */
			openlima::util::Color specular;


			/**
			 * Creates a new spotlight.
			 *
			 * @param position	The source position of this light.
			 * @param direction	The direction of this light.
			 * @param focus		A focus exponent, the higher the more focused this spot light is.
			 * @param cutoff	The angle of this light.
			 * @param ambient	The ambient color of this light.
			 * @param diffuse	The diffuse color of this light.
			 * @param specular	The specular color of this light.
			 */
			OPENLIMA_DLL SpotLight(
				openlima::util::Vector3f position,
				openlima::util::Vector3f direction,
				openlima::util::Real focus,
				openlima::util::Real cutoff,
				openlima::util::Color ambient,
				openlima::util::Color diffuse,
				openlima::util::Color specular);

			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~SpotLight();

			
			/**
			 * Defines the properties of the light with the given index.
			 *
			 * @param index	The index of this light.
			 */
			OPENLIMA_DLL virtual void setLight(openlima::util::u32 index);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_SPOTLIGHT_HPP */