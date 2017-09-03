add_executable(difftest diff.c
                        diff_driver.c)

add_executable(polytest polynomial.c
                        poly_driver.c)

add_executable(coneq construct_eqn.c
                        diff.c
                        polynomial.c)
