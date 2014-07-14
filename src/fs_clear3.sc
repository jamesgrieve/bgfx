$input v_color0, v_texcoord0, v_texcoord1, v_texcoord2

/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_shader.sh"

void main()
{
	gl_FragData[0] = v_color0;
	gl_FragData[1] = v_texcoord0;
	gl_FragData[2] = v_texcoord1;
	gl_FragData[3] = v_texcoord2;
}
