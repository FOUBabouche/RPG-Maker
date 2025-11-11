find_package(imgui REQUIRED)
find_package(ImGui-SFML REQUIRED)

add_library(editor)

target_include_directories(editor PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
target_sources(editor PUBLIC ${SRC})

target_link_libraries(editor PUBLIC
    imgui::imgui
    ImGui-SFML::ImGui-SFML
    engine
)