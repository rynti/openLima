// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <boost/date_time.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/filesystem.hpp>

#include <openlima/util/macros.hpp>
#include <openlima/util/types.hpp>
#include <openlima/sil/SystemWindow.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/gui/Window.hpp>
#include <openlima/input/MouseButton.hpp>
#include <openlima/input/KeyboardButton.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/sil/KeyMapper.hpp>
#include <openlima/util/ResourceManager.hpp>
#include <openlima/util/FileResourceManager.hpp>

using namespace openlima::graphics;
using namespace openlima::sil;
using namespace openlima::gui;
using namespace openlima::input;
using namespace openlima::util;
using namespace boost::posix_time;
using namespace boost::filesystem;


class MyWindow : public Window {
public:
	boost::shared_ptr<IRenderable> myRenderable;
	Real xPos;
	Real yPos;
	Real zPos;

	dtime lastMessage;
	dtime time;
	dtime amount;

	MyWindow* other;

	MyWindow(boost::shared_ptr<ResourceManager> resourceManager,
			const wchar_t* title, GLfloat* lightColor) : Window(title, 640, 480) {

		myRenderable = resourceManager->getResource<StaticMesh>("doubleCubes.obj");

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
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);

		// The lightning system will completely be extracted into openlima::graphics
		GLfloat ambientColor[]= {0.2f, 0.2f, 0.2f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		glEnable(GL_LIGHT0);
		GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		other = NULL;

		//this->setRenderRate(60);
		//this->show();
	}

	virtual ~MyWindow() {
		// Empty
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

	virtual void onKeyboardButtonPressed(Keyboard& source, const KeyboardEvent& e) {
		std::cout << "KeyboardButton #" << (unsigned int)(e.getButton()) << " {" << std::endl;

		char buttonValue = KeyMapper::getKeyboardButtonValue(e.getButton());
		if(buttonValue != 0)
			std::cout << "  Value: " << buttonValue << std::endl;

		const char* buttonDescription = KeyMapper::getKeyboardButtonDescription(e.getButton());
		if(buttonDescription != NULL)
			std::cout << "  Description: " << buttonDescription << std::endl;

		// Deleting NULL-pointers is allowed!
		delete[] buttonDescription;

		std::cout << "}" << std::endl;

		if(e.getButton() == KeyboardButtonType::KEY_ESCAPE)
			this->close();

		if(e.getButton() == KeyboardButtonType::KEY_H)
			this->hide();

		if(e.getButton() == KeyboardButtonType::KEY_S && other != NULL)
			other->show();

	}

	virtual void onKeyboardButtonReleased(Keyboard& source, const KeyboardEvent& e) {
		// Empty
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
	path executable(argv[0]);
	path resourcesDir = executable.remove_filename()/"resources";

	boost::shared_ptr<ResourceManager> resourceManager(
		new FileResourceManager(resourcesDir.string()));

	resourceManager->registerReader<StaticMesh>(new WavefrontObjReader);


	GLfloat lightColors1[] = {0.5f, 1.0f, 0.5f, 1.0f};
	MyWindow window1(resourceManager, L"Window 1", lightColors1);
	GLfloat lightColors2[] = {1.0f, 0.5f, 0.5f, 1.0f};
	MyWindow window2(resourceManager, L"Window 2", lightColors2);

	window1.other = &window2;
	window2.other = &window1;

	window1.show();

	Window::enterMainLoop();

	std::cout << "end" << std::endl;

	return 0;
}
