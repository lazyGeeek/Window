set(WINDOW_PROJECT "Window")

if(WINDOW_REBUILD_THIRDPARTY)
    execute_process(COMMAND python3 "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/build_dependencies.py")
endif()

file(
    GLOB_RECURSE WINDOW_BINS_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/bins/*.*"
)

file(
    GLOB_RECURSE WINDOW_LIBS_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libs/*.*"
)

foreach (BIN_FILE ${WINDOW_BINS_LIST})
    file(COPY ${BIN_FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach ()

foreach (LIB_FILE ${WINDOW_LIBS_LIST})
    file(COPY ${LIB_FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach ()

file(
    GLOB_RECURSE WINDOW_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.h*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/window/*.inl"
)

add_library(${WINDOW_PROJECT} SHARED ${WINDOW_CODE_LIST})

target_compile_features(${WINDOW_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${WINDOW_PROJECT} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
)
target_link_libraries(${WINDOW_PROJECT} ${WINDOW_BINS_LIST})

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
