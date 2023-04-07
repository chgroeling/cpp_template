# Create the library 
add_library({{LIB.DIR}}
  {{LIB.DIR}}/{{LIB.FILENAME}}.cpp
)

# Build the library with C++20 
target_compile_features({{LIB.DIR}} PRIVATE cxx_std_20)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories({{LIB.DIR}} PUBLIC ../include)


