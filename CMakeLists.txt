set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)

add_library(input STATIC input.c)
add_library(diff STATIC diff.c)
add_library(utility STATIC utility.c)
add_library(polynomial STATIC polynomial.c)
target_link_libraries(polynomial utility)
add_library(fraction STATIC fraction.c)

add_executable(difftest diff_driver.c)
target_link_libraries(difftest diff
                                input)

add_executable(polytest poly_driver.c)
target_link_libraries(polytest polynomial)

add_executable(coneq construct_eqn.c)
target_link_libraries(coneq input
                            diff
                            polynomial)

add_executable(finter finterpolation.c)
target_link_libraries(finter input
                             diff
                             polynomial)

add_executable(binter binterpolation.c)
target_link_libraries(binter input
                             diff
                             polynomial)

add_executable(linter lagrange.c)
target_link_libraries(linter input
                             polynomial
                             fraction)

add_executable(gausselimination gausselimination.c)
target_link_libraries(gausselimination m)

add_executable(gaussjordan gaussjordan.c)
target_link_libraries(gaussjordan m)

add_executable(gaussseidel gaussseidel.c)
target_link_libraries(gaussseidel m)

add_executable(gaussjacobi gaussjacobi.c)
target_link_libraries(gaussjacobi m)
