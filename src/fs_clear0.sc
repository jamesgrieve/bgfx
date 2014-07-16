$input v_color0, v_texcoord0, v_texcoord1, v_texcoord2

/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_shader.sh"

void main()
{
	gl_FragColor = v_color0;
}
