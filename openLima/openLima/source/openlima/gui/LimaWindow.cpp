// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <openlima/sil/sigl.hpp>
#include <openlima/input/SystemMouse.hpp>
#include <openlima/input/SystemKeyboard.hpp>
#include <openlima/gui/LimaWindow.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace openlima::input;
using namespace openlima::util;
using namespace openlima::sil;


namespace openlima {
	namespace gui {

		const dtime LimaWindow::defaultUpdateTime = 0.016667; // ~= (1/60) => 60 FPS



		LimaWindow::LimaWindow(const char* title, int width, int height)
			: SystemWindow(title, width, height) {
			this->updateDelta = 0;
			this->updateTime = defaultUpdateTime;
			this->redrawDelta = 0;
			this->redrawTime = defaultUpdateTime;
			this->limitRedraw = false;

			this->resizeFunction = boost::bind(&LimaWindow::onResize, this, _1, _2, _3);
			this->drawFunction = boost::bind(&LimaWindow::onDraw, this, _1);

			this->mouse = new SystemMouse(*this);
			this->mouse->onMouseClick.connect(
				boost::bind(&LimaWindow::onMouseClick, this, _1, _2));
			this->mouse->onMouseMove.connect(
				boost::bind(&LimaWindow::onMouseMove, this, _1, _2));

			this->keyboard = new SystemKeyboard(*this);
			this->keyboard->onKeyboardButtonPressed.connect(
				boost::bind(&LimaWindow::onKeyboardButtonPressed, this, _1, _2));
			this->keyboard->onKeyboardButtonReleased.connect(
				boost::bind(&LimaWindow::onKeyboardButtonReleased, this, _1, _2));
		}

		LimaWindow::~LimaWindow() {
			delete this->mouse;
			delete this->keyboard;
		}

		void LimaWindow::hideConsole() {
#ifdef OPENLIMA_WIN
			FreeConsole();
#endif
		}

		void LimaWindow::onResize(SystemWindow& window, int width, int height) {
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);

			glLoadIdentity();
			gluPerspective(45.0, (double)width / (double)height, 0.01, 200.0);
		}

		void LimaWindow::onDraw(SystemWindow& window) {
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

			if(this->isVisible()) {
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
		}

		Mouse* LimaWindow::getMouse() {
			return this->mouse;
		}

		Keyboard* LimaWindow::getKeyboard() {
			return this->keyboard;
		}

		void LimaWindow::setRenderRate(Real rate) {
			if(rate <= 0) {
				this->limitRedraw = false;
			} else {
				this->limitRedraw = true;
				this->redrawTime = 1 / rate;
			}
		}

		void LimaWindow::setUpdateRate(Real rate) {
			this->updateTime = 1 / rate;
		}

		void LimaWindow::initializeRendering() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		void LimaWindow::finishRendering() {
			this->swapBuffers();
		}



		void LimaWindow::onMouseClick(Mouse& source, const MouseClickEvent& e) {
			// Empty
		}

		void LimaWindow::onMouseMove(Mouse& source, const MouseMoveEvent& e) {
			// Empty
		}

		void LimaWindow::onKeyboardButtonPressed(Keyboard& source, const KeyboardEvent& e) {
			// Empty
		}

		void LimaWindow::onKeyboardButtonReleased(Keyboard& source, const KeyboardEvent& e) {
			// Empty
		}

		void LimaWindow::update(dtime delta) {
			// Empty
		}

		void LimaWindow::render(dtime delta) {
			// Empty
		}

	}
}
