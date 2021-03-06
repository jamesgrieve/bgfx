cmake_minimum_required(VERSION 2.8)

project( texturec )

set( TEXTUREC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( BGFX_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
set( BX_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/../../../bx )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tools )

foreach( OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES} )

  string( TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/bin/tools )

endforeach()

include_directories( ${BGFX_DIR}/include )
include_directories( ${BGFX_DIR}/src )
include_directories( ${BX_DIR}/include )
include_directories( ${BGFX_DIR}/3rdparty/khronos )

file( GLOB TEXTUREC_FILES ${TEXTUREC_DIR}/*.cpp
                          ${BGFX_DIR}/src/image.*  )

if(APPLE)

  include_directories( ${BX_DIR}/include/compat/osx )

  find_library(COCOA_LIBRARY Cocoa)
  set(TEXTUREC_LIBS ${COCOA_LIBRARY})

endif()

if(MSVC)

	include_directories( ${BX_DIR}/include/compat/msvc )
	include_directories( "$ENV{DXSDK_DIR}/include" )

  	set( CMAKE_EXE_LINKER_FLAGS "" )
  	
endif()

add_executable( texturec ${TEXTUREC_FILES} )
target_link_libraries( texturec ${TEXTUREC_LIBS} )
