## Overview
This was my undergrad final year project; it's a strange combination of a realtime 3D graphics engine and a raytracing library.
The core part is a library called FP3D, which provides methods to set up a 3D scene either by programmatically generating primitives or by importing an OBJ file (basic models only). The scene can then be rendered using a realtime OpenGL-based renderer or a more complex raytracer.

The main challege I set myself for this project was to use as few external libraries as possible, so that I would have to learn the nitty-gritty details of several 3D graphics technologies and tools. The whole project uses only 3 external tools: [GLAD](https://github.com/Dav1dde/glad) for loading OpenGL function pointers, [GLFW](https://github.com/glfw/glfw) for creating the OpenGL demo window and [wxWidgets](https://github.com/wxWidgets/wxWidgets) for the GUI of the raytracing demo.
This was good for giving me a low-level understanding of the techniques I used, but the final product is, by consequence, fairly useless: everything FP3D does can be done better by existing tools.

Being an undergraduate project, this is not exactly the most elegant or well-designed program ever. Although I enjoyed writing it, FP3D was only meant as an exercise and a playground in 3D graphics, not for any kind of real-world use.

## Build instructions
Please clone this repository with the `-r` option to automatically download all project submodules, or use `git submodule update --init` if the repo is already cloned.

To build, `cd` to a new folder in the project directory and use `cmake ..` to generate the makefiles (on Unix) or the Visual Studio project (on Windows). Then compile with `make` (Unix) or by building the Visual Studio project (Windows).
