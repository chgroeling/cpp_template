add_executable({{APP.TARGET}} main.cpp)

# Link local libraries
target_link_libraries({{APP.TARGET}} PUBLIC {{LIB.DIR}})

# Link extern libraries
{% if EXTERN.fmt%}
target_link_libraries({{APP.TARGET}} PUBLIC fmt)
{% endif %}

{% if EXTERN.spdlog%}
# Link logging library
target_link_libraries({{APP.TARGET}} PUBLIC spdlog)
{% endif %}

{% if EXTERN.wxWidgets%}
# Link GUI library
target_link_libraries({{APP.TARGET}} PUBLIC wx::net wx::core wx::base)
{% endif %}
