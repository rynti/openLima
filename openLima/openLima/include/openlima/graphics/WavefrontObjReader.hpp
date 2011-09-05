// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP
#define OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP

#include <boost/smart_ptr.hpp>

#include <iostream>
#include <vector>

#include <openlima/util/macros.hpp>
#include <openlima/util/Vector3.hpp>
#include <openlima/util/IResourceReader.hpp>
#include <openlima/graphics/StaticMesh.hpp>


namespace openlima {
	namespace graphics {

		/**
		 * A Wavefront .obj-reader.
		 * Can read static meshes.
		 *
		 * @sa	StaticMesh
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class WavefrontObjReader : public openlima::util::IResourceReader<StaticMesh> {
		private:

			/**
			 * Reads a vertex out of the given input stream.
			 *
			 * @param [in,out]	in			The input stream.
			 * @param [in,out]	vertices	The vertices.
			 */
			void readVertex(std::istream &in,
				std::vector<openlima::util::Vector3f>& vertices);

			/**
			 * Reads a normal out of the given input stream.
			 *
			 * @param [in,out]	in	   	The input stream.
			 * @param [in,out]	normals	The normals.
			 */
			void readNormal(std::istream &in,
				std::vector<openlima::util::Vector3f>& normals);

			/**
			 * Reads a face out of the given input stream.
			 *
			 * @param [in,out]	in			 	The input stream.
			 * @param [in,out]	vertexIndices	The vertex indices.
			 * @param [in,out]	normalIndices	The normal indices.
			 * @param [in,out]	vertices		The vertices.
			 * @param [in,out]	normals			The normals.
			 */
			void readFace(std::istream &in,
				std::vector<openlima::util::Vector3i>& vertexIndices,
				std::vector<openlima::util::Vector3i>& normalIndices,
				std::vector<openlima::util::Vector3f>& vertices,
				std::vector<openlima::util::Vector3f>& normals);

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
			int readFacePart(std::istream &in,
				int& vertex, int& texture, int& normal);

		public:

			/**
			 * Creates a new Wavefront .obj-Reader.
			 *
			 * Is able to correctly read .obj-ressources.
			 */
			OPENLIMA_DLL WavefrontObjReader();

			/**
			 * Query if 'name' is a legal resource name for this resource reader.
			 *
			 * @param	name	The name of the resource.
			 *
			 * @return	true if the name is legal, false if not.
			 */
			OPENLIMA_DLL virtual bool isLegal(const std::string& name) const;

			/**
			 * Reads a static mesh out of the given input stream.
			 *
			 * @param [in,out]	in	The input stream.
			 *
			 * @return	The read static mesh.
			 */
			OPENLIMA_DLL virtual boost::shared_ptr<StaticMesh> readResource(std::istream &in);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP */
