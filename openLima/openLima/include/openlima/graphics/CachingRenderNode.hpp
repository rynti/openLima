// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_CACHEDNODE_HPP
#define OPENLIMA_GRAPHICS_CACHEDNODE_HPP

#include <boost/smart_ptr.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/graphics/RenderNode.hpp>
#include <openlima/graphics/IRenderable.hpp>


namespace openlima {
	namespace graphics {
		
		/**
		 * A rendering node that caches what it draws and with that it increases the performance of
		 * static models significantly.
		 * 
		 * @see RenderNode
		 */
		class CachingRenderNode : public RenderNode {
		private:

			/** The display list identifier. */
			unsigned int glList;

			/** Determines if this cache is still valid. */
			bool validCache;

		public:

			/**
			 * Creates a new caching render node.
			 */
			OPENLIMA_DLL CachingRenderNode();
			
			/**
			 * Finalizer.
			 */
			OPENLIMA_DLL virtual ~CachingRenderNode();

			
			/**
			 * When this caching render node is still valid, it will render using the internal
			 * cache, else it will refresh the cache by rendering all children of this render node.
			 */
			OPENLIMA_DLL virtual void render();
			
			/**
			 * Invalidates this caching render node and by that forces it to redraw the underlying
			 * children. Use this when you modified anything on the children or added/removed a
			 * child.
			 */
			OPENLIMA_DLL virtual void invalidate();
			
			/**
			 * Returns a value that determines if the cache of this render node is still valid.
			 *
			 * @return True, if the cache of this render node is still valid, else false.
			 */
			OPENLIMA_DLL virtual bool isValid() const;

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_CACHEDNODE_HPP */