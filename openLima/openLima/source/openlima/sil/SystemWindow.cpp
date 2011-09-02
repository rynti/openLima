// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#include <openlima/util/macros.hpp>
#include <openlima/sil/sigl.hpp>
#include <openlima/sil/SystemWindow.hpp>
#include <openlima/sil/KeyMapper.hpp>

#include <iostream>

#ifdef OPENLIMA_SIL_XLIB
#include <X11/Xlib.h>
#endif

using namespace openlima::input;


namespace openlima {
	namespace sil {

#ifdef OPENLIMA_SIL_WINAPI
		// The WinAPI implementation

		std::map<HWND, SystemWindow*> SystemWindow::registeredWindows;

		HINSTANCE SystemWindow::hInstance = GetModuleHandle(NULL);


		LRESULT CALLBACK SystemWindow::globalWindowMessageHandler(HWND hWnd, UINT message, WPARAM wParam,
				LPARAM lParam) {
			return SystemWindow::registeredWindows[hWnd]->processWindowMessage(hWnd, message, wParam, lParam);
		}

		LRESULT SystemWindow::wmDestroy(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			unloadGL();
			PostQuitMessage(0);
			return 0;
		}

		LRESULT SystemWindow::wmSystemCommand(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch(wParam) {
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		LRESULT SystemWindow::wmEraseBackground(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			this->draw();
			return 0;
		}

		LRESULT SystemWindow::wmSizing(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			RECT clientRect;
			RECT windowRect;
			RECT newWindowRect;

			GetClientRect(hWnd, &clientRect);
			GetWindowRect(hWnd, &windowRect);

			// Borderwidth:
			int borderWidth = (windowRect.right - windowRect.left) -
				(clientRect.right - clientRect.left);

			// Borderheight:
			int borderHeight = (windowRect.bottom - windowRect.top) -
				(clientRect.bottom - clientRect.top);

			newWindowRect = *((RECT*)lParam);
			int width = (newWindowRect.right - newWindowRect.left) - borderWidth;
			int height = (newWindowRect.bottom - newWindowRect.top) - borderHeight;
			if(height == 0)
				height = 1;

			this->resize(width, height);
			return 0;
		}

		LRESULT SystemWindow::wmSize(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			if(height == 0)
				height = 1;

			this->resize(width, height);
			return 0;
		}

		LRESULT SystemWindow::wmMouseMove(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

			if(mouseLeaved) {
				mouseLeaved = false;
				if(!this->cursorVisibility)
					ShowCursor(false);
			}

			TRACKMOUSEEVENT tme = {sizeof(tme)};
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);

			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			this->mouseMoveFunction(*this, x, y);
			return 0;
		}

		LRESULT SystemWindow::wmMouseLeave(
				HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			mouseLeaved = true;
			if(!this->cursorVisibility)
				ShowCursor(true);
			return 0;
		}

		LRESULT CALLBACK SystemWindow::processWindowMessage(HWND hWnd, UINT message, WPARAM wParam,
				LPARAM lParam) {
			switch(message) {
			case WM_DESTROY:
				return wmDestroy(hWnd, message, wParam, lParam);
			case WM_SYSCOMMAND:
				return wmSystemCommand(hWnd, message, wParam, lParam);
			case WM_ERASEBKGND:
				return wmEraseBackground(hWnd, message, wParam, lParam);
			case WM_SIZING:
				return wmSizing(hWnd, message, wParam, lParam);
			case WM_SIZE:
				return wmSize(hWnd, message, wParam, lParam);
			case WM_KEYDOWN:
				this->keyDownFunction(*this, KeyMapper::mapVirtualKey(wParam)); return 0;
			case WM_KEYUP:
				this->keyUpFunction(*this, KeyMapper::mapVirtualKey(wParam)); return 0;
			case WM_MOUSELEAVE:
				return wmMouseLeave(hWnd, message, wParam, lParam);
			case WM_MOUSEMOVE:
				return wmMouseMove(hWnd, message, wParam, lParam);
			case WM_LBUTTONDOWN:
				this->mouseClickFunction(*this, MouseButtonType::LEFT, true); return 0;
			case WM_LBUTTONUP:
				this->mouseClickFunction(*this, MouseButtonType::LEFT, false); return 0;
			case WM_MBUTTONDOWN:
				this->mouseClickFunction(*this, MouseButtonType::MIDDLE, true); return 0;
			case WM_MBUTTONUP:
				this->mouseClickFunction(*this, MouseButtonType::MIDDLE, false); return 0;
			case WM_RBUTTONDOWN:
				this->mouseClickFunction(*this, MouseButtonType::RIGHT, true); return 0;
			case WM_RBUTTONUP:
				this->mouseClickFunction(*this, MouseButtonType::RIGHT, false); return 0;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		void SystemWindow::setupGL() {
			PIXELFORMATDESCRIPTOR pfd;
			int iFormat;

			hDC = GetDC(hWnd);

			ZeroMemory(&pfd, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 24;
			pfd.cDepthBits = 16;
			pfd.iLayerType = PFD_MAIN_PLANE;
			iFormat = ChoosePixelFormat(hDC, &pfd);
			SetPixelFormat(hDC, iFormat, &pfd);

			hRC = wglCreateContext(hDC);

			// Keep it open so after the SystemWindow constructor modifications of OpenGL can be
			// done:
			wglMakeCurrent(hDC, hRC);
			// Maybe a "dirty" way to do it, I'm think about adding a virtual initialize() method
			// that can do some GL-initialization stuff.
		}

		void SystemWindow::resize(int width, int height) {
			this->width = width;
			this->height = height;

			wglMakeCurrent(hDC, hRC);

			this->resizeFunction(*this, width, height);

			wglMakeCurrent(NULL, NULL);
		}

		void SystemWindow::draw() {
			wglMakeCurrent(hDC, hRC);

			this->drawFunction(*this);

			wglMakeCurrent(NULL, NULL);
		}

		void SystemWindow::unloadGL() {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hRC);
			ReleaseDC(hWnd, hDC);
		}

		bool SystemWindow::nextEvent() {
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if(msg.message == WM_QUIT) {
					return false;
				} else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					this->draw();
					return true;
				}
			} else {
				this->draw();
				return true;
			}
		}



		// Public

		SystemWindow::SystemWindow(const char* title, int width, int height) {
#ifdef UNICODE
			size_t len = strlen(title);
			wchar_t* unicodeTitle = new wchar_t[len + 1];
			for(size_t i = 0; i < len; i++)
				unicodeTitle[i] = (wchar_t)(title[i]);

			unicodeTitle[len] = 0;
#endif

			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc = SystemWindow::globalWindowMessageHandler;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = hInstance;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
#ifdef UNICODE
			wc.lpszClassName = unicodeTitle;
#else
			wc.lpszClassName = title;
#endif
			wc.lpszMenuName = NULL;
			RegisterClass(&wc);

			this->width = -1;
			this->height = -1;
			this->cursorVisibility = true;
			this->mouseLeaved = false;
			this->alive = true;
			this->visible = false;
			this->title = title;
			this->resizable = true;


#ifdef UNICODE
			hWnd = CreateWindow(unicodeTitle,
				unicodeTitle,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				width,
				height,
				NULL,
				NULL,
				hInstance,
				NULL);

			delete [] unicodeTitle;
#else
			hWnd = CreateWindow(title,
				title,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				width,
				height,
				NULL,
				NULL,
				hInstance,
				NULL);
#endif

			SystemWindow::registeredWindows[hWnd] = this;

			setupGL();

			this->setSize(width, height);
		}

		SystemWindow::~SystemWindow() {
			SystemWindow::registeredWindows.erase(hWnd);
		}

		void SystemWindow::setMousePosition(int x, int y) {
			POINT myPoint;
			myPoint.x = x;
			myPoint.y = y;
			ClientToScreen(hWnd, &myPoint);
			SetCursorPos(myPoint.x, myPoint.y);
		}

		int SystemWindow::getWidth() {
			return this->width;
		}

		int SystemWindow::getHeight() {
			return this->height;
		}

		void SystemWindow::setMouseVisibility(bool visible) {
			if(this->cursorVisibility != visible) {
				ShowCursor(visible);
				this->cursorVisibility = visible;
			}
		}

		void SystemWindow::setSize(int width, int height) {
			if(this->width != width || this->height != height) {
				this->width = width;
				this->height = height;

				RECT clientRect, windowRect;
				GetClientRect(hWnd, &clientRect);
				GetWindowRect(hWnd, &windowRect);
				int borderWidth = (windowRect.right - windowRect.left) -
					(clientRect.right - clientRect.left);

				int borderHeight = (windowRect.bottom - windowRect.top) -
					(clientRect.bottom - clientRect.top);

				MoveWindow(hWnd, windowRect.left, windowRect.top,
					width + borderWidth, height + borderHeight, true);
			}
		}

		void SystemWindow::setTitle(const char* title) {
			this->title = title;
#ifdef UNICODE
			size_t len = strlen(title);
			wchar_t* unicodeTitle = new wchar_t[len + 1];
			for(size_t i = 0; i < len; i++)
				unicodeTitle[i] = (wchar_t)(title[i]);

			unicodeTitle[len] = 0;

			SetWindowText(hWnd, unicodeTitle);

			delete [] unicodeTitle;
#else
			SetWindowText(hWnd, title);
#endif
		}

		void SystemWindow::setResizable(bool resizable) {
			if(this->resizable != resizable) {
				if(resizable) {
					this->resizable = resizable;
					SetWindowLong(hWnd, GWL_STYLE,
						GetWindowLong(hWnd, GWL_STYLE) | WS_THICKFRAME | WS_MAXIMIZEBOX);
					this->setSize(this->width, this->height);
				} else {
					this->resizable = resizable;
					SetWindowLong(hWnd, GWL_STYLE,
						GetWindowLong(hWnd, GWL_STYLE) & ~(WS_THICKFRAME | WS_MAXIMIZEBOX));
					this->setSize(this->width, this->height);
				}
			}
		}

		void SystemWindow::close() {
			if(this->alive) {
				this->alive = false;
				DestroyWindow(hWnd);
			}
		}

		void SystemWindow::hide() {
			if(this->visible) {
				this->visible = false;
				ShowWindow(hWnd, SW_HIDE);
				UpdateWindow(hWnd);
			}
		}

		void SystemWindow::show() {
			if(!this->visible) {
				this->visible = true;
				ShowWindow(hWnd, SW_SHOW);
				UpdateWindow(hWnd);
			}
		}

		void SystemWindow::swapBuffers() {
			SwapBuffers(hDC);
		}

		bool SystemWindow::mainLoopStep() {
			bool rVal = true;
			BOOST_FOREACH_PAIR(HWND hWnd, SystemWindow* window, SystemWindow::registeredWindows) {
				if(!window->nextEvent())
					rVal = false;
			}
			return rVal;
		}

#endif

#ifdef OPENLIMA_SIL_XLIB

		std::map<Window, SystemWindow*> SystemWindow::registeredWindows;
		Display* SystemWindow::display = XOpenDisplay(NULL);
		int SystemWindow::screen = DefaultScreen(SystemWindow::display);
		unsigned long SystemWindow::white = WhitePixel(SystemWindow::display, SystemWindow::screen);
		unsigned long SystemWindow::black = BlackPixel(SystemWindow::display, SystemWindow::screen);

		long SystemWindow::eventMask =
			ButtonPressMask			| ButtonReleaseMask			| KeyPressMask |
			KeyReleaseMask			| PointerMotionMask			| StructureNotifyMask;

		Atom SystemWindow::wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
		char SystemWindow::noData[] = {0,0,0,0,0,0,0,0};


		SystemWindow::SystemWindow(const char* title, int width, int height) {
			this->width = width;
			this->height = height;
			this->alive = true;
			this->visible = false;
			this->resizable = true;
			this->cursorVisibility = true;
			this->title = title;
			this->sizeHints = XAllocSizeHints();

			XSetWindowAttributes winAttributes;
			Window root = DefaultRootWindow(display);
			int attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
			visualInfo = glXChooseVisual(display, screen, attributes);

			winAttributes.colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);
			winAttributes.event_mask = eventMask;

			this->window = XCreateWindow(
				display, root, 0, 0, width, height, 0,
				visualInfo->depth, InputOutput,
				visualInfo->visual,
				CWColormap | CWEventMask,
				&winAttributes);

			SystemWindow::registeredWindows[window] = this;

			setupGL();

			XAutoRepeatOn(display);

			XSetWMNormalHints(display, window, sizeHints);
			XStoreName(display, window, title);
			XSetWMProtocols(display, window, &wmDelete, 1);

			Pixmap emptyBitmap;
			XColor black;
			black.red = black.green = black.blue = 0;
			emptyBitmap = XCreateBitmapFromData(display, window, noData, 8, 8);
			invisibleCursor = XCreatePixmapCursor(display, emptyBitmap, emptyBitmap,
													&black, &black, 0, 0);

		}

		SystemWindow::~SystemWindow() {
			this->close();
			SystemWindow::registeredWindows.erase(window);
			delete visualInfo;
			XFree(this->sizeHints);
			unloadGL();
		}

		void SystemWindow::setMousePosition(int x, int y) {
			XWarpPointer(display, window, window, 0, 0, 0, 0, x, y);
		}

		int SystemWindow::getWidth() {
			return this->width;
		}

		int SystemWindow::getHeight() {
			return this->height;
		}

		void SystemWindow::setMouseVisibility(bool visible) {
			if(this->cursorVisibility != visible) {
				this->cursorVisibility = visible;
				// When passing "None" as cursor, it will use the default cursor!
				XDefineCursor(display, window, visible ? None : invisibleCursor);
			}
		}

		void SystemWindow::setSize(int width, int height) {
			if(width < 1)
				width = 1;

			if(height < 1)
				height = 1;

			if(this->width != width || this->height != height) {
				if(!this->isResizable()) {
					this->width = width;
					this->height = height;
					this->setResizable(true);
					XFlush(display);
					XResizeWindow(display, window,
								  static_cast<unsigned int>(width),
								  static_cast<unsigned int>(height));
					XFlush(display);
					this->setResizable(false);
					XFlush(display);
					resize(width, height);
				} else {
					XResizeWindow(display, window,
								  static_cast<unsigned int>(width),
								  static_cast<unsigned int>(height));
				}
			}
		}

		void SystemWindow::setTitle(const char* title) {
			this->title = title;
			XStoreName(display, window, title);
		}

		void SystemWindow::setResizable(bool resizable) {
			if(this->resizable != resizable) {
				this->resizable = resizable;
				if(resizable) {
					sizeHints->flags = 0;
					XSetWMNormalHints(display, window, sizeHints);
				} else {
					sizeHints->flags = PMinSize | PMaxSize;
					sizeHints->min_width = this->getWidth();
					sizeHints->min_height = this->getHeight();
					sizeHints->max_width = this->getWidth();
					sizeHints->max_height = this->getHeight();
					XSetWMNormalHints(display, window, sizeHints);
				}
			}
		}

		void SystemWindow::close() {
			if(this->alive) {
				this->alive = false;
				XDestroyWindow(display, window);
				XFreeCursor(display, invisibleCursor);
			}
		}

		void SystemWindow::hide() {
			if(this->visible) {
				this->visible = false;
				XUnmapWindow(display, window);
			}
		}

		void SystemWindow::show() {
			if(!this->visible) {
				this->visible = true;
				XMapWindow(display, window);
			}
		}

		void SystemWindow::swapBuffers() {
			glXSwapBuffers(display, window);
		}

		bool SystemWindow::nextEvent(XEvent& evt) {
			if(!this->alive)
				return false;

			switch(evt.type) {
			case ClientMessage:
			case DestroyNotify:
				this->alive = false;
				return false;
			case ConfigureNotify:
				configureNotifyEvent(evt);
				break;
			case MapNotify:
				mapNotifyEvent(evt);
				break;
			case MotionNotify:
				motionNotifyEvent(evt);
				break;
			case ButtonPress:
				buttonPressedEvent(evt);
				break;
			case ButtonRelease:
				buttonReleasedEvent(evt);
				break;
			case KeyPress:
				keyPressedEvent(evt);
				break;
			case KeyRelease:
				keyReleasedEvent(evt);
				break;
			}

			return true;
		}

		void SystemWindow::mapNotifyEvent(XEvent& evt) {
			XMapEvent event = *((XMapEvent*)&evt);

			resize(this->width, this->height);
		}

		void SystemWindow::configureNotifyEvent(XEvent& evt) {
			XConfigureEvent event = *((XConfigureEvent*)&evt);

			if(event.width != this->width || event.height != this->height) {
				this->width = width;
				this->height = height;
				resize(event.width, event.height);
			}
		}

		void SystemWindow::motionNotifyEvent(XEvent& evt) {
			XPointerMovedEvent event = *((XPointerMovedEvent*)&evt);

			this->mouseMoveFunction(*this, event.x, event.y);
		}

		void SystemWindow::buttonReleasedEvent(XEvent& evt) {
			XButtonReleasedEvent event = *((XButtonReleasedEvent*)&evt);
			if(event.button == Button1)
				this->mouseClickFunction(*this, MouseButtonType::LEFT, false);

			if(event.button == Button2)
				this->mouseClickFunction(*this, MouseButtonType::MIDDLE, false);

			if(event.button == Button3)
				this->mouseClickFunction(*this, MouseButtonType::RIGHT, false);

		}

		void SystemWindow::buttonPressedEvent(XEvent& evt) {
			XButtonPressedEvent event = *((XButtonPressedEvent*)&evt);
			if(event.button == Button1)
				this->mouseClickFunction(*this, MouseButtonType::LEFT, true);

			if(event.button == Button2)
				this->mouseClickFunction(*this, MouseButtonType::MIDDLE, true);

			if(event.button == Button3)
				this->mouseClickFunction(*this, MouseButtonType::RIGHT, true);

		}

		void SystemWindow::keyReleasedEvent(XEvent& evt) {
			XKeyReleasedEvent event = *((XKeyReleasedEvent*)&evt);

			this->keyUpFunction(*this, KeyMapper::mapKeycode(display, event.keycode));
		}

		void SystemWindow::keyPressedEvent(XEvent& evt) {
			XKeyPressedEvent event = *((XKeyPressedEvent*)&evt);

			this->keyDownFunction(*this, KeyMapper::mapKeycode(display, event.keycode));
		}

		void SystemWindow::setupGL() {
			glContext = glXCreateContext(display, visualInfo, NULL, true);
			glXMakeCurrent(display, window, glContext);
		}

		void SystemWindow::unloadGL() {
			glXDestroyContext(display, glContext);
		}

		void SystemWindow::draw() {
			glXMakeCurrent(display, window, glContext);
			this->drawFunction(*this);
			glXMakeCurrent(display, None, NULL);
		}

		void SystemWindow::resize(int width, int height) {
			this->width = width;
			this->height = height;

			glXMakeCurrent(display, window, glContext);
			this->resizeFunction(*this, width, height);
			glXMakeCurrent(display, None, NULL);
		}

		bool SystemWindow::mainLoopStep() {
			if(registeredWindows.size() == 0)
				return false;	// If no windows are registered

			while(XPending(display) > 0) {
				XEvent evt;
				XNextEvent(display, &evt);
				if(!registeredWindows[((XAnyEvent*)&evt)->window]->nextEvent(evt))
					return false;
			}

			BOOST_FOREACH_PAIR(Window wHandle, SystemWindow* window, registeredWindows) {
				if(!window->isAlive())
					return false;	// If any window is not alive anymore
				window->draw();
			}

			return true;
		}

#endif

		bool SystemWindow::isAlive() {
			return this->alive;
		}

		bool SystemWindow::isVisible() {
			return this->visible;
		}

		bool SystemWindow::isMouseVisible() {
			return this->cursorVisibility;
		}

		const char* SystemWindow::getTitle() {
			return this->title;
		}

		bool SystemWindow::isResizable() {
			return this->resizable;
		}

		void SystemWindow::mainLoop() {
			while(SystemWindow::mainLoopStep()) {}
		}

	}
}
