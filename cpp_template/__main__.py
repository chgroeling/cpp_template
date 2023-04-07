from jinja2 import Environment, PackageLoader, select_autoescape
from pathlib import Path
import os
import subprocess


def GitInit(repoDir):
    cmd = ["git", "init"]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()


project_def = {
    "PROJECT_NAME": "cpp_template",
    "PROJECT_VERSION": "0.3",
    "PROJECT_DESCRIPTION": "Test Project",
    "APP": {
        "DIR": "myapp",    # The project will be generated with one app in the given directory
        "TARGET": "appl",  # Thats the name of the target
    },  
    "LIB": {  # The project will be generated with one library
        "DIR": "mylib",  # This is the name of the library directory
        "FILENAME": "libary",  # The library directory contains one cpp module with this name
        "CLASS": "MyClass",  # This is the name of the class defined in the generated cpp module
    },
    "EXTERN": {
        "doxygen": False,
        "googletest": False,
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


# ----------------------------------------------------------------------------
# CREATE DIRECTORY STRUCTURE
# ----------------------------------------------------------------------------

app_dir = project_def["APP"]["DIR"]
# Create directory structure
Path("./tmp/%s/" % (app_dir)).mkdir(parents=True, exist_ok=True)
Path("./tmp/src/").mkdir(parents=True, exist_ok=True)
Path("./tmp/src/%s/" % (project_def["LIB"]["DIR"])).mkdir(parents=True, exist_ok=True)
Path("./tmp/include/").mkdir(parents=True, exist_ok=True)
Path("./tmp/include/%s/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)

# ----------------------------------------------------------------------------
# RENDER TEMPLATES AND WRITE THEM INTO THE STRUCTURE
# ----------------------------------------------------------------------------
create("gitignore", "tmp/.gitignore")
create("CMakeLists.txt", "tmp/CMakeLists.txt")
create("app/CMakeLists.txt", "tmp/%s/CMakeLists.txt" % (app_dir))
create("src/CMakeLists.txt", "tmp/src/CMakeLists.txt")
create("app/main.cpp", "tmp/%s/main.cpp" % (app_dir))
create(
    "src/lib/lib.cpp",
    "tmp/src/%s/%s.cpp" % (project_def["LIB"]["DIR"], project_def["LIB"]["FILENAME"]),
)
create(
    "include/lib/lib.h",
    "tmp/include/%s/%s.h" % (project_def["LIB"]["DIR"], project_def["LIB"]["FILENAME"]),
)

# ----------------------------------------------------------------------------
# Initialize Git Repositories
# ----------------------------------------------------------------------------
GitInit("./tmp")
