// Copyright (C) 2011 Robert Boehm
// This file is part of openLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with openLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_RENDERNODE_HPP
#define OPENLIMA_GRAPHICS_RENDERNODE_HPP

#include <boost/smart_ptr.hpp>

#include <vector>

#include <openlima/util/macros.hpp>
#include <openlima/graphics/IRenderable.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A render node that contains a list of children that all implements the IRenderable-
		 * interface.
		 *
		 * @see IRenderable
		 */
		class RenderNode : public IRenderable {
		protected:

			/** The children of this node. */
			std::vector<boost::shared_ptr<IRenderable> > children;

		public:

			/**
			 * Creates a new render node.
			 */
			OPENLIMA_DLL RenderNode();
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~RenderNode();

			
			/**
			 * Adds the given child to this node.
			 *
			 * @param child	The child that should get added to this node.
			 */
			OPENLIMA_DLL virtual void addChild(boost::shared_ptr<IRenderable> child);
			
			/**
			 * Clears this node and by that removes all children from the list.
			 */
			OPENLIMA_DLL virtual void clearChildren();
			
			/**
			 * Renders all children of this node.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_RENDERNODE_HPP */
