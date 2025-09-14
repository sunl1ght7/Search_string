cmake_minimum_required(VERSION 4.0.2..4.0.2)
project(SearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests AND IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
else()
    message(WARNING "Tests directory not found - skipping tests")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/bin/config.json COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/requests.json ${CMAKE_BINARY_DIR}/bin/requests.json COPYONLY)

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
            add_link_options(-lstdc++fs)
        endif()
    endif()
endif()