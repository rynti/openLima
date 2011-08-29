# openLima
project(openLima)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS signals filesystem date_time)
find_package(OpenGL)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})


include_directories("include")


file(GLOB_RECURSE OPENLIMA_SOURCES
	"source/openlima/*.cpp"
)

file(GLOB_RECURSE OPENLIMA_HEADERS
	"include/openlima/*.hpp"
)


file(GLOB OPENLIMA
	"source/openlima/*.cpp"
	"include/openlima/*.hpp"
)
source_group("openlima" FILES ${OPENLIMA})

file(GLOB OPENLIMA_GRAPHICS
	"source/openlima/graphics/*.cpp"
	"include/openlima/graphics/*.hpp"
)
source_group("openlima\\graphics" FILES ${OPENLIMA_GRAPHICS})

file(GLOB OPENLIMA_INPUT
	"source/openlima/input/*.cpp"
	"include/openlima/input/*.hpp"
)
source_group("openlima\\input" FILES ${OPENLIMA_INPUT})

file(GLOB OPENLIMA_GUI
	"source/openlima/gui/*.cpp"
	"include/openlima/gui/*.hpp"
)
source_group("openlima\\gui" FILES ${OPENLIMA_GUI})

file(GLOB OPENLIMA_SIL
	"source/openlima/sil/*.cpp"
	"include/openlima/sil/*.hpp"
)
source_group("openlima\\sil" FILES ${OPENLIMA_SIL})

file(GLOB OPENLIMA_UTIL
	"source/openlima/util/*.cpp"
	"include/openlima/util/*.hpp"
)
source_group("openlima\\util" FILES ${OPENLIMA_UTIL})


IF(BUILD_SHARED_LIBS)
	add_library(openLima SHARED ${OPENLIMA_HEADERS} ${OPENLIMA_SOURCES})
ELSE(BUILD_SHARED_LIBS)
	IF(BUILD_STATIC_LIBS)
		add_library(openLima STATIC ${OPENLIMA_HEADERS} ${OPENLIMA_SOURCES})
	ELSE(BUILD_STATIC_LIBS)
		add_library(openLima ${OPENLIMA_HEADERS} ${OPENLIMA_SOURCES})
	ENDIF(BUILD_STATIC_LIBS)
ENDIF(BUILD_SHARED_LIBS)

target_link_libraries(openLima ${OPENGL_LIBRARY} ${Boost_LIBRARIES})
