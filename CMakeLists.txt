cmake_minimum_required(VERSION 3.25)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)

project(Window LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WINDOW_USE_VULKAN "Use Vulkan (GLFW_NO_API); otherwise OpenGL context" OFF)

if(WINDOW_USE_VULKAN)
    add_compile_definitions(WINDOW_USE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

# Set output directory: bin/<architecture>/<os>/<Debug|Release>
string(TOLOWER "${CMAKE_SYSTEM_NAME}" WINDOW_OS)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" WINDOW_ARCH)
set(WINDOW_BIN_ROOT "${CMAKE_SOURCE_DIR}/bin/${WINDOW_ARCH}/${WINDOW_OS}")

if(CMAKE_CONFIGURATION_TYPES)
    # Multi-config generators (Visual Studio, Ninja Multi-Config).
    foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER "${cfg}" cfg_upper)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg_upper} "${WINDOW_BIN_ROOT}/${cfg}")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg_upper} "${WINDOW_BIN_ROOT}/${cfg}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${cfg_upper} "${WINDOW_BIN_ROOT}/${cfg}")
    endforeach()
    set(WINDOW_OUTPUT_DIR "${WINDOW_BIN_ROOT}/$<CONFIG>")
else()
    # Single-config generators.
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WINDOW_BIN_ROOT}/${CMAKE_BUILD_TYPE}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${WINDOW_BIN_ROOT}/${CMAKE_BUILD_TYPE}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${WINDOW_BIN_ROOT}/${CMAKE_BUILD_TYPE}")
    set(WINDOW_OUTPUT_DIR "${WINDOW_BIN_ROOT}/${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX "" CACHE STRING "" FORCE)

file(GLOB_RECURSE WINDOW_BINS_LIST CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bins/*.*")
file(GLOB_RECURSE WINDOW_LIBS_LIST CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libs/*.*")

foreach(_bin_file IN LISTS WINDOW_BINS_LIST)
    get_filename_component(_bin_name "${_bin_file}" NAME)
    if(_bin_name MATCHES "\.(pdb|dll|so(\.[0-9.]+)?)$")
        configure_file("${_bin_file}" "${WINDOW_OUTPUT_DIR}/${_bin_name}" COPYONLY)
    endif()
endforeach()

foreach(_lib_file IN LISTS WINDOW_LIBS_LIST)
    get_filename_component(_lib_name "${_lib_file}" NAME)
    if(_lib_name MATCHES "\.(lib|dylib|a)$")
        configure_file("${_lib_file}" "${WINDOW_OUTPUT_DIR}/${_lib_name}" COPYONLY)
    endif()
endforeach()

file(GLOB_RECURSE WINDOW_SOURCES CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE WINDOW_HEADERS CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.inl")

add_library(Window SHARED ${WINDOW_SOURCES} ${WINDOW_HEADERS})

target_include_directories(Window
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include"
)

if(WINDOW_USE_VULKAN)
    target_link_libraries(Window PRIVATE Vulkan::Vulkan)
endif()

if(WINDOW_LIBS_LIST OR WINDOW_BINS_LIST)
    target_link_directories(Window PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libs")
    target_link_libraries(Window PRIVATE ${WINDOW_LIBS_LIST})
endif()

foreach(_source IN ITEMS ${WINDOW_SOURCES} ${WINDOW_HEADERS})
    get_filename_component(_path "${_source}" PATH)
    file(RELATIVE_PATH _rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_path}")
    string(REPLACE "\\" "/" _group "${_rel}")
    source_group("${_group}" FILES "${_source}")
endforeach()

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
