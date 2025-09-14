add_executable(search_engine_tests
    test_main.cpp
    test_invertedindex.cpp
    test_searchserver.cpp
)

target_include_directories(search_engine_tests
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(search_engine_tests
    PRIVATE search_engine_lib
    PRIVATE gtest_main
    PRIVATE nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(search_engine_tests)

if(EXISTS ${CMAKE_SOURCE_DIR}/resources)
    add_custom_command(TARGET search_engine_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:search_engine_tests>/resources
    )
endif()

add_custom_command(TARGET search_engine_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/config.json
    $<TARGET_FILE_DIR:search_engine_tests>/config.json
)

add_custom_command(TARGET search_engine_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/requests.json
    $<TARGET_FILE_DIR:search_engine_tests>/requests.json
)