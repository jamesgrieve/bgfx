static const uint8_t fs_clear1_glsl[133] =
{
	0x46, 0x53, 0x48, 0x02, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x69, 0x6e, // FSH.......v...in
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, //  vec4 v_color0;.
	0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // in vec4 v_texcoo
	0x72, 0x64, 0x30, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, // rd0;.void main (
	0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, // ).{.  gl_FragDat
	0x61, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, // a[0] = v_color0;
	0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x31, // .  gl_FragData[1
	0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, // ] = v_texcoord0;
	0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                                   // .}...
};

static const uint8_t fs_clear1_dx11[133] =
{
	0x46, 0x53, 0x48, 0x02, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x69, 0x6e, // FSH.......v...in
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, //  vec4 v_color0;.
	0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // in vec4 v_texcoo
	0x72, 0x64, 0x30, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, // rd0;.void main (
	0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, // ).{.  gl_FragDat
	0x61, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, // a[0] = v_color0;
	0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x31, // .  gl_FragData[1
	0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, // ] = v_texcoord0;
	0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                                   // .}...
};

static const uint8_t fs_clear1_dx9[133] =
{
	0x46, 0x53, 0x48, 0x02, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x69, 0x6e, // FSH.......v...in
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, //  vec4 v_color0;.
	0x69, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // in vec4 v_texcoo
	0x72, 0x64, 0x30, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, // rd0;.void main (
	0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, // ).{.  gl_FragDat
	0x61, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, // a[0] = v_color0;
	0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x31, // .  gl_FragData[1
	0x5d, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, // ] = v_texcoord0;
	0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                                   // .}...
};
