// Copyright (C) 2011 Robert Boehm
// This file is part of OpenLima.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with OpenLima. If not, see: <http://www.gnu.org/licenses/>.

#ifndef OPENLIMA_GRAPHICS_STATICMESH_HPP
#define OPENLIMA_GRAPHICS_STATICMESH_HPP

#include <vector>

#include "../util/macros.hpp"
#include "../util/Vector3.hpp"
#include "Mesh.hpp"


namespace openlima {
	namespace graphics {

		/**
		 * A static mesh. Use - for instance - the WavefrontObjReader to load a static mesh.
		 *
		 * @sa	IRenderable
		 * @sa	Mesh
		 * @sa	WavefrontObjReader
		 *
		 * @author	rynti (Robert Boehm)
		 */
		class StaticMesh : public Mesh {
		private:

			/**
			 * Renders only the vertices.
			 */
			OPENLIMA_DLL void renderVertices();

			/**
			 * Renders the vertices and the normals.
			 */
			OPENLIMA_DLL void renderVerticesAndNormals();
			
		public:

			/** The vertices. */
			std::vector<openlima::util::Vector3f> vertices;

			/** The normals. */
			std::vector<openlima::util::Vector3f> normals;

			/** The vertex indices. */
			std::vector<openlima::util::Vector3i> vertexIndices;

			/** The normal indices. */
			std::vector<openlima::util::Vector3i> normalIndices;

			/**
			 * Creates a new static mesh based upon the mesh data.
			 *
			 * @param	vertices	 	The vertices.
			 * @param	normals		 	The normals.
			 * @param	vertexIndices	The vertex indices.
			 * @param	normalIndices	The normal indices.
			 */
			OPENLIMA_DLL StaticMesh(std::vector<openlima::util::Vector3f> vertices,
				std::vector<openlima::util::Vector3f> normals,
				std::vector<openlima::util::Vector3i> vertexIndices,
				std::vector<openlima::util::Vector3i> normalIndices);

			/**
			 * Renders this static mesh.
			 */
			OPENLIMA_DLL virtual void render();

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_STATICMESH_HPP */
