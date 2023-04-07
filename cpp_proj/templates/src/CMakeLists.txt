# Create the library 
add_library(lib
  lib/lib.cpp
)

# Build the library with C++20 
target_compile_features(lib PRIVATE cxx_std_20)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(lib PUBLIC ../include)


