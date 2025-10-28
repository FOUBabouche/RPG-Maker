# CMakeList.txt : projet CMake pour RPG Maker, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.10)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SFML as static libraries" FORCE)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-docking/imgui")

project("RPG_Maker")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SFML-3.0.2")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-docking")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-sfml-3.0")


add_executable(${CMAKE_PROJECT_NAME})

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/rpg_maker/src/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/rpg_maker/include/")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  sfml-system 
  sfml-window 
  sfml-graphics
	imgui
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
