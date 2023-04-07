# Create the library 
add_library({{LIB.DIR}}
  {{LIB.DIR}}/{{LIB.FILENAME}}.cpp
  {{LIB.DIR}}/use_cases/sample_interactor.cpp
  {{LIB.DIR}}/controller/sample_controller.cpp
)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories({{LIB.DIR}} PUBLIC ../include)

# Link extern libraries
{% if EXTERN.fmt%}
target_link_libraries({{LIB.DIR}} PUBLIC fmt)
{% endif %}

{% if EXTERN.spdlog%}
target_link_libraries({{LIB.DIR}} PUBLIC spdlog)
{% endif %}

