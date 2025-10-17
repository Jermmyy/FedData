cmake_minimum_required(VERSION 3.16)
project(fed_terminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# FetchContent for CPR (HTTP library)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.4
)
set(CPR_USE_SYSTEM_CURL OFF CACHE BOOL "Use system CURL" FORCE)
FetchContent_MakeAvailable(cpr)

# FetchContent for nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(fed_terminal src/main.cpp)

# Link libraries
target_link_libraries(fed_terminal PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
