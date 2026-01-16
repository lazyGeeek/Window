cmake_minimum_required(VERSION 3.18)

set(WINDOW_TESTS "WindowTests")

project(${WINDOW_TESTS} CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin_tests/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE  
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()


file(
    GLOB_RECURSE WINDOW_TESTS_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c*"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h*"
    )
    
add_executable(${WINDOW_TESTS} ${WINDOW_TESTS_CODE_LIST})
    
target_link_directories(${WINDOW_TESTS} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_GENERATOR_PLATFORM})
target_link_libraries(${WINDOW_TESTS} GTest::gtest_main GTest::gmock Window)

target_include_directories(${WINDOW_TESTS} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/include
)

include(GoogleTest)
gtest_discover_tests(${WINDOW_TESTS})

# Enable testing
enable_testing()
add_test(NAME ${WINDOW_TESTS} COMMAND ${WINDOW_TESTS})
