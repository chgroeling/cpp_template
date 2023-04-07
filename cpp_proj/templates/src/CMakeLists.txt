# Create the library 
add_library({{LIB.DIR}}
  {{LIB.DIR}}/{{LIB.FILENAME}}.cpp
)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories({{LIB.DIR}} PUBLIC ../include)


