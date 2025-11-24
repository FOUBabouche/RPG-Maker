find_package(imgui REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

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
    nlohmann_json::nlohmann_json
    imgui::imgui
    ImGui-SFML::ImGui-SFML
    engine
)