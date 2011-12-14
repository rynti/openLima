# Copyright (C) 2011 Robert Boehm
# This file is part of openLima.
#
# You should have received a copy of the GNU Lesser General Public License
# along with openLima. If not, see: <http://www.gnu.org/licenses/>.
#
# LimaBeans

project(LimaBeans)

find_package(Boost REQUIRED COMPONENTS system signals filesystem date_time)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

include_directories("../openLima/include")

file(GLOB LIMABEANS_SOURCES "source/*.cpp")

add_executable(LimaBeans ${LIMABEANS_SOURCES})
target_link_libraries(LimaBeans openLima ${Boost_LIBRARIES})
add_dependencies(LimaBeans openLima)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}/resources"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources"
)
add_custom_target(LimaBeansResources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
