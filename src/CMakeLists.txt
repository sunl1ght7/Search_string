add_library(search_engine_lib
    ConverterJSON.cpp
    InvertedIndex.cpp
    SearchServer.cpp
)

target_include_directories(search_engine_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(search_engine_lib
    PUBLIC nlohmann_json::nlohmann_json
)

add_executable(search_engine main.cpp)

target_link_libraries(search_engine
    PRIVATE search_engine_lib
)

if(EXISTS ${CMAKE_SOURCE_DIR}/resources)
    add_custom_command(TARGET search_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:search_engine>/resources
    )
endif()

add_custom_command(TARGET search_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/config.json
    $<TARGET_FILE_DIR:search_engine>/config.json
)

add_custom_command(TARGET search_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/requests.json
    $<TARGET_FILE_DIR:search_engine>/requests.json
)