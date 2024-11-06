cmake_minimum_required(VERSION 3.22)
project(mastermind-solver)

enable_testing()
add_subdirectory(mastermind-solver-cpp)

IF (DEFINED EMSCRIPTEN)
    add_custom_target(mastermind_npm
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE_DIR:mastermind>/mastermind.js
            $<TARGET_FILE_DIR:mastermind>/mastermind.wasm
            ${CMAKE_CURRENT_SOURCE_DIR}/mastermind-solver-js
    )
    add_dependencies(mastermind_npm mastermind)

    add_test(NAME TestWasm
            COMMAND npm test
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mastermind-solver-js
    )
endif ()