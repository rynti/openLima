// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP
#define OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP

#include <iostream>
#include <vector>

#include "../util/macros.hpp"
#include "../util/Vector3.hpp"
#include "StaticMesh.hpp"


namespace openlima {
	namespace graphics {

		/**
		 * A Wavefront .obj-reader.
		 * Can read static meshes.
		 * 
		 * @sa	StaticMesh
		 */
		class WavefrontObjReader {
		private:

			/**
			 * Reads a vertex out of the given input stream.
			 *
			 * @param [in,out]	in			The input stream.
			 * @param [in,out]	vertices	The vertices.
			 */
			static void readVertex(std::istream &in,
				std::vector<openlima::util::Vector3f>& vertices);
			
			/**
			 * Reads a normal out of the given input stream.
			 *
			 * @param [in,out]	in	   	The input stream.
			 * @param [in,out]	normals	The normals.
			 */
			static void readNormal(std::istream &in,
				std::vector<openlima::util::Vector3f>& normals);

			/**
			 * Reads a face out of the given input stream.
			 *
			 * @param [in,out]	in			 	The input stream.
			 * @param [in,out]	vertexIndices	The vertex indices.
			 * @param [in,out]	normalIndices	The normal indices.
			 */
			static void readFace(std::istream &in,
				std::vector<openlima::util::Vector3i>& vertexIndices,
				std::vector<openlima::util::Vector3i>& normalIndices);

			/**
			 * Reads a face part.
			 *
			 * @param [in,out]	in	   	The input stream.
			 * @param [in,out]	vertex 	The vertex index.
			 * @param [in,out]	texture	The texture index.
			 * @param [in,out]	normal 	The normal index.
			 *
			 * @return	A numeric value to determine what values were load. The bitmasks:
			 * 			01 - Texture index has been loaded.
			 * 			10 - Normal index has been loaded.
			 * 			The vertex index gets always loaded.
			 */
			static int readFacePart(std::istream &in,
				int& vertex, int& texture, int& normal);

		public:

			/**
			 * Reads a static mesh from a file with the given filename.
			 *
			 * @param [in,out]	filename	The filename of the file.
			 *
			 * @return	The new static mesh.
			 */
			static OPENLIMA_DLL StaticMesh* readStatic(char* filename);

			/**
			 * Reads a static mesh out of the given input stream.
			 *
			 * @param [in,out]	in	The input stream.
			 *
			 * @return	The new static mesh.
			 */
			static OPENLIMA_DLL StaticMesh* readStatic(std::istream &in);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP */
