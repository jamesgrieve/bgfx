cmake_minimum_required(VERSION 2.8)

# Debugging support
# add_definitions(-DBGFX_CONFIG_DEBUG=1)

set (BGFX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (BGFX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (BGFX_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../bx/include ${BGFX_INCLUDE_DIR} ${BGFX_EXAMPLES_DIR}/common ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty )

set ( BGFX_SRC ${BGFX_SOURCE_DIR}/bgfx.cpp 
               ${BGFX_SOURCE_DIR}/vertexdecl.cpp 
               ${BGFX_SOURCE_DIR}/image.cpp 
               ${BGFX_SOURCE_DIR}/image.cpp 
               ${BGFX_SOURCE_DIR}/glcontext_egl.cpp 
               ${BGFX_SOURCE_DIR}/glcontext_glx.cpp 
               ${BGFX_SOURCE_DIR}/glcontext_ppapi.cpp 
               ${BGFX_SOURCE_DIR}/glcontext_wgl.cpp 
               ${BGFX_SOURCE_DIR}/renderer_d3d9.cpp 
               ${BGFX_SOURCE_DIR}/renderer_d3d11.cpp 
               ${BGFX_SOURCE_DIR}/renderer_gl.cpp 
               ${BGFX_SOURCE_DIR}/renderer_null.cpp    )

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

#        include_directories( /System/Library/Frameworks )
        find_library(COCOA_LIBRARY Cocoa)
        find_library(OpenGL_LIBRARY OpenGL )
        set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})

        add_definitions( -DBGFX_CONFIG_RENDERER_OPENGL=31 -msse2 )
#        add_definitions( -msse2 )
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

file(GLOB example_common ${BGFX_EXAMPLES_DIR}/common/*.cpp
                         ${BGFX_EXAMPLES_DIR}/common/entry/*.cpp 
                         ${BGFX_EXAMPLES_DIR}/common/entry/*.mm 
                         ${BGFX_EXAMPLES_DIR}/common/font/*.cpp 
                         ${BGFX_EXAMPLES_DIR}/common/imgui/*.cpp 
                         ${BGFX_EXAMPLES_DIR}/common/nanovg/*.cpp    )

add_library( common ${example_common} )
target_link_libraries( common )

set( EXTRA_LIBS ${EXTRA_LIBS} common )

add_executable( helloworld          ${BGFX_EXAMPLES_DIR}/00-helloworld/helloworld.cpp )
add_executable( cubes               ${BGFX_EXAMPLES_DIR}/01-cubes/cubes.cpp )
add_executable( metaballs           ${BGFX_EXAMPLES_DIR}/02-metaballs/metaballs.cpp )
add_executable( raymarch            ${BGFX_EXAMPLES_DIR}/03-raymarch/raymarch.cpp )
add_executable( mesh                ${BGFX_EXAMPLES_DIR}/04-mesh/mesh.cpp )
add_executable( instancing          ${BGFX_EXAMPLES_DIR}/05-instancing/instancing.cpp )
add_executable( bump                ${BGFX_EXAMPLES_DIR}/06-bump/bump.cpp )
add_executable( callback            ${BGFX_EXAMPLES_DIR}/07-callback/callback.cpp )
add_executable( update              ${BGFX_EXAMPLES_DIR}/08-update/update.cpp )
add_executable( hdr                 ${BGFX_EXAMPLES_DIR}/09-hdr/hdr.cpp )
add_executable( font                ${BGFX_EXAMPLES_DIR}/10-font/font.cpp )
add_executable( fontsdf             ${BGFX_EXAMPLES_DIR}/11-fontsdf/fontsdf.cpp )
add_executable( lod                 ${BGFX_EXAMPLES_DIR}/12-lod/lod.cpp )
add_executable( stencil             ${BGFX_EXAMPLES_DIR}/13-stencil/stencil.cpp )
add_executable( shadowvolumes       ${BGFX_EXAMPLES_DIR}/14-shadowvolumes/shadowvolumes.cpp )
add_executable( shadowmaps-simple   ${BGFX_EXAMPLES_DIR}/15-shadowmaps-simple/shadowmaps_simple.cpp )
add_executable( shadowmaps          ${BGFX_EXAMPLES_DIR}/16-shadowmaps/shadowmaps.cpp )
add_executable( drawstress          ${BGFX_EXAMPLES_DIR}/17-drawstress/drawstress.cpp )
add_executable( ibl                 ${BGFX_EXAMPLES_DIR}/18-ibl/ibl.cpp )
add_executable( oit                 ${BGFX_EXAMPLES_DIR}/19-oit/oit.cpp )
add_executable( nanovg              ${BGFX_EXAMPLES_DIR}/20-nanovg/nanovg.cpp )
add_executable( deferred            ${BGFX_EXAMPLES_DIR}/21-deferred/deferred.cpp )

target_link_libraries( helloworld           bgfx ${EXTRA_LIBS} )
target_link_libraries( cubes                bgfx ${EXTRA_LIBS} )
target_link_libraries( metaballs            bgfx ${EXTRA_LIBS} )
target_link_libraries( raymarch             bgfx ${EXTRA_LIBS} )
target_link_libraries( mesh                 bgfx ${EXTRA_LIBS} )
target_link_libraries( instancing           bgfx ${EXTRA_LIBS} )
target_link_libraries( bump                 bgfx ${EXTRA_LIBS} )
target_link_libraries( callback             bgfx ${EXTRA_LIBS} )
target_link_libraries( update               bgfx ${EXTRA_LIBS} )
target_link_libraries( hdr                  bgfx ${EXTRA_LIBS} )
target_link_libraries( font                 bgfx ${EXTRA_LIBS} )
target_link_libraries( fontsdf              bgfx ${EXTRA_LIBS} )
target_link_libraries( lod                  bgfx ${EXTRA_LIBS} )
target_link_libraries( stencil              bgfx ${EXTRA_LIBS} )
target_link_libraries( shadowvolumes        bgfx ${EXTRA_LIBS} )
target_link_libraries( shadowmaps-simple    bgfx ${EXTRA_LIBS} )
target_link_libraries( shadowmaps           bgfx ${EXTRA_LIBS} )
target_link_libraries( drawstress           bgfx ${EXTRA_LIBS} )
target_link_libraries( ibl                  bgfx ${EXTRA_LIBS} )
target_link_libraries( oit                  bgfx ${EXTRA_LIBS} )
target_link_libraries( nanovg               bgfx ${EXTRA_LIBS} )
target_link_libraries( deferred             bgfx ${EXTRA_LIBS} )

set( SHADER_FILES "" )
file( GLOB_RECURSE F_SHADER_FILES ${BGFX_EXAMPLES_DIR}/fs*.sc )
file( GLOB_RECURSE V_SHADER_FILES ${BGFX_EXAMPLES_DIR}/vs*.sc )
set( SHADER_BIN_FILES "" )
set( SHADERC_PLAT "osx" )
set( SHADERC ${CMAKE_CURRENT_SOURCE_DIR}/tools/bin/darwin/shaderc )

foreach( SHADER_FILE ${V_SHADER_FILES} )
  add_custom_command(
    OUTPUT "${SHADER_FILE}.bin"
    DEPENDS ${SHADER_FILE}
    COMMAND ${SHADERC} -f "${SHADER_FILE}" -o "${SHADER_FILE}.bin" -i "${BGFX_SOURCE_DIR}" --platform ${SHADERC_PLAT} --type v
    COMMENT "Compiling ${SHADER_FILE}..." )
  list( APPEND SHADER_BIN_FILES "${SHADER_FILE}.bin" )
endforeach()

foreach( SHADER_FILE ${F_SHADER_FILES} )
  add_custom_command(
    OUTPUT "${SHADER_FILE}.bin"
    DEPENDS ${SHADER_FILE}
    COMMAND ${SHADERC} -f "${SHADER_FILE}" -o "${SHADER_FILE}.bin" -i "${BGFX_SOURCE_DIR}" --platform ${SHADERC_PLAT} --type f
    COMMENT "Compiling ${SHADER_FILE}..." )
  list( APPEND SHADER_BIN_FILES "${SHADER_FILE}.bin" )
endforeach()

add_custom_target( SHADER_COMPILE ALL DEPENDS ${SHADER_BIN_FILES} )

add_subdirectory(tools)