# rojo

A cross-platform C++11 library that helps creating games and other graphical applications easier to write within C++. 

The main reason that this library is being created is for educational purposes.

# Table of Contents

1. Design Goals
2. Dependices
3. Supported Platforms
	- Platforms
	- Supported Rendering Backends
4. Getting Started
	- Downloading the Library
	- Dependencies
	- Installation
5. Using the Library
	- Modules
		- Math
		- Graphics
			- Dependencies
			- API
			- 2D
			- 3D
		- Audio
			- Dependencies
			- API
			- 2D
			- 3D

# Design Goals

- Simple and yet easy to use with C++
- No unnecessary overhead; use of compile-time polymorphism wherever necessary*
- Use of standard C++ design patterns, namely RAII
- Use of new C++11 design patterns (e.g. moving over copying)
- Use of the new C++11 standard library

*some people writing C++ code seem to mis-use virtual functions, especially when the implementation of something should not change during run-time.

# Dependices

In order to build this library, it is reccomended that you use CMake to do so. As I am using CMake as a build system. It is possible to not use CMake, but it will make your life much harder.

# Supported Platforms

## Platforms

The following platforms will be supported:

- OS X
- Linux
- Windows
- iOS

> **NOTE:**
>
> OS X 10.9 will more than likely be the first operating system
> to be supported, as I develop directly from OS X 10.9.


## Supported Rendering Backends

- OpenGL 3.x

> **NOTES:**
>
> 1. These are just the rendering backends that are supported out of the box. 
> 2. DirectX (and possibly other APIs) may be supported in the future.

# Getting Started

## Downloading the Library

There are multiple ways to download the library. Here are your options:

- [clone] the repo: `git clone https://github.com/miguelishawt/rojo.git`
- Download the library ([zip]/[tar-gz])

## Dependencies

An updated compiler that supports C++11 features.

## Installation

    mkdir build; cd build
    ccmake ..
    
# Using The Library

## Concepts

This library heavily uses of what is known as concepts. As one of the design goals of this library is to use compile-time polymorphism whenever possible. A concept basically is just an interface that guarentees that certain methods are there.

## Naming conventions

The naming conventions of the library is somewhat similiar to the standard library.

## Binary naming conventions

The binraries produced from compiling this library follow the same pattern(s). 

### The "name" of the Binary

The "name" of the binary is either defined by the module (e.g. `graphics` for the Graphics Module), or by the test-case or example name (e.g. `example_Teapot`)

### Binary Prefixes

All binaries have one prefix, followed by an underscore (`_`). This prefix is dependent on what type of binary you are building. Here is a list of all the types of binaries that this library may produce:

| Prefix | Type of Binary | Explanation |
|:-------|:----------------|:------------|
| rojo   | Module Binary   | These binaries are created via modules of the library. They do not have to be directly created via the module, but they do relate to the module. For example, backends within the `graphics` module require to be compiled (as in a binary is required to be created). |
| test   | Test-case Binary | These binaries are created from test-cases within the library, within the `test` directory.  |
| example | Example Binary | These binraries are created from examples within the library, within the `examples` directory. |

> **NOTE:**
> 
> As mentioned before, all prefixes are followed by an underscore. For example: `test_<binary-name>`.

### Suffixes

| Suffix | Explanation |
|:-------|:------------|
| `_d`     | A binary compiled with debug symbols, and is un-optimized (unless you decide to optimze the binary via `CMAKE_CXX_FLAGS`) |
| `_s`     | A binary that is statically compiled. |
| `_d_s`  | A binary that has debug symbols and is statically compiled. |

## Modules

The library is split up into various modules, which may even have multiple modules of the their own. This is so that there is no unnecessary code that is linked with your own executable. It is quite similiar to SFML's module system, however, there are multiple more layers of modules. Here is a list of all the modules avaliable:

- Math
- Graphics
	- Dependencies
	- API
	- 2D Support
		- Sprites
		- Particles
	- 3D Support
		- Meshes
		- Scene Graph
		- Particles
- Audio
	- Dependencies
	- API

## Math

At the current moment, the math library is just GLM, as it has not been implemented as of yet.

## Graphics

### Dependices

- rojo_math (rojo's Math Module)

### API

The API is composed of simple building blocks in order for other libraries/modules to build upon. The API may be of what too low-level to be used directly.

#### Graphics Backend

In order to actually use the graphics module for pratical purposes, you require to have a graphics backend implemented and obviously link towards it. You can either create your own or use a pre-existing one (all pre-made backends are within the `rojo/backends/` directory). The currently avaliable backends are listed below:

| Backend | Description|
|:--------|:-----------|
| ogl_backend | An OpenGL backend |


Please see the documentation if you wish to create your own graphics backend.
 
#### Graphics Device

Once you have a backend ready to use (linked to your binary) you may use it via a graphics device. A graphics device provides an abstract interface over all backends that could be used. The main reason a graphics device exists is to abstract all the lower-level API-specific details out of the picture. 

#### Resources

A resource is a resource which is typically allocated on your GPU. Here is a list of all the avaliable resources that may be allocated from a graphics device.

| Resource   | Description | 
|:-----------|:-------------|
| texture     | Describes a texture to be used for rendering |
| vertex_buffer | Describes a buffer, filled with vertices |
| index_buffer | Describes an index buffer |
| shader       | Describes a shader |
| program | Describes a shader program | 

### 2D Support

TODO

### 3D Support

TODO

## Audio

As of the current moment, the audio library has not been implemented.

# License
Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

[clone]: github-mac://openRepo/https://github.com/miguelishawt/rojo
[zip]: https://api.github.com/repos/miguelishawt/anax/zipball
[tar-gz]: https://api.github.com/repos/miguelishawt/rojo/tarball
