// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_TRANSLATIONNODE_HPP
#define OPENLIMA_GRAPHICS_TRANSLATIONNODE_HPP

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/graphics/RenderNode.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A translating render node, which means it draws it's children translated.
		 *
		 * @see RenderNode
		 */
		class TranslatingRenderNode : public RenderNode {
		protected:

			/** The translation vector. */
			openlima::util::Vector3f translation;

		public:

			/**
			 * Creates a new translating render node by the given parameters.
			 *
			 * @param translation	The translation vector.
			 */
			OPENLIMA_DLL TranslatingRenderNode(openlima::util::Vector3f translation);
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~TranslatingRenderNode();

			
			/**
			 * Renders the children of this node translated.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_TRANSLATIONNODE_HPP */
