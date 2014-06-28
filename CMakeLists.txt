cmake_minimum_required(VERSION 2.8)

# Debugging support
# add_definitions(-DBGFX_CONFIG_DEBUG=1)

set( BUILD_EXAMPLES OFF )

set (BGFX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (BGFX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (BGFX_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib )

foreach( OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES} )

  string( TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG )

  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} bin )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} lib )
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} lib )

endforeach()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../bx/include ${BGFX_INCLUDE_DIR} ${BGFX_EXAMPLES_DIR}/common ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty )

add_subdirectory(tools)

file(GLOB BGFX_SRC ${BGFX_SOURCE_DIR}/*.cpp ${BGFX_SOURCE_DIR}/*.h )

if(APPLE)

    add_definitions( -U__STRICT_ANSI__ -Wfatal-errors -Wunused-value )

    if(BGFX_BUILD_IOS EQUAL 1)

        add_definitions( -DBGFX_CONFIG_RENDERER_OPENGLES2=1 )
        if (BGFX_IOS_LEGACY EQUAL 1)
            include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../bx/include/compat/osx )
        endif()
        set ( BGFX_SRC ${BGFX_SRC} ${BGFX_SOURCE_DIR}/glcontext_external.cpp )
        
    else()

        # OSX

        find_library(COCOA_LIBRARY Cocoa)
        find_library(OpenGL_LIBRARY OpenGL )
        set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})

        add_definitions( -DBGFX_CONFIG_RENDERER_OPENGL=31 -msse2 )
        include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../bx/include/compat/osx )
        include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/khronos )

        set ( BGFX_SRC ${BGFX_SRC} ${BGFX_SOURCE_DIR}/glcontext_eagl.mm )
        set ( BGFX_SRC ${BGFX_SRC} ${BGFX_SOURCE_DIR}/glcontext_nsgl.mm )

#        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v" )
#        set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v" )

    endif()    

endif()

if (MSVC)

        # add_definitions(-DBGFX_CONFIG_RENDERER_OPENGL=1)
        set ( BGFX_SRC ${BGFX_SRC} ${BGFX_SOURCE_DIR}/renderer_d3d11.cpp )

endif()

if (LINUX)

    add_definitions ( -std=c++0x )
    set ( BGFX_SRC ${BGFX_SRC} ${BGFX_SOURCE_DIR}/renderer_gl.cpp ${BGFX_SOURCE_DIR}/glcontext_external.cpp )

endif()

add_library( bgfx ${BGFX_SRC} )
target_link_libraries( bgfx )

if( BUILD_EXAMPLES )

  file(GLOB example_common ${BGFX_EXAMPLES_DIR}/common/*.cpp
                           ${BGFX_EXAMPLES_DIR}/common/*.h
                           ${BGFX_EXAMPLES_DIR}/common/entry/*.cpp 
                           ${BGFX_EXAMPLES_DIR}/common/entry/*.mm 
                           ${BGFX_EXAMPLES_DIR}/common/font/*.cpp 
                           ${BGFX_EXAMPLES_DIR}/common/imgui/*.cpp 
                           ${BGFX_EXAMPLES_DIR}/common/nanovg/*.cpp    )

  add_library( common ${example_common} )
  target_link_libraries( common )

  set( EXTRA_LIBS ${EXTRA_LIBS} common )

  set( EXAMPLES 
          00-helloworld
          01-cubes
          02-metaballs
          03-raymarch
          04-mesh
          05-instancing
          06-bump
          07-callback
          08-update
          09-hdr
          10-font
          11-fontsdf
          12-lod
          13-stencil
          14-shadowvolumes
          15-shadowmaps-simple
          16-shadowmaps
          17-drawstress
          18-ibl
          19-oit
          20-nanovg
          21-deferred  )

  foreach( EXAMPLE ${EXAMPLES} )

    file( GLOB EXAMPLE_FILES 
          ${BGFX_EXAMPLES_DIR}/${EXAMPLE}/*.cpp 
          ${BGFX_EXAMPLES_DIR}/${EXAMPLE}/*.h    )
    add_executable( ${EXAMPLE} ${EXAMPLE_FILES} )
    set_target_properties( ${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./bin/examples/${EXAMPLE} )
    foreach( OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES} )

      string( TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG )
      set_target_properties( ${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ./bin/examples/${EXAMPLE} )

    endforeach()

    target_link_libraries( ${EXAMPLE} bgfx ${EXTRA_LIBS} )

  endforeach()

  set( SHADER_FILES "" )
  file( GLOB_RECURSE F_SHADER_FILES ${BGFX_EXAMPLES_DIR}/fs*.sc )
  file( GLOB_RECURSE V_SHADER_FILES ${BGFX_EXAMPLES_DIR}/vs*.sc )
  list( APPEND SHADER_FILES ${F_SHADER_FILES} ${V_SHADER_FILES} )

  set( SHADER_BIN_FILES "" )
  set( SHADERC_PLAT "osx" )
  set( SHADERC ${CMAKE_CURRENT_SOURCE_DIR}/tools/bin/darwin/shaderc )

  foreach( SHADER_FILE ${SHADER_FILES} )

    string( REGEX REPLACE ${BGFX_EXAMPLES_DIR}/ "" EXAMPLE_NAME ${SHADER_FILE} )  # strip example dir
    string( REGEX REPLACE "common/" "" EXAMPLE_NAME ${EXAMPLE_NAME} )             # strip common dir if present

    string( REGEX MATCH   "/.*"    SHADER_FILE_NAME ${EXAMPLE_NAME} )             # match after the last /
    string( REGEX REPLACE "^/" ""  SHADER_FILE_NAME ${SHADER_FILE_NAME} )         # strip leading /

    string( REGEX REPLACE "\\..*" "" SHADER_NAME ${SHADER_FILE_NAME} )             # strip file extension

    string( REGEX REPLACE "/.*" "" EXAMPLE_NAME  ${EXAMPLE_NAME} )                # strip everything after last /

    string( REGEX MATCH "^[fv]" SHADER_TYPE ${SHADER_FILE_NAME} )                 # strip initial char

    message(${SHADER_NAME})

    set( SHADER_OUTPUT_DIR  "${PROJECT_BINARY_DIR}/bin/examples/${EXAMPLE_NAME}/shaders/glsl" )
    set( SHADER_OUTPUT_FILE ${SHADER_OUTPUT_DIR}/${SHADER_NAME}.bin )

    # ensure directory is created for shaderc output
    file( MAKE_DIRECTORY ${SHADER_OUTPUT_DIR} )

    add_custom_command(
      OUTPUT  ${SHADER_OUTPUT_FILE}
      DEPENDS ${SHADER_FILE}
      COMMAND ${SHADERC} -f "${SHADER_FILE}" -o ${SHADER_OUTPUT_FILE} -i "${BGFX_SOURCE_DIR}" --platform ${SHADERC_PLAT} --type ${SHADER_TYPE}
      COMMENT "Compiling ${SHADER_FILE}..." )
    list( APPEND SHADER_BIN_FILES ${SHADER_OUTPUT_FILE} )

  endforeach()

  add_custom_target( SHADER_COMPILE ALL DEPENDS ${SHADER_BIN_FILES} shaderc )
endif( BUILD_EXAMPLES )
