// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifdef OPENLIMA_WIN
#include <tchar.h>
#endif

#include "../util/macros.hpp"
#include "sigl.hpp"
#include "SystemWindow.hpp"
#include "KeyMapper.hpp"

using namespace openlima::input;


namespace openlima {
	namespace sil {
		
#ifdef OPENLIMA_WIN
		// The WinAPI implementation

		std::map<HWND, SystemWindow*> SystemWindow::registeredWindows;

		HINSTANCE SystemWindow::hInstance = GetModuleHandle(NULL);


		SystemWindow::SystemWindow(const wchar_t* title, int width, int height) {
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc = SystemWindow::globalWindowMessageHandler;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = hInstance;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszClassName = title;
			wc.lpszMenuName = NULL;
			RegisterClass(&wc);

			this->width = width;
			this->height = height;
			this->cursorVisibility = true;
			this->mouseLeaved = false;
			
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

			SystemWindow::registeredWindows[hWnd] = this;

			setupGL();
		}

		SystemWindow::~SystemWindow() {
			SystemWindow::registeredWindows.erase(hWnd);
		}

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
			this->onMouseMove(*this, x, y);
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
				this->onKeyDown(*this, KeyMapper::mapVirtualKey(wParam)); return 0;
			case WM_KEYUP:
				this->onKeyUp(*this, KeyMapper::mapVirtualKey(wParam)); return 0;
			case WM_MOUSELEAVE:
				return wmMouseLeave(hWnd, message, wParam, lParam);
			case WM_MOUSEMOVE:
				return wmMouseMove(hWnd, message, wParam, lParam);
			case WM_LBUTTONDOWN:
				this->onMouseClick(*this, MouseButtonType::LEFT, true); return 0;
			case WM_LBUTTONUP:
				this->onMouseClick(*this, MouseButtonType::LEFT, false); return 0;
			case WM_MBUTTONDOWN:
				this->onMouseClick(*this, MouseButtonType::MIDDLE, true); return 0;
			case WM_MBUTTONUP:
				this->onMouseClick(*this, MouseButtonType::MIDDLE, false); return 0;
			case WM_RBUTTONDOWN:
				this->onMouseClick(*this, MouseButtonType::RIGHT, true); return 0;
			case WM_RBUTTONUP:
				this->onMouseClick(*this, MouseButtonType::RIGHT, false); return 0;
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

			wglMakeCurrent(hDC, hRC);
		}

		void SystemWindow::resize(int width, int height) {
			this->width = width;
			this->height = height;

			wglMakeCurrent(hDC, hRC);

			this->onResize(*this, width, height);

			//wglMakeCurrent(NULL, NULL);
		}

		void SystemWindow::draw() {
			wglMakeCurrent(hDC, hRC);

			this->onDraw(*this);

			//wglMakeCurrent(NULL, NULL);
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
			RECT clientRect, windowRect;
			GetClientRect(hWnd, &clientRect);
			GetWindowRect(hWnd, &windowRect);
			int borderWidth = (clientRect.right - clientRect.left) -
				(windowRect.right - windowRect.left);

			int borderHeight = (clientRect.bottom - clientRect.top) -
				(windowRect.bottom - windowRect.top);

			MoveWindow(hWnd, windowRect.left, windowRect.top,
				width + borderWidth, height + borderHeight, true);
		}

		void SystemWindow::setTitle(const wchar_t* title) {
			SetWindowText(hWnd, title);
		}

		void SystemWindow::setResizable(bool resizable) {
			if(resizable) {
				SetWindowLong(hWnd, GWL_STYLE,
					GetWindowLong(hWnd, GWL_STYLE) | WS_THICKFRAME | WS_MAXIMIZEBOX);
				this->setSize(this->width, this->height);
			} else {
				SetWindowLong(hWnd, GWL_STYLE,
					GetWindowLong(hWnd, GWL_STYLE) & ~(WS_THICKFRAME | WS_MAXIMIZEBOX));
				this->setSize(this->width, this->height);
			}
		}

		void SystemWindow::showWindow() {
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
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

		void SystemWindow::mainLoop() {
			while(SystemWindow::mainLoopStep()) {}
		}

	}
}
