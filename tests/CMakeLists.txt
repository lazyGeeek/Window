include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(WINDOW_USE_VULKAN)
    add_compile_definitions(WINDOW_USE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

string(TOLOWER "${CMAKE_SYSTEM_NAME}" WINDOW_OS)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" WINDOW_ARCH)

set(WINDOW_TESTS_OUTPUT "${CMAKE_SOURCE_DIR}/bin/${WINDOW_ARCH}/${WINDOW_OS}/Tests")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WINDOW_TESTS_OUTPUT}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${WINDOW_TESTS_OUTPUT}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${WINDOW_TESTS_OUTPUT}")

file(GLOB_RECURSE WINDOW_TEST_SOURCES CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(window_tests ${WINDOW_TEST_SOURCES})

if(WINDOW_USE_VULKAN)
    target_link_libraries(window_tests PRIVATE Vulkan::Vulkan)
endif()

target_link_libraries(window_tests PRIVATE GTest::gtest_main Window)

target_include_directories(window_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/support"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/include"
)

add_custom_command(TARGET window_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:Window>"
        "$<TARGET_FILE_DIR:window_tests>"
    COMMENT "Copying Window runtime library to Tests output"
)

if(EXISTS "${CMAKE_SOURCE_DIR}/thirdparty/bins")
    add_custom_command(TARGET window_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/thirdparty/bins"
            "$<TARGET_FILE_DIR:window_tests>"
        COMMENT "Copying thirdparty runtime libraries to Tests output"
    )
endif()

include(GoogleTest)
gtest_discover_tests(window_tests WORKING_DIRECTORY "${WINDOW_TESTS_OUTPUT}")
