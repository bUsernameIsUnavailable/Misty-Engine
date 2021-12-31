cmake_minimum_required(VERSION 3.21)
project(Misty)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
list(APPEND OPENGL_LIBRARIES "glew32" "glew32s")
if (NOT OpenGL_FOUND)
    message(ERROR " OpenGL not found!")
endif(NOT OpenGL_FOUND)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if (NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

set(glm_DIR "lib/glm/cmake/glm")
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})
if (NOT glm_FOUND)
    message(ERROR " glm not found!")
endif(NOT glm_FOUND)

find_library(SOIL_LIB SOIL.lib ${PROJECT_SOURCE_DIR}/lib/soil)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/PCH.cxx CONTENT "")
add_library(PCH OBJECT ${CMAKE_CURRENT_BINARY_DIR}/PCH.cxx)
target_precompile_headers(PCH PRIVATE PCH.hxx)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL_LIB})
target_precompile_headers(${PROJECT_NAME} REUSE_FROM PCH)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E
        create_symlink ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
