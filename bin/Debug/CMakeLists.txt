cmake_minimum_required(VERSION 3.15)
project(objects)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Project/export/dlls")
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)


add_library(${LIB_NAME} SHARED 
    "${CMAKE_CURRENT_SOURCE_DIR}/Project/assets/Scripts/${LIB_NAME}.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Project/export/script/${LIB_NAME}_export.cpp"
)

target_include_directories(${LIB_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Project/assets/Scripts/"
    "${CMAKE_CURRENT_SOURCE_DIR}/Project/export/script"
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/include"
)

target_link_libraries(${LIB_NAME} PUBLIC
    SFML::System
    SFML::Window
    SFML::Graphics
    opengl32
    engine
)