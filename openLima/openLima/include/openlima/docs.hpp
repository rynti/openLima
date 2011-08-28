// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_DOCS_HPP
#define OPENLIMA_DOCS_HPP


/**
 * @mainpage OpenLima
 * 			 
 * 			 <p>OpenLima is a powerful engine for games and is licensed under the terms of the GNU
 * 			 Lesser General Public License (LGPL).</p>
 * 			 
 * 			 <h2>Can I have more information about the license?</h2>
 * 			 
 * 			 <p>The LGPL, under which this project is licensed, makes OpenLima free to use in your
 * 			 project, even if they may be with commercial purposes.</p>
 * 			 
 * 			 <p>You may ask, why the engine uses LGPL instead of GPL, well the reason is very
 * 			 simple, projects that are licensed under the terms of GPL aren't allowed to be
 * 			 used - even as a library - in projects that are using other licenses than GPL. The LGPL
 * 			 gives you the right to use this library in your project, no matter under which license
 * 			 your project is.</p>
 * 			 
 * 			 <h2>What is the engine built on?</h2>
 * 			 
 * 			 <p>The engine is made using C++, OpenGL and the boost framework.</p>
 * 			 
 * 			 <h2>Questions?</h2>
 * 			 
 * 			 <p>If you have any questions, feel free to ask me per
 * 			 <a href="mailto:robert.boehm94@gmail.com">mail</a> or write me a
 * 			 <a href="https://github.com/inbox/new/rynti">message on GitHub</a></p>
 */

/**
 * The main openlima namespace.
 */
namespace openlima {

	/**
	 * The graphics namespace contains stuff for drawing, etc.
	 */
	namespace graphics {}

	/**
	 * The GUI namespace contains stuff for window creation and management.
	 */
	namespace gui {}

	/**
	 * The input namespace contains communication interfaces for input devices.
	 */
	namespace input {}

	/**
	 * The util namespace contains additional, helpful utilities.
	 */
	namespace util {}

	/**
	 * The SIL namespace is the interface between the operating system and openlima.
	 * 
	 * SIL stands for "System independency layer" and it does exactly what the name says:
	 * It provides classes that are for the outside system-independent, but inside they work
	 * system-dependent, so every class here can be used (from outside) as if it is
	 * system-independent.
	 */
	namespace sil {}

}

#endif /* OPENLIMA_DOCS_HPP */