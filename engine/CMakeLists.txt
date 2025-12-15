add_library(engine)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

include(FetchContent)

FetchContent_Declare(Scripting_API                           # name of the content
  GIT_REPOSITORY https://github.com/Zero-Foo/ScriptingAPI-SFML.git  # the repository
  GIT_TAG v1.0
)

FetchContent_MakeAvailable(Scripting_API)

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
    Scripting-API
)

target_include_directories(engine PUBLIC ${SFML_INCLUDE_DIR})