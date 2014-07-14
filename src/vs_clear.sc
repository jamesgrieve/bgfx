$input a_position, a_color0, a_texcoord0, a_texcoord1, a_texcoord2
$output v_color0, v_texcoord0, v_texcoord1, v_texcoord2

/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_shader.sh"

void main()
{
	gl_Position = vec4(a_position, 1.0);
	v_color0 = a_color0;
	v_texcoord0 = a_texcoord0;
	v_texcoord1 = a_texcoord1;
	v_texcoord2 = a_texcoord2;
}
