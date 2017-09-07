add_executable(difftest diff.c
                        diff_driver.c
                        input.c)

add_executable(polytest polynomial.c
                        poly_driver.c)

add_executable(coneq construct_eqn.c
                        input.c
                        diff.c
                        polynomial.c)

add_executable(finter finterpolation.c
                        input.c
                        diff.c
                        polynomial.c)

add_executable(binter binterpolation.c
                        input.c
                        diff.c
                        polynomial.c)

add_executable(linter lagrange.c
                        input.c
                        polynomial.c
                        fraction.c)
