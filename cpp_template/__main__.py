from jinja2 import Environment, PackageLoader, select_autoescape
from pathlib import Path

project_def = {
    "PROJECT_NAME": "cpp_template",
    "PROJECT_VERSION": "0.3",
    "PROJECT_DESCRIPTION": "Test Project",
    "EXTERN": {
        "doxygen": False,
        "googletest" : False,
        "cxx_opts": False,
        "fmt": False,
        "spdlog": False,
        "PCRE2": False,
    },
}

env = Environment(
    loader=PackageLoader("cpp_proj"), trim_blocks=True, lstrip_blocks=True
)


def create(template_name, filepos):
    template_ = env.get_template(template_name)
    out_template = template_.render(project_def)

    # to save the results
    with open(filepos, "w") as fh:
        fh.write(out_template)


# Create directory structure
Path("./tmp/app/").mkdir(parents=True, exist_ok=True)
Path("./tmp/src/").mkdir(parents=True, exist_ok=True)
Path("./tmp/include/").mkdir(parents=True, exist_ok=True)


create("CMakeLists.txt", "tmp/CMakeLists.txt")
create("app/CMakeLists.txt", "tmp/app/CMakeLists.txt")
create("app/main.cpp", "tmp/app/main.cpp")
