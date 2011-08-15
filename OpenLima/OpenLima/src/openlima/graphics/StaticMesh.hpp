// Copyright (C) 2011 Robert Böhm
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

		class StaticMesh : public Mesh {
		public:
			std::vector<openlima::util::Vector3f> vertices;
			std::vector<openlima::util::Vector3f> normals;
			std::vector<openlima::util::Vector3i> vertexIndices;
			std::vector<openlima::util::Vector3i> normalIndices;

			OPENLIMA_DLL StaticMesh(std::vector<openlima::util::Vector3f> vertices,
				std::vector<openlima::util::Vector3f> normals,
				std::vector<openlima::util::Vector3i> vertexIndices,
				std::vector<openlima::util::Vector3i> normalIndices);

			OPENLIMA_DLL virtual void render();

		};

	}
}


#endif /* OPENLIMA_GRAPHICS_STATICMESH_HPP */