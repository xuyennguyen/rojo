#ifndef ROJO_GRAPHICS_BACKENDS_OGL_OGL_INCLUDE_HPP
#define ROJO_GRAPHICS_BACKENDS_OGL_OGL_INCLUDE_HPP 

#ifdef _WIN32
// Windows header(s) for OpenGL
#include <Windows.h>
#include <GL/glew.h>
#else // _WIN32

#ifdef __APPLE__
// Mac header(s) for OpenGL
#include <OpenGL/gl.h>
#endif // __APPLE__

#endif // ROJO_GRAPHICS_BACKENDS_OGL_OGL_INCLUDE_HPP
