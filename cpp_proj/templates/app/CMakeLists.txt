add_executable({{APP.TARGET}} main.cpp)

target_compile_features({{APP.TARGET}} PRIVATE cxx_std_20)

target_link_libraries({{APP.TARGET}} PUBLIC {{LIB.DIR}})
