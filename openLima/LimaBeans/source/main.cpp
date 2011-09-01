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
#include <openlima/gui/LimaWindow.hpp>
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


void showHelp();

class MyWindow : public LimaWindow {
public:
	boost::shared_ptr<IRenderable> myRenderable;
	Real xPos;
	Real yPos;
	Real zPos;

	dtime lastMessage;
	dtime time;
	dtime amount;

	MyWindow* other;

	MyWindow(boost::shared_ptr<IRenderable> renderable,
			const char* title, GLfloat* lightColor) : LimaWindow(title, 640, 480) {

		myRenderable = renderable;

		xPos = 0;
		yPos = 0;
		zPos = 0;
		lastMessage = 5;
		time = 0;
		amount = 0;

		// All gl-functions will be removed so users of openlima don't have to deal with them
		// directly, instead they'll use abstractions.

		// For instance, those flags will come to the LimaWindow-class and can be modified by
		// different methods:
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
			std::cout << "Mouse stickyness " <<
				(catchIt ? "activated." : "deactivated.") << std::endl;
		}
	}

	void showWindowInformation() {
		std::cout <<	"Window Information:" << std::endl <<
						"  Title:         \"" << this->getTitle() << "\"" << std::endl <<
						"  Size:          " << this->getWidth() << "x" <<
											   this->getHeight() << std::endl <<
						"  Alive:         " << (this->isAlive() ? "Yes" : "No") << std::endl <<
						"  Visible:       " << (this->isVisible() ? "Yes" : "No") << std::endl <<
						"  Resizable:     " << (this->isResizable() ? "Yes" : "No") << std::endl <<
						"  Mouse Visible: " << (this->isMouseVisible() ? "Yes" : "No") << std::endl;
	}

	virtual void onKeyboardButtonPressed(Keyboard& source, const KeyboardEvent& e) {
		if(source.isPressed(KeyboardButtonType::KEY_CONTROL)) {
			if(e.getButton() == KeyboardButtonType::KEY_ADD) {
				this->setSize(this->getWidth() + 16, this->getHeight() + 12);
				std::cout << "Window enlarged!" << std::endl;

			} else if(e.getButton() == KeyboardButtonType::KEY_SUBTRACT) {
				this->setSize(this->getWidth() - 16, this->getHeight() - 12);
				std::cout << "Window shrinked!" << std::endl;

			} else if(e.getButton() == KeyboardButtonType::KEY_R) {
				this->setResizable(!this->isResizable());
				std::cout << "This window is " <<
					(this->isResizable() ? "now resizable." : "not resizable anymore.") <<
					std::endl;

			} else if(e.getButton() == KeyboardButtonType::KEY_I) {
				this->showWindowInformation();

			} else if(e.getButton() == KeyboardButtonType::KEY_Q) {
				showHelp();

			} else if(e.getButton() == KeyboardButtonType::KEY_X) {
				this->close();
				std::cout << "Window closed!" << std::endl;

			} else if(e.getButton() == KeyboardButtonType::KEY_H) {
				if(other == NULL) {
					std::cout <<
						"Cant' hide the window, reason: There is no other window!" << std::endl <<
						"Use CTRL+X to close this window." << std::endl;
				} else if(!other->isVisible()) {
					std::cout <<
						"Cant' hide the window, reason: The other window is not visible!" <<
						std::endl << "Use CTRL+S to show the other window." << std::endl;
				} else {
					this->hide();
					std::cout << "Window hidden!" << std::endl;
				}

			} else if(e.getButton() == KeyboardButtonType::KEY_S) {
				if(other == NULL) {
					std::cout << "Cant' show the other window, reason: There is no other window!" <<
						std::endl;
				} else {
					other->show();
					std::cout << "Showing the other window!" << std::endl;
				}
			}
		}
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


void showHelp() {
	std::cout <<	"Debug Controls (CTRL + Key):" << std::endl <<
					" Q - Show this command overview" << std::endl <<
					" R - Toggle the resizable attribute" << std::endl <<
					" I - Print some debug information" << std::endl <<
					" X - Close the window" << std::endl <<
					" H - Hide the window" << std::endl <<
					" S - Show the other window" << std::endl <<
					" + (Numpad) - Enlarge the window" << std::endl <<
					" - (Numpad) - Shrink the window" << std::endl;
}

OPENLIMA_MAIN(int argc, char** argv) {
	path executable(argv[0]);
	path resourcesDir = executable.remove_filename()/"resources";

	boost::shared_ptr<ResourceManager> resourceManager(
		new FileResourceManager(resourcesDir.string()));

	resourceManager->registerReader<StaticMesh>(new WavefrontObjReader);
	boost::shared_ptr<IRenderable> renderable =
		resourceManager->getResource<StaticMesh>("doubleCubes.obj");

	if(!renderable) {
		std::cout << "Failed to load resource: \"./resources/doubleCubes.obj\"" << std::endl;
		return 1;
	}

	GLfloat lightColors1[] = {0.5f, 1.0f, 0.5f, 1.0f};
	MyWindow window1(renderable, "Window 1", lightColors1);
	GLfloat lightColors2[] = {1.0f, 0.5f, 0.5f, 1.0f};
	MyWindow window2(renderable, "Window 2", lightColors2);

	window1.other = &window2;
	window2.other = &window1;

	window1.setTitle("LOOOL");
	window2.setTitle("TROLL");
	window1.show();

	showHelp();

	SystemWindow::mainLoop();

	return 0;
}
