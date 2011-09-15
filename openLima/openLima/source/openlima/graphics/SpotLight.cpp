// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/graphics/SpotLight.hpp>

using namespace openlima::util;


namespace openlima {
	namespace graphics {

		SpotLight::SpotLight(Vector3f position, Vector3f direction, Real focus, Real cutoff,
				Color ambient, Color diffuse, Color specular)
				: position(position), direction(direction), focus(focus), cutoff(cutoff),
				  ambient(ambient), diffuse(diffuse), specular(specular) {
			// Empty
		}

		SpotLight::~SpotLight() {
			// Empty
		}


		void SpotLight::setLight(u32 index) {
			GLenum lightIndex = GL_LIGHT0 + index;

			float positionFv[] = {
				(float)position.x, (float)position.y,
				(float)position.z, 1.0f
			};
			glLightfv(lightIndex, GL_POSITION, positionFv);

			float directionFv[] = {
				(float)direction.x, (float)direction.y,
				(float)direction.z, 0.0f
			};
			glLightfv(lightIndex, GL_SPOT_DIRECTION, directionFv);

			float ambientFv[] = {
				(float)ambient.r, (float)ambient.g,
				(float)ambient.b, (float)ambient.a
			};
			glLightfv(lightIndex, GL_AMBIENT, ambientFv);

			float diffuseFv[] = {
				(float)diffuse.r, (float)diffuse.g,
				(float)diffuse.b, (float)diffuse.a
			};
			glLightfv(lightIndex, GL_DIFFUSE, diffuseFv);

			float specularFv[] = {
				(float)specular.r, (float)specular.g,
				(float)specular.b, (float)specular.a
			};
			glLightfv(lightIndex, GL_SPECULAR, specularFv);

#ifdef OPENLIMA_PRECISE_REAL
			glLightf(lightIndex, GL_SPOT_CUTOFF, static_cast<float>(cutoff));
			glLightf(lightIndex, GL_SPOT_EXPONENT, static_cast<float>(focus));
#else
			glLightf(lightIndex, GL_SPOT_CUTOFF, cutoff);
			glLightf(lightIndex, GL_SPOT_EXPONENT, focus);
#endif

		}

	}
}
