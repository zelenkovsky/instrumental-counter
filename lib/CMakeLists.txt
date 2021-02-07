add_library (counter counter.cxx counter_private.cxx)

target_include_directories (counter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})