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
#include <openlima/graphics/Environment.hpp>
#include <openlima/graphics/PerspectiveCamera.hpp>
#include <openlima/graphics/WavefrontObjReader.hpp>
#include <openlima/graphics/IRenderable.hpp>
#include <openlima/graphics/CachingRenderNode.hpp>
#include <openlima/graphics/TranslatingRenderNode.hpp>
#include <openlima/graphics/RotatingRenderNode.hpp>
#include <openlima/graphics/ScalingRenderNode.hpp>
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
	boost::shared_ptr<PerspectiveCamera> camera;
	Environment env;

	dtime lastMessage;
	dtime time;
	dtime amount;

	bool fpsMode;

	MyWindow* other;

	MyWindow(boost::shared_ptr<IRenderable> renderable,
			const char* title, GLfloat* lightColor)
			: LimaWindow(title, 640, 480) {

		camera = boost::make_shared<PerspectiveCamera>(OPENLIMA_REAL(75.0));
		camera->position.z = -30;
		env.setCamera(camera);

		boost::shared_ptr<CachingRenderNode> node = boost::make_shared<CachingRenderNode>();
		node->addChild(renderable);
		env.getRenderNode().addChild(node);

		fpsMode = false;
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
			camera->rotation.y += e.getDelta().x / 10.0f;
			camera->rotation.x += e.getDelta().y / 10.0f;
			while(camera->rotation.y < 0)
				camera->rotation.y += 360;
			while(camera->rotation.y >= 360)
				camera->rotation.y -= 360;

			if(camera->rotation.x < -80)
				camera->rotation.x = -80;
			if(camera->rotation.x > 80)
				camera->rotation.x = 80;
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
						 "          X: " << camera->position.x << std::endl <<
						 "          Y: " << camera->position.y << std::endl <<
						 "          Z: " << camera->position.z << std::endl <<
						 " X Rotation: " << camera->rotation.x << std::endl <<
						 " Y Rotation: " << camera->rotation.y << std::endl;
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


			Real yRotRadian = camera->rotation.y / 180 * OPENLIMA_REAL(3.14159265);

			if(forwardMovement != 0) {
				camera->position.z += cos(-yRotRadian) * movementSpeed * forwardMovement;
				camera->position.x += sin(-yRotRadian) * movementSpeed * forwardMovement;
			}

			if(sidewardMovement != 0) {
				camera->position.z += sin(yRotRadian) * movementSpeed * sidewardMovement;
				camera->position.x += cos(yRotRadian) * movementSpeed * sidewardMovement;
			}

			if(upwardMovement != 0) {
				camera->position.y += movementSpeed * upwardMovement;
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
		
		env.render(Vector2i(this->getWidth(), this->getHeight()));

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
		resourceManager->getResource<StaticMesh>("sampleTerrain.obj");

	if(!renderable) {
		std::cout << "Failed to load resource: \"./resources/sampleTerrain.obj\"" << std::endl;
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
