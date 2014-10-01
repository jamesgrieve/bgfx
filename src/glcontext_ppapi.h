/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_GLCONTEXT_PPAPI_H_HEADER_GUARD
#define BGFX_GLCONTEXT_PPAPI_H_HEADER_GUARD

#if BX_PLATFORM_NACL

#	include <ppapi/gles2/gl2ext_ppapi.h>
#	include <ppapi/c/pp_completion_callback.h>
#	include <ppapi/c/ppb_instance.h>
#	include <ppapi/c/ppb_graphics_3d.h>

namespace bgfx
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, bool _vsync);

		static bool isSwapChainSupported();
		SwapChainGL* createSwapChain(void* _nwh);
		void destorySwapChain(SwapChainGL*  _swapChain);
		void swap(SwapChainGL* _swapChain = NULL);
		void makeCurrent(SwapChainGL* _swapChain = NULL);

		void import();
		bool isValid() const;
	};
} // namespace bgfx

#endif // BX_PLATFORM_NACL

#endif // BGFX_GLCONTEXT_PPAPI_H_HEADER_GUARD
