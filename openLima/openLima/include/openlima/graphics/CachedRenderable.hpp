// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_CACHEDRENDERABLE_HPP
#define OPENLIMA_GRAPHICS_CACHEDRENDERABLE_HPP

#include <boost/smart_ptr.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/graphics/IRenderable.hpp>


namespace openlima {
	namespace graphics {
		
		class CachedRenderable : public IRenderable {
		private:

			boost::shared_ptr<IRenderable> renderable;

			unsigned int glList;

			bool validCache;

		public:

			OPENLIMA_DLL CachedRenderable(boost::shared_ptr<IRenderable> renderable);

			OPENLIMA_DLL virtual ~CachedRenderable();


			OPENLIMA_DLL virtual void render();

			OPENLIMA_DLL virtual void invalidate();

			OPENLIMA_DLL virtual bool isValid();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_CACHEDRENDERABLE_HPP */