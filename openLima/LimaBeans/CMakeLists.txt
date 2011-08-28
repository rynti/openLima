# LimaBeans
project(LimaBeans)

find_package(Boost REQUIRED COMPONENTS signals filesystem date_time)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

include_directories("../openLima/include")

add_executable(LimaBeans "source/*.cpp")
target_link_libraries(LimaBeans openLima ${Boost_LIBRARIES})
add_dependencies(LimaBeans openLima)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/resources"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}/resources"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources"
)
add_custom_target(LimaBeansResources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)