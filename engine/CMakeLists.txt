add_library(engine)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_include_directories(engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
target_sources(engine PUBLIC ${SRC})

target_link_libraries(engine PUBLIC
    SFML::System
    SFML::Window
    SFML::Graphics
    opengl32
)

target_include_directories(engine PUBLIC ${SFML_INCLUDE_DIR})