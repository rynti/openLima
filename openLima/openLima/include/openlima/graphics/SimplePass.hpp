// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_SIMPLEPASS_HPP
#define OPENLIMA_GRAPHICS_SIMPLEPASS_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/util/Color.hpp>
#include <openlima/graphics/IPass.hpp>


namespace openlima {
	namespace graphics {

		class SimplePass : public IPass {
		private:
			float* ambient;
			float* diffuse;
			float* specular;
			float* emission;
			float shininess;

		public:
			OPENLIMA_DLL SimplePass(openlima::util::Color ambient, openlima::util::Color diffuse,
				openlima::util::Color specular, openlima::util::Color emission, float shininess);

			OPENLIMA_DLL virtual ~SimplePass();


			OPENLIMA_DLL virtual void setProperties();

			OPENLIMA_DLL virtual void unsetProperties();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_SIMPLEPASS_HPP */