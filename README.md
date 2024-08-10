# RaveGL - A Procedural Visualizer

Hey there!

Welcome to RaveGL, a procedural visualizer that is synchronized to music. This project is a work in progress, so feel free to contribute or give feedback!

# Goal of the Project

The goal is to give anyone with a computer the ability to create a unique visual experience that is synchronized to music without the need for expensive software, hardware, or VFX knowledge.

# Typical use cases

- Pre-record visualizations that can be played back in a live performance setting. (e.g. a DJ set).

- Create a unique visual experience reacting to music in real-time.

- Create a visual representation of your music that can be shared on social media.

- Help with your creative process by providing a visual representation of your music.

# About RaveGL (Technical Details)

- The project is written in C++ and uses the OpenGL graphics library for rendering.

- The scene is generated using a series of algorithms that create a unique visual experience every time the program is run. No two runs will be the same.

- The visualizer is designed to be used in a live performance setting, where the visuals are synchronized to music or other audio input.

# How to Build

## Prerequisites

- Install the following libraries:
  - OpenGL
  - GLFW
  - GLEW
  - GLM
  - GLSL
  - glad.h

## Build Instructions

- Clone the repository
- Run `make -j8` in the root directory
- Run `./raveGl` to start the visualizer

# Roadmap

- [ ] Generate scene procedurally (based on audio input, etc...)
- [ ] Add Text to the scene (e.g. Dj name)
- [ ] Make it seem like the camera is moving around the scene (e.g. camera shake, camera rotation, etc...)
- [ ] Add more objects to the scene (e.g parsing ".obj" files, etc...)
- [ ] Possibility to load custom obj files from a directory (samples will be provided)
- [ ] Add Physics to objects using Bullet Physics
- [ ] Complex shapes like fractals, torus to the scene
- [ ] Effects to the scene (e.g. bloom, etc...)
- [ ] Shaders to the scene (e.g. water shader, etc...)
- [ ] Particles to the scene (e.g. fire, etc...)
- [ ] Lights to the scene (e.g. spotlights, etc...)
- [ ] Textures to the scene (e.g. skybox, etc...)

VERY LATER:
- [ ] AI powered scene modification using Stable Diffusion (e.g. scene changes based on the mood of the music, it would propose different effects...)

# Authors

- [Alan] (https://github.com/ExtraBinoss)
- [Ewan] (https://github.com/NoxLoveYa)