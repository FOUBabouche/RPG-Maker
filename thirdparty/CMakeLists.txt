add_library(imgui STATIC)

file(GLOB IMGUI_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp"
)
target_sources(imgui PRIVATE ${IMGUI_SRC})

add_subdirectory(imgui-sfml-3.0)

target_include_directories(imgui PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML-3.0.2/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml-3.0"
)


