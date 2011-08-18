// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/macros.hpp>
#include <openlima/gui/Window.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/input/MouseButton.hpp>
#include <openlima/util/types.hpp>
#include <boost/bind.hpp>
#include <boost/date_time.hpp>

using namespace openlima::graphics;
using namespace openlima::gui;
using namespace openlima::input;
using namespace openlima::util;
using namespace boost::posix_time;


class MyWindow : public Window {
public:
	IRenderable* myRenderable;
	Real xPos;
	Real yPos;
	Real zPos;

	dtime lastMessage;
	dtime time;
	dtime amount;

	MyWindow(const char* title, GLfloat* lightColor) : Window(title, 800, 600) {
		myRenderable = WavefrontObjReader::readStatic("resources/simpleCube.obj");
		xPos = 0;
		yPos = 0;
		zPos = 0;
		lastMessage = 5;
		time = 0;
		amount = 0;

		// All glX-functions will be removed so users of openlima don't have to deal with them
		// directly, instead they'll use abstractions.
		
		// For instance, those flags will come to the Window-class and can be modified by different
		// methods:
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);

		// The lightning system will completely be extracted into openlima::graphics
		GLfloat ambientColor[]= {0.2f, 0.2f, 0.2f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		glEnable(GL_LIGHT0);
		GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		this->setRenderRate(60);
	}

	virtual ~MyWindow() {
		delete myRenderable;
	}

	virtual void onMouseMove(Mouse& source, const MouseMoveEvent& e) {
		bool catched = this->getMouse()->isSticky();
		if(catched) {
			xPos += e.getDelta().x / 500.0f;
			yPos -= e.getDelta().y / 500.0f;
		}
	}

	virtual void onMouseClick(Mouse& source, const MouseClickEvent& e) {
		if(e.getButton() == MouseButtonType::MIDDLE && e.isPressed()) {
			bool catchIt = !this->getMouse()->isSticky();
			this->getMouse()->setSticky(catchIt);
			this->getMouse()->setVisible(!catchIt);
		}
	}

	virtual void update(dtime delta) {
		if(this->getMouse()->isPressed(MouseButtonType::LEFT)) {
			zPos -= static_cast<Real>(delta); // TODO Make dtime implicitly castable with Real.
		} else if(this->getMouse()->isPressed(MouseButtonType::RIGHT)) {
			zPos += static_cast<Real>(delta);
		}
	}

	virtual void render(dtime delta) {
		lastMessage -= delta;
		time += delta;
		amount++;
		if(lastMessage <= 0) {
			std::cout << "FPS: " << (1/(time/amount)) << std::endl;
			lastMessage = 5;
			time = 0;
			amount = 0;
		}

		// You can skip the rendering if you neither call initializeRendering, nor finishRendering.
		this->initializeRendering();

		glTranslatef(0.0f, 0.0f, -5.0f);
		glTranslatef(xPos, yPos, zPos);
		myRenderable->render();

		this->finishRendering();
	}

};

OPENLIMA_MAIN(int argc, char** argv) {
	
	Window::initialize(&argc, argv);

	//Window::hideConsole();
		
	GLfloat lightColors1[] = {0.5f, 1.0f, 0.5f, 1.0f};
	MyWindow window1("Window 1", lightColors1);
	//GLfloat lightColors2[] = {1.0f, 0.5f, 0.5f, 1.0f};
	//MyWindow window2("Window 2", 500.0f, lightColors2);

	Window::setWindowDependency(false);

	Window::enterMainLoop();

	std::cout << "end" << std::endl;

	return 0;
}