set(APP_SOURCES
  main.cpp
)

add_executable({{APP.TARGET}} ${APP_SOURCES})

# Link local libraries
target_link_libraries({{APP.TARGET}} PUBLIC {{LIB.DIR}})

# Link string format library
{% if EXTERN.fmt%}
target_link_libraries({{APP.TARGET}} PUBLIC fmt)

{% endif %}
{% if EXTERN.spdlog%}
# Link logging library
target_link_libraries({{APP.TARGET}} PUBLIC spdlog)

{% endif %}
{% if EXTERN.cxxopts%}
# Link command line option library
target_link_libraries({{APP.TARGET}} PUBLIC cxxopts)

{% endif %}
{% if EXTERN.wxWidgets%}
# Link GUI library
target_link_libraries({{APP.TARGET}} PUBLIC wx::net wx::core wx::base)
{% endif %}
