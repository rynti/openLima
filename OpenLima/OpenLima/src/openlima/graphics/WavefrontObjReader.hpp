#ifndef OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP
#define OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP

#include <iostream>

#include "../util/macros.hpp"
#include "StaticMesh.hpp"
#include "../util/IReader.hpp"


namespace openlima {
	namespace graphics {

		class WavefrontObjReader : public IReader<StaticMesh>
		{
		private:
			static const size_t LINEBUFFER_SIZE = 512;

		public:
			static L_DLL StaticMesh* readStatic(char* filename);
			static L_DLL StaticMesh* readStatic(std::istream &in);

		};

	}
}

#endif /* OPENLIMA_GRAPHICS_WAVEFRONTOBJREADER_HPP */