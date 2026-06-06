# Build process

To build 3rd party libraries call python script form Window root folder

Example:
```sh
# For Linux/MacOS
python3 thirdparty/build_dependencies.py

# Windows
python thirdparty\\build_dependencies.py
```

Configure project:
```sh
cmake --preset debug
# Or
cmake --preset release
# Or
cmake --preset tests
```

Build project:
```sh
cmake --build --preset debug
# Or
cmake --preset debug / cmake --build --preset debug

# For release and tests similar approach
```

Build and run tests:
```sh
cmake --preset tests
cmake --build --preset tests
ctest --preset tests
```

# Tech

Was tested on Windows 11 and Ubuntu 24.04 LTS.

- Compiler: clang 21.1.0
- Generator: Ninja
- GLFW: 3.3.8
- C++: 23
- Graphics Renderer: OpenGL, Vulkan
- Unit test: googletest 1.17.0

# Renderer

Default renderer is OpenGL, to use Vulkan add `-DWINDOW_USE_VULKAN=ON` flag to cache
