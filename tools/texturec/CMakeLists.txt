cmake_minimum_required(VERSION 2.8)

project( texturec )

set( TEXTUREC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( BGFX_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
set( BX_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/../../../bx )

message( ${TEXTUREC_DIR} )
message( ${BGFX_DIR} )
message( ${BX_DIR} )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEXTUREC_DIR}/../bin/darwin )

include_directories( ${BGFX_DIR}/include )
include_directories( ${BGFX_DIR}/src )
include_directories( ${BX_DIR}/include )
include_directories( ${BX_DIR}/include/compat/osx )
include_directories( ${BGFX_DIR}/3rdparty/khronos )

file( GLOB TEXTUREC_FILES ${TEXTUREC_DIR}/*.cpp
                          ${BGFX_DIR}/src/image.*  )

if(APPLE)

  find_library(COCOA_LIBRARY Cocoa)
  set(TEXTUREC_LIBS ${COCOA_LIBRARY})

endif()

add_executable( texturec ${TEXTUREC_FILES} )
target_link_libraries( texturec ${TEXTUREC_LIBS} )
