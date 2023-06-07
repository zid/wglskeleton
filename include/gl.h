#ifndef GL_H
#define GL_H
#include <gl/gl.h>
#include <stddef.h>

void gl_init_procs(void);

/* These are missing from my ancient gl.h - delete if you get a conflict */
typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

#define GL_FRAGMENT_SHADER      0x8B30
#define GL_VERTEX_SHADER        0x8B31
#define GL_INFO_LOG_LENGTH      0x8B84

#define GL_STATIC_DRAW          0x88E4
#define GL_ARRAY_BUFFER         0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FRAGMENT_SHADER      0x8B30
#define GL_VERTEX_SHADER        0x8B31
#define GL_TEXTURE0             0x84C0
#define GL_INFO_LOG_LENGTH      0x8B84
#define GL_TEXTURE_CUBE_MAP     0x8513
#define GL_TEXTURE_WRAP_R       0x8072
#define GL_CLAMP_TO_EDGE        0x812F
#define GL_MULTISAMPLE          0x809D

#define GL_TEXTURE_BASE_LEVEL          0x813C
#define GL_TEXTURE_MAX_LEVEL           0x813D
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A

#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB        0x2042
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_ACCELERATION_ARB   0x2003
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001

/*
 * Someone will actually define these function pointers, but we
 * just want to provide a declaration to most people.
 * The someone will define ABI but non-extern.
 */
#ifndef ABI
#define ABI extern __attribute__((stdcall))
#endif

/* 
 * Include the function list.
 * ABI acts like an X-Macro to provide a prototype for each function.
 */
#include "gl-functions.h"

#endif