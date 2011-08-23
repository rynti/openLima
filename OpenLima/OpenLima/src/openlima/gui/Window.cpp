// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include "../sil/sigl.hpp"
#include "../input/SystemMouse.hpp"
#include "../input/SystemKeyboard.hpp"
#include "Window.hpp"

using namespace std;
using namespace boost::posix_time;
using namespace openlima::input;
using namespace openlima::util;
using namespace openlima::sil;


namespace openlima {
	namespace gui {

		const dtime Window::defaultUpdateTime = 0.016667; // ~= (1/60) => 60 FPS



		Window::Window(const wchar_t* title, int width, int height) {
			this->updateDelta = 0;
			this->updateTime = defaultUpdateTime;
			this->redrawDelta = 0;
			this->redrawTime = defaultUpdateTime;
			this->limitRedraw = false;

			this->systemWindow = new SystemWindow(title, width, height);

			this->systemWindow->onResize = boost::bind(&Window::onResize, this, _1, _2, _3);
			this->systemWindow->onDraw = boost::bind(&Window::onDraw, this, _1);

			this->mouse = new SystemMouse(*systemWindow);
			this->mouse->onMouseClick.connect(
				boost::bind(&Window::onMouseClick, this, _1, _2));
			this->mouse->onMouseMove.connect(
				boost::bind(&Window::onMouseMove, this, _1, _2));

			this->keyboard = new SystemKeyboard(*systemWindow);
			this->keyboard->onKeyboardButtonPressed.connect(
				boost::bind(&Window::onKeyboardButtonPressed, this, _1, _2));
			this->keyboard->onKeyboardButtonReleased.connect(
				boost::bind(&Window::onKeyboardButtonReleased, this, _1, _2));
			
		}

		Window::~Window() {
			delete this->mouse;
			delete this->keyboard;
			delete this->systemWindow;
		}

		void Window::enterMainLoop() {
			openlima::sil::SystemWindow::mainLoop();
		}

		void Window::hideConsole() {
#ifdef OPENLIMA_WIN
			FreeConsole();
#endif
		}

		void Window::onResize(SystemWindow& window, int width, int height) {
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();
			gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
		}

		void Window::onDraw(SystemWindow& window) {
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

		Mouse* Window::getMouse() {
			return this->mouse;
		}

		void Window::showWindow() {
			this->systemWindow->showWindow();
		}

		void Window::setTitle(const wchar_t* title) {
			this->systemWindow->setTitle(title);
		}

		void Window::setSize(int width, int height) {
			this->systemWindow->setSize(width, height);
		}

		void Window::setResizable(bool resizable) {
			this->systemWindow->setResizable(resizable);
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
			this->systemWindow->swapBuffers();
		}



		void Window::onMouseClick(Mouse& source, const MouseClickEvent& e) {
			// Empty
		}

		void Window::onMouseMove(Mouse& source, const MouseMoveEvent& e) {
			// Empty
		}

		void Window::onKeyboardButtonPressed(Keyboard& source, const KeyboardEvent& e) {
			// Empty
		}

		void Window::onKeyboardButtonReleased(Keyboard& source, const KeyboardEvent& e) {
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
