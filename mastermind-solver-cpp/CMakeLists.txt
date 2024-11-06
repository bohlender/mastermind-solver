project(mastermind_solver_cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
)

add_subdirectory(thirdparty)

set(MASTERMIND_SOURCE
        src/core.cpp
        src/bruteforce.cpp
        src/sat.cpp
        src/api.cpp
)

if (DEFINED EMSCRIPTEN)
    add_executable(mastermind ${MASTERMIND_SOURCE})
    target_compile_options(mastermind PRIVATE -Os)
    target_link_options(mastermind PRIVATE
            -sEXPORTED_FUNCTIONS=_malloc,_free,_Solver_ctor,_Solver_dtor,_add_interaction,_solve
#            -sENVIRONMENT=web
            -sMODULARIZE=1
#            -sEXPORT_ES6=1
#            -sEXPORT_NAME=loadWasm
            -sALLOW_MEMORY_GROWTH=1
            --no-entry
            -flto
    )
else ()
    add_library(mastermind ${MASTERMIND_SOURCE})
endif ()
target_include_directories(mastermind PUBLIC src)
target_link_libraries(mastermind PRIVATE kissat)

if (NOT DEFINED EMSCRIPTEN)
    add_executable(mastermind_test
            test/api_test.cpp
            test/core_test.cpp
            test/bruteforce_test.cpp
            test/sat_test.cpp
    )
    target_link_libraries(mastermind_test mastermind gtest_main)
    include(GoogleTest)
    gtest_discover_tests(mastermind_test)
endif ()