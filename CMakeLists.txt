cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("RPG-MAKER")
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static SFML libraries" FORCE)

add_subdirectory(engine)
add_subdirectory(editor)

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

target_link_libraries(${PROJECT_NAME} PUBLIC
    editor
)
