// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "../input/GlutMouse.hpp"
#include "Window.hpp"

using namespace std;
using namespace boost::posix_time;
using namespace openlima::input;
using namespace openlima::util;


namespace openlima {
	namespace gui {

		const dtime Window::defaultUpdateTime = 0.016667; // ~= (1/60) => 60 FPS

		std::map<GlutHandle, Window*> Window::registeredWindows;



		Window::Window(const char* title, int width, int height,
				unsigned int displayMode /* = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH */) {

			this->updateDelta = 0;
			this->updateTime = defaultUpdateTime;
			this->redrawDelta = 0;
			this->redrawTime = defaultUpdateTime;
			this->limitRedraw = false;

			glutInitDisplayMode(displayMode);
			glutInitWindowSize(width, height);

			this->glutWindowId = glutCreateWindow(title);
			Window::registeredWindows[this->glutWindowId] = this;

			glutReshapeFunc(&Window::globalResizeHandler);
			glutDisplayFunc(&Window::globalDrawHandler);

			this->mouse = new GlutMouse(this->glutWindowId);
			this->mouse->onMouseClick.connect(boost::bind(&Window::onMouseClick, this, _1, _2));
			this->mouse->onMouseMove.connect(boost::bind(&Window::onMouseMove, this, _1, _2));
		}

		Window::~Window() {
			Window::registeredWindows.erase(this->glutWindowId);
			delete this->mouse;
		}

		void Window::initialize(int* argcp, char** argv) {
			static bool initialized = false;
			if(!initialized) {
				glutInit(argcp, argv);
				glutIdleFunc(&Window::globalIdleHandler);
				setWindowDependency();

				initialized = true;
			}
		}

		void Window::enterMainLoop() {
			glutMainLoop();
		}

		void Window::setWindowDependency(bool dependent /* = true*/) {
			if(dependent) {
				glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
			} else {
				glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
			}
		}

		void Window::hideConsole() {
#ifdef OPENLIMA_WIN
			FreeConsole();
#endif
		}

		void Window::globalResizeHandler(int width, int height) {
			Window::registeredWindows[glutGetWindow()]->onResize(width, height);
		}

		void Window::globalDrawHandler() {
			Window::registeredWindows[glutGetWindow()]->onDraw();
		}

		void Window::globalIdleHandler() {
			BOOST_FOREACH_PAIR(GlutHandle windowId, Window* window, Window::registeredWindows) {
				window->onIdle();
			}
		}

		void Window::onResize(int width, int height) {
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();
			gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
		}

		void Window::onDraw() {
			if(this->previousUpdate.is_not_a_date_time()) {
				this->previousUpdate = microsec_clock::local_time();
			}
			ptime now = microsec_clock::local_time();
			time_duration delta = now - this->previousUpdate;
			this->previousUpdate = now;
			dtime deltaSeconds = delta.total_microseconds() / 1000000.0;

			this->updateDelta += deltaSeconds;
			while(this->updateDelta >= this->updateTime) {
				this->update(this->updateTime);
				this->updateDelta -= this->updateTime;
			}

			if(limitRedraw) {
				this->redrawDelta += deltaSeconds;
				if(this->redrawDelta >= this->redrawTime) {
					this->render(this->redrawDelta);
					this->redrawDelta = 0;
				}
			} else {
				this->render(deltaSeconds);
			}
		}

		void Window::onIdle() {
			glutPostWindowRedisplay(this->glutWindowId);
		}

		Mouse* Window::getMouse() {
			return this->mouse;
		}

		void Window::setTitle(const char* title) {
			glutSetWindow(this->glutWindowId);
			glutSetWindowTitle(title);
		}

		void Window::setSize(int width, int height) {
			glutSetWindow(this->glutWindowId);
			glutReshapeWindow(width, height);
		}

		void Window::setRenderRate(Real rate) {
			if(rate <= 0) {
				this->limitRedraw = false;
			} else {
				this->limitRedraw = true;
				this->redrawTime = 1 / rate;
			}
		}

		void Window::setUpdateRate(Real rate) {
			this->updateTime = 1 / rate;
		}

		void Window::initializeRendering() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		void Window::finishRendering() {
			glutSwapBuffers();
		}



		void Window::onMouseClick(Mouse& source, const MouseClickEvent& e) {
			// Empty
		}

		void Window::onMouseMove(Mouse& source, const MouseMoveEvent& e) {
			// Empty
		}

		void Window::update(dtime delta) {
			// Empty
		}

		void Window::render(dtime delta) {
			// Empty
		}

	}
}
