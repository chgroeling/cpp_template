cmake_minimum_required (VERSION 3.2.0)

#include(cmake/print_target_properties.cmake)

# Project name and a few useful settings. Other commands can pick up the results
project(
  {{project.specs.name}} 
  VERSION {{project.specs.version}}
  DESCRIPTION "{{project.specs.description}}"
  LANGUAGES CXX C)

set (CMAKE_CXX_STANDARD 20)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
{% if 'wxwidgets' in extern%}
  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Cxx extensions(aka -std=gnu++20) needed by wxWidgets compiling on mac
  set(CMAKE_CXX_EXTENSIONS ON)
{% else %}
  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)
{% endif %}

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

{% if 'googletest' in extern%}
  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)
{% endif %}
{% if 'doxygen' in extern %}
  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
{% endif %}
endif()
{% if 'nlohmann_json' in extern %}
# ------------------------------------
# nlohmann json library
# ------------------------------------
add_subdirectory(extern/nlohmann_json EXCLUDE_FROM_ALL)

{% endif %}
{% if 'cxx_opts' in extern %}
# ------------------------------------
# CXXOPTS
# ------------------------------------
add_subdirectory(extern/cxxopts)

{% endif %}
{% if 'fmt' in extern %}
# ------------------------------------
# FMT
# ------------------------------------
add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)

{% endif %}
{% if 'spdlog' in extern%}
# ------------------------------------
# SPDLOG 
# ------------------------------------
set(SPDLOG_FMT_EXTERNAL ON) # Don't use internal fmt. Its provided directly!
add_subdirectory(extern/spdlog EXCLUDE_FROM_ALL)

{% endif %}
{% if 'cxxopts' in extern%}
# ------------------------------------
# CXXOPTS
# ------------------------------------
add_subdirectory(extern/cxxopts EXCLUDE_FROM_ALL)

{% endif %}
{% if 'pcre2' in extern%}
# ------------------------------------
# PCRE
# ------------------------------------
set(PCRE2_BUILD_PCRE2GREP OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
set(PCRE2_BUILD_TESTS OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
set(PCRE2_SUPPORT_UNICODE OFF CACHE BOOL "")
set(PCRE2_SHOW_REPORT OFF CACHE BOOL "")

add_subdirectory(extern/pcre2)
# Add missing include directories that the library can be used by this project
target_include_directories(pcre2-8-static INTERFACE ${PROJECT_BINARY_DIR}/extern/pcre2/ )

{% endif %}
{% if 'wxwidgets' in extern%}
# ------------------------------------
# wxWidgets
# ------------------------------------
add_subdirectory(extern/wxWidgets EXCLUDE_FROM_ALL)

{% endif %}
{% if lib is defined%}
# ------------------------------------
# Library: {{lib.specs.dir}} 
# ------------------------------------
add_subdirectory(src)

{% endif %}
{% if app is defined%}
# ------------------------------------
# Application: {{app.specs.target}} 
# ------------------------------------
add_subdirectory({{app.specs.dir}})

{% endif %}
{% if 'googletest' in extern%}
# Testing only available if this is the main app
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  include(GoogleTest)
  add_subdirectory(tests)
endif()
{% endif %}
