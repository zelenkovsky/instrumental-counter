add_executable (countertest countertest.cxx)

target_link_libraries (countertest LINK_PUBLIC counter)

enable_testing()

add_test(counter countertest)