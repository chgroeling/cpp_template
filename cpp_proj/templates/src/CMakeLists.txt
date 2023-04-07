# Create the library 
set ({{lib.specs.dir|upper}}_SOURCES 
  {{lib.specs.dir}}/{{lib.specs.filename}}.cpp
{% if 'clean_architecture' in lib%}
  {{lib.specs.dir}}/use_cases/sample_interactor.cpp
  {{lib.specs.dir}}/controller/sample_controller.cpp
  {{lib.specs.dir}}/presenter/sample_presenter.cpp
{% endif %}
)

add_library({{lib.specs.dir}} ${{"{"}}{{lib.specs.dir|upper}}_SOURCES})

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories({{lib.specs.dir}} PUBLIC ../include)

# Link extern libraries
{% if 'fmt' in extern%}
target_link_libraries({{lib.specs.dir}} PUBLIC fmt)

{% endif %}
{% if 'spdlog' in extern%}
target_link_libraries({{lib.specs.dir}} PUBLIC spdlog)

{% endif %}
{% if 'nlohmann_json' in extern%}
# Link GUI library
target_link_libraries({{lib.specs.dir}} PUBLIC nlohmann_json)
{% endif %}

