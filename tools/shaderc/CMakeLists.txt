cmake_minimum_required(VERSION 2.8)

project( shaderc )

set( SHADERC_DIR  ${CMAKE_CURRENT_SOURCE_DIR} )
set( FCPP_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/fcpp )
set( GLSL_OPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/glsl-optimizer )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tools )

foreach( OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES} )

  string( TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/bin/tools )

endforeach()

include_directories( ${FCPP_DIR} )
include_directories( ${GLSL_OPT_DIR}/include )
include_directories( ${GLSL_OPT_DIR}/src/glsl )
include_directories( ${GLSL_OPT_DIR}/src/mapi )
include_directories( ${GLSL_OPT_DIR}/src/mesa )

file( GLOB SHADERC_FILES ${GLSL_OPT_DIR}/src/mesa/main/*.c
                         ${GLSL_OPT_DIR}/src/mesa/program/*.c
                         ${GLSL_OPT_DIR}/src/mesa/*.h
                         ${GLSL_OPT_DIR}/src/glsl/*.cpp
                         ${GLSL_OPT_DIR}/src/glsl/*.c
                         ${GLSL_OPT_DIR}/src/glsl/*.h
                         ${GLSL_OPT_DIR}/src/glsl/glcpp/*.c
                         ${GLSL_OPT_DIR}/src/glsl/glcpp/*.h
                         ${FCPP_DIR}/cpp?.c
                         ${FCPP_DIR}/*.h
                         ${SHADERC_DIR}/*.cpp
                         ${SHADERC_DIR}/*.h  )

list( REMOVE_ITEM SHADERC_FILES ${GLSL_OPT_DIR}/src/glsl/main.cpp )

if(APPLE)

  find_library(COCOA_LIBRARY Cocoa)
  set(SHADERC_LIBS ${COCOA_LIBRARY})

endif()

set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fno-strict-aliasing )

add_definitions( -DNINCLUDE=64 -DNWORK=65536 -DNBUFF=65536 )

add_executable( shaderc ${SHADERC_FILES} )
#target_link_libraries( shaderc ${SHADERC_LIBS} )
