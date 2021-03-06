// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_IPROJECTIONMODIFIER_HPP
#define OPENLIMA_GRAPHICS_IPROJECTIONMODIFIER_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector2.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * An interface for projection modifiers.
		 */
		class IProjectionModifier {
		public:
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~IProjectionModifier() {}

			
			/**
			 * Modifies the projection matrix. The dimensions are sometimes needed for instance to
			 * calculate aspect ratios.
			 *
			 * @param dimensions	The screen dimensions
			 */
			OPENLIMA_DLL virtual void modifyProjection(openlima::util::Vector2i dimensions) const
				= 0;

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_IPROJECTIONMODIFIER_HPP */
