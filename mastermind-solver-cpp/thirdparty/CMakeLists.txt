#===============================================================================
# kissat
#===============================================================================
include(FetchContent)
FetchContent_Declare(kissat
        URL https://github.com/arminbiere/kissat/archive/refs/tags/rel-4.0.1.tar.gz
)
if(NOT kissat_POPULATED)
    FetchContent_MakeAvailable(kissat)
endif()

add_library(kissat
        ${kissat_SOURCE_DIR}/src/allocate.c
        ${kissat_SOURCE_DIR}/src/analyze.c
        ${kissat_SOURCE_DIR}/src/ands.c
#        ${kissat_SOURCE_DIR}/src/application.c
        ${kissat_SOURCE_DIR}/src/arena.c
        ${kissat_SOURCE_DIR}/src/assign.c
        ${kissat_SOURCE_DIR}/src/averages.c
        ${kissat_SOURCE_DIR}/src/backbone.c
        ${kissat_SOURCE_DIR}/src/backtrack.c
#        ${kissat_SOURCE_DIR}/src/build.c
        ${kissat_SOURCE_DIR}/src/bump.c
        ${kissat_SOURCE_DIR}/src/check.c
        ${kissat_SOURCE_DIR}/src/classify.c
        ${kissat_SOURCE_DIR}/src/clause.c
        ${kissat_SOURCE_DIR}/src/collect.c
        ${kissat_SOURCE_DIR}/src/colors.c
        ${kissat_SOURCE_DIR}/src/compact.c
        ${kissat_SOURCE_DIR}/src/config.c
        ${kissat_SOURCE_DIR}/src/configure
        ${kissat_SOURCE_DIR}/src/congruence.c
        ${kissat_SOURCE_DIR}/src/decide.c
        ${kissat_SOURCE_DIR}/src/deduce.c
        ${kissat_SOURCE_DIR}/src/definition.c
        ${kissat_SOURCE_DIR}/src/dense.c
        ${kissat_SOURCE_DIR}/src/dump.c
        ${kissat_SOURCE_DIR}/src/eliminate.c
        ${kissat_SOURCE_DIR}/src/equivalences.c
        ${kissat_SOURCE_DIR}/src/error.c
        ${kissat_SOURCE_DIR}/src/extend.c
        ${kissat_SOURCE_DIR}/src/factor.c
        ${kissat_SOURCE_DIR}/src/fastel.c
        ${kissat_SOURCE_DIR}/src/file.c
        ${kissat_SOURCE_DIR}/src/flags.c
        ${kissat_SOURCE_DIR}/src/format.c
        ${kissat_SOURCE_DIR}/src/forward.c
        ${kissat_SOURCE_DIR}/src/gates.c
        ${kissat_SOURCE_DIR}/src/handle.c
        ${kissat_SOURCE_DIR}/src/heap.c
        ${kissat_SOURCE_DIR}/src/ifthenelse.c
        ${kissat_SOURCE_DIR}/src/import.c
        ${kissat_SOURCE_DIR}/src/internal.c
        ${kissat_SOURCE_DIR}/src/kimits.c
        ${kissat_SOURCE_DIR}/src/kitten.c
        ${kissat_SOURCE_DIR}/src/krite.c
        ${kissat_SOURCE_DIR}/src/learn.c
        ${kissat_SOURCE_DIR}/src/logging.c
        ${kissat_SOURCE_DIR}/src/lucky.c
#        ${kissat_SOURCE_DIR}/src/main.c
        ${kissat_SOURCE_DIR}/src/minimize.c
        ${kissat_SOURCE_DIR}/src/mode.c
        ${kissat_SOURCE_DIR}/src/options.c
#        ${kissat_SOURCE_DIR}/src/parse.c
        ${kissat_SOURCE_DIR}/src/phases.c
        ${kissat_SOURCE_DIR}/src/preprocess.c
        ${kissat_SOURCE_DIR}/src/print.c
        ${kissat_SOURCE_DIR}/src/probe.c
        ${kissat_SOURCE_DIR}/src/profile.c
        ${kissat_SOURCE_DIR}/src/promote.c
        ${kissat_SOURCE_DIR}/src/proof.c
        ${kissat_SOURCE_DIR}/src/propbeyond.c
        ${kissat_SOURCE_DIR}/src/propdense.c
        ${kissat_SOURCE_DIR}/src/propinitially.c
        ${kissat_SOURCE_DIR}/src/proprobe.c
        ${kissat_SOURCE_DIR}/src/propsearch.c
        ${kissat_SOURCE_DIR}/src/queue.c
        ${kissat_SOURCE_DIR}/src/reduce.c
        ${kissat_SOURCE_DIR}/src/reluctant.c
        ${kissat_SOURCE_DIR}/src/reorder.c
        ${kissat_SOURCE_DIR}/src/rephase.c
        ${kissat_SOURCE_DIR}/src/report.c
        ${kissat_SOURCE_DIR}/src/resize.c
        ${kissat_SOURCE_DIR}/src/resolve.c
        ${kissat_SOURCE_DIR}/src/resources.c
        ${kissat_SOURCE_DIR}/src/restart.c
        ${kissat_SOURCE_DIR}/src/search.c
        ${kissat_SOURCE_DIR}/src/shrink.c
        ${kissat_SOURCE_DIR}/src/smooth.c
        ${kissat_SOURCE_DIR}/src/sort.c
        ${kissat_SOURCE_DIR}/src/stack.c
        ${kissat_SOURCE_DIR}/src/statistics.c
        ${kissat_SOURCE_DIR}/src/strengthen.c
        ${kissat_SOURCE_DIR}/src/substitute.c
        ${kissat_SOURCE_DIR}/src/sweep.c
        ${kissat_SOURCE_DIR}/src/terminate.c
        ${kissat_SOURCE_DIR}/src/tiers.c
        ${kissat_SOURCE_DIR}/src/trail.c
        ${kissat_SOURCE_DIR}/src/transitive.c
        ${kissat_SOURCE_DIR}/src/utilities.c
        ${kissat_SOURCE_DIR}/src/vector.c
        ${kissat_SOURCE_DIR}/src/vivify.c
        ${kissat_SOURCE_DIR}/src/walk.c
        ${kissat_SOURCE_DIR}/src/warmup.c
        ${kissat_SOURCE_DIR}/src/watch.c
        ${kissat_SOURCE_DIR}/src/weaken.c
#        ${kissat_SOURCE_DIR}/src/witness.c
)
target_compile_options(kissat PRIVATE
    -DNOPTIONS
    -DQUIET
    -O3
)
target_include_directories(kissat PUBLIC ${kissat_SOURCE_DIR}/src)

#===============================================================================
# googletest
#===============================================================================
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz)
FetchContent_MakeAvailable(googletest)
