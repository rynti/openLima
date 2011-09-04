// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_ROTATIONNODE_HPP
#define OPENLIMA_GRAPHICS_ROTATIONNODE_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A rotating render node, which means it draws it's children rotated on the given axis by
		 * the given angle.
		 *
		 * @see RenderNode
		 */
		class RotatingRenderNode : public RenderNode {
		protected:
			
			/** The rotation angle in degrees. */
			openlima::util::Real angle;

			/** The rotation axis vector. */
			openlima::util::Vector3f axis;

		public:

			/**
			 * Creates a new rotating render node by the given parameters.
			 *
			 * @param angle	The rotation angle in degrees.
			 * @param axis	The rotation axis vector.
			 */
			OPENLIMA_DLL RotatingRenderNode(openlima::util::Real angle,
				openlima::util::Vector3f axis);
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~RotatingRenderNode();

			
			/**
			 * Renders the children of this node rotated.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_ROTATIONNODE_HPP */
