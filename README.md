# Build process

To build 3rd party libraries call python script form Window root folder

Example:
```sh
python3 "/thirdparty/build_dependencies.py
```
# Renderer

To use Vulkan specify `cmake -Bbuild . -DWINDOW_USE_VULKAN=ON`
For OpenGL remove `build` and `bin` folders and build with `cmake -Bbuild .` or `cmake -Bbuild . -DWINDOW_USE_VULKAN=OFF`
