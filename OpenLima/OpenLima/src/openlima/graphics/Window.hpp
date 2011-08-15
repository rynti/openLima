// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_WINDOW_HPP
#define OPENLIMA_GRAPHICS_WINDOW_HPP


#include <GL/freeglut.h>
#include <boost/function.hpp>

#include "../util/macros.hpp"



namespace openlima {
	namespace graphics {

		class Window {
		private:
			boost::function<void()> drawFunction;

			static void resizeHandler(int winWidth, int winHeight);
			static void drawHandler();

			Window() {}
			Window(const Window&) {}
			Window& operator=(const Window&) {}
			~Window() {}

			void draw();

		public:
			static OPENLIMA_DLL Window& getInstance();
			static OPENLIMA_DLL void hideConsole();

			OPENLIMA_DLL void setDrawFunction(boost::function<void()> func);
			OPENLIMA_DLL void setup(int* argcp, char** argv, const char* winCaption, int winWidth = 640,
				int winHeight = 480, unsigned int displayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			OPENLIMA_DLL void loop();

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_WINDOW_HPP */