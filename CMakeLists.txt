set(WINDOW_PROJECT "Window")

if(WINDOW_USE_VULKAN)
    add_compile_definitions(WINDOW_USE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

file(
    GLOB_RECURSE WINDOW_BINS_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bins/*.*"
)

file(
    GLOB_RECURSE WINDOW_LIBS_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libs/*.*"
)

foreach (BIN_FILE ${UI_BINS_LIST})
    get_filename_component(BIN_NAME "${BIN_FILE}" NAME)
    file(COPY_FILE ${BIN_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${BIN_NAME} ONLY_IF_DIFFERENT)
endforeach()

foreach (LIB_FILE ${UI_LIBS_LIST})
    get_filename_component(LIB_NAME "${LIB_FILE}" NAME)
    file(COPY_FILE ${LIB_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${LIB_NAME} ONLY_IF_DIFFERENT)
endforeach()

file(
    GLOB_RECURSE WINDOW_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.h*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.inl"
)

add_library(${WINDOW_PROJECT} SHARED ${WINDOW_CODE_LIST})

target_compile_features(${WINDOW_PROJECT} PRIVATE cxx_std_20)

if(WINDOW_USE_VULKAN)
    target_link_libraries(${WINDOW_PROJECT} ${WINDOW_BINS_LIST} ${Vulkan_LIBRARIES})
    target_include_directories(${WINDOW_PROJECT} PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
        ${Vulkan_INCLUDE_DIRS})
else()
    target_link_libraries(${WINDOW_PROJECT} ${WINDOW_BINS_LIST})
    target_include_directories(${WINDOW_PROJECT} PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include)
endif()

foreach(CODE_FILE IN ITEMS ${WINDOW_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/window" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()
