cmake_minimum_required(VERSION 3.16.3)
project(Misty)

set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})
add_definitions(${OPENGL_DEFINITIONS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_libraries(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
add_definitions(${GLEW_DEFINITIONS})

set(glm_DIR "lib/glm/cmake/glm")
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_libraries(${GLM_LIBRARIES})
add_definitions(${GLM_DEFINITIONS})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/PCH.cxx CONTENT "")
add_library(PCH OBJECT ${CMAKE_CURRENT_BINARY_DIR}/PCH.cxx)
target_precompile_headers(PCH PRIVATE PCH.hxx)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} REUSE_FROM PCH)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

find_library(SOIL_LIB SOIL.lib ${PROJECT_SOURCE_DIR}/lib/soil)
if(SOIL_LIB)
    target_link_libraries(${PROJECT_NAME} ${SOIL_LIB})
endif()

option(DISPLAY 0)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "Symbolic link for resources folder"
)
