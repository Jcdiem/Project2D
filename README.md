# P2D
A simple 2D game engine built with C++ and SDL2. The game engine currently using meson for build and a custom script for acquiring libraries.

Currently the engine has basic funtionality for drawing objects to the background and adding entities with moving properties.

# Does this have any use to a non-dev?
Nope! If you are interested in playing a game made on this engine, we will be linking our game repos here as examples. Currently, however, releases have a 'demo' of sorts for testing what stage we are at in the engine.

# How to build and setup project for dev using engine
<ol>
  <li>Download the <a href="https://www.libsdl.org/download-2.0.php">SDL2 & SDL2 Image</a> dev libraries</li>
  <li><a href="https://docs.mesa3d.org/meson.html">Install Meson and Ninja</a></li>
  <li>Navigate to the project directory</li>
  <li>Run 'ninja -C build/'</li>
  <li>Run 'ninja -C build/ install'</li>
</ol>
Windows support can be found on our Windows branch and is currently in an unstable state.


If you run into any issues, please open an issue request.

# Progress
Follow our progress over at https://app.gitkraken.com/glo/board/XzQgMqsO6gARq5hb
