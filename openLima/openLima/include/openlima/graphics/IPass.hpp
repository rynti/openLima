// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_IPASS_HPP
#define OPENLIMA_GRAPHICS_IPASS_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>


namespace openlima {
	namespace graphics {

		class IPass {
		public:

			OPENLIMA_DLL virtual ~IPass() {}


			OPENLIMA_DLL virtual void setProperties() = 0;

			OPENLIMA_DLL virtual void unsetProperties() = 0;

		};
		
	}
}

#endif /* OPENLIMA_GRAPHICS_IPASS_HPP */