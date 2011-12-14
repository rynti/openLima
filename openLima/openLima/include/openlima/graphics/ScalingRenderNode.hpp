// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_SCALENODE_HPP
#define OPENLIMA_GRAPHICS_SCALENODE_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A scaling render node, which means it draws it's children scaled.
		 *
		 * @see RenderNode
		 */
		class ScalingRenderNode : public RenderNode {
		protected:

			/** The scale vector. */
			openlima::util::Vector3f scale;

		public:
			
			/**
			 * Creates a new scaling render node by the given parameters.
			 *
			 * @param scale	The scale vector.
			 */
			OPENLIMA_DLL ScalingRenderNode(openlima::util::Vector3f scale);
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~ScalingRenderNode();

			
			/**
			 * Renders the children of this node scaled.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_SCALENODE_HPP */
