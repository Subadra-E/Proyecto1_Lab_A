cmake_minimum_required(VERSION 3.0)
project(paa_reader)

find_package(ROOT REQUIRED)

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${ROOT_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIR}
                    )

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


add_executable(paa_reader ${sources} read_paa.cpp)
target_link_libraries(paa_reader ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARIES})

