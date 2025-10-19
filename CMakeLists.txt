cmake_minimum_required(VERSION 3.17)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
project(fed_terminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CPR_USE_SYSTEM_CURL OFF CACHE BOOL "" FORCE)
set(CPR_USE_SYSTEM_ZLIB OFF CACHE BOOL "" FORCE)
set(CPR_FORCE_OPENSSL_BACKEND OFF CACHE BOOL "" FORCE)
set(CPR_FORCE_WINSSL_BACKEND ON CACHE BOOL "" FORCE) 
set(CURL_STATICLIB ON CACHE BOOL "" FORCE)

include(FetchContent)

# FetchContent for CPR
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
)
FetchContent_MakeAvailable(cpr)

# FetchContent for nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

add_executable(fed_terminal WIN32
src/main.cpp 
src/api/sofr_client.cpp 
src/panels/sofr_panel.hpp 
src/panels/sofr_panel.cpp
)

set_target_properties(fed_terminal PROPERTIES
    WIN32_EXECUTABLE ON
)

target_include_directories(fed_terminal PRIVATE src)

# Link libraries
target_link_libraries(fed_terminal PRIVATE 
cpr::cpr 
nlohmann_json::nlohmann_json
imgui::imgui
implot::implot
d3d11
dxgi
d3dcompiler
)