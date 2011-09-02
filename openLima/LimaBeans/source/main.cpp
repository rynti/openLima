// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <boost/date_time.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
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
#include <openlima/graphics/CachedRenderable.hpp>
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
	Real yRot;
	Real xRot;

	dtime lastMessage;
	dtime time;
	dtime amount;

	bool fpsMode;

	MyWindow* other;

	MyWindow(boost::shared_ptr<IRenderable> renderable,
			const char* title, GLfloat* lightColor) : LimaWindow(title, 640, 480) {

		myRenderable = boost::make_shared<CachedRenderable>(renderable);

		fpsMode = false;
		xPos = 0;
		yPos = 0;
		zPos = -30.0f;
		yRot = 0;
		xRot = 0;
		lastMessage = 5;
		time = 0;
		amount = 0;

		// All gl-functions will be removed so users of openlima don't have to deal with them
		// directly, instead they'll use abstractions.

		// For instance, those flags will come to the LimaWindow-class and can be modified by
		// different methods:
		glEnable(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);

		// The lightning system will completely be extracted into openlima::graphics
		GLfloat ambientColor[]= {0.2f, 0.2f, 0.2f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		glEnable(GL_LIGHT0);
		GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		other = NULL;

		this->setRenderRate(60);
		//this->show();
	}

	virtual ~MyWindow() {
		// Empty
	}

	virtual void onMouseMove(Mouse& source, const MouseMoveEvent& e) {
		if(fpsMode) {
			yRot += e.getDelta().x / 10.0f;
			xRot += e.getDelta().y / 10.0f;
			while(yRot < 0)
				yRot += 360;
			while(yRot >= 360)
				yRot -= 360;

			if(xRot < -80)
				xRot = -80;
			if(xRot > 80)
				xRot = 80;
		}
	}

	virtual void onMouseClick(Mouse& source, const MouseClickEvent& e) {
		if(e.getButton() == MouseButtonType::MIDDLE && e.isPressed()) {
			fpsMode = !fpsMode;
			this->getMouse()->setSticky(fpsMode);
			this->getMouse()->setVisible(!fpsMode);
			std::cout << "FPS mode " <<
				(fpsMode ? "activated." : "deactivated.") << std::endl;
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
		if(e.getButton() == KeyboardButtonType::KEY_F1) {
			std::cout << "Camera Position:" << std::endl <<
						 "          X: " << xPos << std::endl <<
						 "          Y: " << yPos << std::endl <<
						 "          Z: " << zPos << std::endl <<
						 " X Rotation: " << xRot << std::endl <<
						 " Y Rotation: " << yRot << std::endl;
		}

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
						"Can't hide the window, reason: There is no other window!" << std::endl <<
						"Use CTRL+X to close this window." << std::endl;
				} else if(!other->isVisible()) {
					std::cout <<
						"Can't hide the window, reason: The other window is not visible!" <<
						std::endl << "Use CTRL+S to show the other window." << std::endl;
				} else {
					this->hide();
					std::cout << "Window hidden!" << std::endl;
				}

			} else if(e.getButton() == KeyboardButtonType::KEY_S) {
				if(other == NULL) {
					std::cout << "Can't show the other window, reason: There is no other window!" <<
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
		if(fpsMode) {
			// TODO Make dtime implicitly castable with Real.

			Real movementSpeed = static_cast<Real>(delta) * 3;

			int forwardMovement = 0;
			int sidewardMovement = 0;
			int upwardMovement = 0;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_W))
				forwardMovement++;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_S))
				forwardMovement--;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_A))
				sidewardMovement++;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_D))
				sidewardMovement--;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_Q))
				upwardMovement--;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_E))
				upwardMovement++;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_SPACE))
				movementSpeed /= 5;

			if(this->getKeyboard()->isPressed(KeyboardButtonType::KEY_SHIFT))
				movementSpeed *= 5;



			Real yRotRadian = yRot / 180 * 3.14159265;

			if(forwardMovement != 0) {
				zPos += cos(-yRotRadian) * movementSpeed * forwardMovement;
				xPos += sin(-yRotRadian) * movementSpeed * forwardMovement;
			}

			if(sidewardMovement != 0) {
				zPos += sin(yRotRadian) * movementSpeed * sidewardMovement;
				xPos += cos(yRotRadian) * movementSpeed * sidewardMovement;
			}

			if(upwardMovement != 0) {
				yPos += movementSpeed * upwardMovement;
			}
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

#ifdef OPENLIMA_PRECISE_REAL
		glRotated(xRot, 1.0, 0.0, 0.0);
		glRotated(yRot, 0.0, 1.0, 0.0);
		glTranslated(xPos, yPos, zPos);

		glTranslated(-10.0, 0.0, 0.0);
		for(size_t x = 0; x < 6; x++) {
			glTranslated(0.0, 10.0, 0.0);
			for(size_t y = 0; y < 6; y++) {
				myRenderable->render();
				glTranslated(0.0, -4.0, 0.0);
			}
			glTranslated(4.0, 14.0, 0.0);
		}
#else
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);

		glTranslatef(-10.0f, 0.0f, 0.0f);
		for(size_t x = 0; x < 6; x++) {
			glTranslatef(0.0f, 10.0f, 0.0f);
			for(size_t y = 0; y < 6; y++) {
				myRenderable->render();
				glTranslatef(0.0f, -4.0f, 0.0f);
			}
			glTranslatef(4.0f, 14.0f, 0.0f);
		}
#endif

		this->finishRendering();
	}

};


void showHelp() {
	std::cout <<	"Debug controls (CTRL + Key):" << std::endl <<
					" Q - Show this command overview" << std::endl <<
					" R - Toggle the resizable attribute" << std::endl <<
					" I - Print some debug information" << std::endl <<
					" X - Close the window" << std::endl <<
					" H - Hide the window" << std::endl <<
					" S - Show the other window" << std::endl <<
					" + (Numpad) - Enlarge the window" << std::endl <<
					" - (Numpad) - Shrink the window" << std::endl <<
					std::endl <<
					"FPS movement mode:" << std::endl <<
					" Press the middle mouse to toggle FPS movement on and off." << std::endl <<
					" You probably already know how to control the camera now, but" << std::endl <<
					" if you don't:" << std::endl <<
					" * Use the WASD-keys to move the camera." << std::endl <<
					" * Move the mouse to rotate the camera." << std::endl <<
					" * Use Q and E to move the camera up- or downwards." << std::endl <<
					" * Use SHIFT and SPACE to modify the movement speed." << std::endl;
}

OPENLIMA_MAIN(int argc, char** argv) {
	path executable(argv[0]);
	path resourcesDir = executable.remove_filename()/"resources";

	boost::shared_ptr<ResourceManager> resourceManager(
		new FileResourceManager(resourcesDir.string()));

	resourceManager->registerReader<StaticMesh>(new WavefrontObjReader);
	boost::shared_ptr<IRenderable> renderable =
		resourceManager->getResource<StaticMesh>("monkey.obj");

	if(!renderable) {
		std::cout << "Failed to load resource: \"./resources/monkey.obj\"" << std::endl;
		return 1;
	}

	GLfloat lightColors1[] = {0.5f, 1.0f, 0.5f, 1.0f};
	MyWindow window1(renderable, "Window 1", lightColors1);
	//GLfloat lightColors2[] = {1.0f, 0.5f, 0.5f, 1.0f};
	//MyWindow window2(renderable, "Window 2", lightColors2);

	//window1.other = &window2;
	//window2.other = &window1;

	window1.setTitle("LOOOL");
	//window2.setTitle("TROLL");
	window1.show();

	showHelp();

	SystemWindow::mainLoop();

	return 0;
}
