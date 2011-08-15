// Copyright (C) 2011 Robert Böhm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

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