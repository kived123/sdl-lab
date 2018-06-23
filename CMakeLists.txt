cmake_minimum_required(VERSION 2.8)
project(lab-sdl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

if(LABSDLLIBS)
	set(CMAKE_FIND_ROOT_PATH ${LABSDLLIBS})	
endif()

find_package(glm REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(OpenGL REQUIRED)




set(SRC_LIST 
  src/Direction.cpp
  src/LabMesh.cpp
  src/Phys.cpp
  src/Map.cpp
  src/Renderer.cpp
  src/Rndroute.cpp
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} SOIL)
