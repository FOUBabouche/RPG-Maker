cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("RPG-MAKER")
set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static SFML libraries" FORCE)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML-3.0.2/lib/cmake/SFML")
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(engine)

add_executable(${PROJECT_NAME})

# Sources du projet
file(GLOB SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/rpg_maker/src/*.cpp"
)
target_sources(${PROJECT_NAME} PUBLIC ${SRC})

# Includes du projet
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/rpg_maker/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    engine
    ImGui-SFML::ImGui-SFML
    SFML::System
    SFML::Window
    SFML::Graphics
    opengl32
)
