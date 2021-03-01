add_executable (countertest countertest.cxx)

target_link_libraries (countertest LINK_PUBLIC counter)

add_test(counter-test-1 countertest 1)
add_test(counter-test-2 countertest 2)
add_test(counter-test-3 countertest 3)
add_test(counter-test-4 countertest 4)
add_test(counter-test-5 countertest 5)
add_test(counter-test-6 countertest 6)
add_test(counter-test-7 countertest 7)
