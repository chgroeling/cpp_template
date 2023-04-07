from jinja2 import Environment, PackageLoader, select_autoescape
from pathlib import Path
import os
import subprocess


def GitInit(repoDir):
    cmd = ["git", "init"]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()


def GitAddSubModule(repoDir, url, path):
    cmd = ["git", "submodule", "add", url, path]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()


def GitCheckoutSubModule(repoDir, hash):
    cmd = ["git", "checkout", hash]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()


project_def = {
    "PROJECT_NAME": "test_project",
    "PROJECT_VERSION": "0.3",
    "PROJECT_DESCRIPTION": "Test Project",
    "APP": {
        "DIR": "myapp",  # The project will be generated with one app in the given directory
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
        "fmt": True,
        "spdlog": True,
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

proj_path = "./tmp/"
app_dir = project_def["APP"]["DIR"]
is_fmt = project_def["EXTERN"]["fmt"]
is_spdlog = project_def["EXTERN"]["spdlog"]

# Create directory structure
Path(proj_path + "%s/" % (app_dir)).mkdir(parents=True, exist_ok=True)
Path(proj_path + "src/").mkdir(parents=True, exist_ok=True)
Path(proj_path + "src/%s/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)
Path(proj_path + "include/").mkdir(parents=True, exist_ok=True)
Path(proj_path + "include/%s/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)
Path(proj_path + "include/%s/entities/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)
Path(proj_path + "include/%s/use_cases/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)
Path(proj_path + "include/%s/presenter/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)
Path(proj_path + "include/%s/controller/" % (project_def["LIB"]["DIR"])).mkdir(
    parents=True, exist_ok=True
)


if is_fmt or is_spdlog:
    Path(proj_path + "extern").mkdir(parents=True, exist_ok=True)

# ----------------------------------------------------------------------------
# RENDER TEMPLATES AND WRITE THEM INTO THE STRUCTURE
# ----------------------------------------------------------------------------
create("gitignore", proj_path + ".gitignore")
create("CMakeLists.txt", proj_path + "CMakeLists.txt")
create("app/CMakeLists.txt", proj_path + "%s/CMakeLists.txt" % (app_dir))
create("src/CMakeLists.txt", proj_path + "src/CMakeLists.txt")
create("app/main.cpp", proj_path + "%s/main.cpp" % (app_dir))
create(
    "src/lib/lib.cpp",
    proj_path
    + "src/%s/%s.cpp" % (project_def["LIB"]["DIR"], project_def["LIB"]["FILENAME"]),
)
create(
    "include/lib/lib.h",
    proj_path
    + "include/%s/%s.h" % (project_def["LIB"]["DIR"], project_def["LIB"]["FILENAME"]),
)

create(
    "include/lib/entities/sample_interactor_request.h",
    proj_path
    + "include/%s/entities/sample_interactor_request.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/entities/sample_interactor_response.h",
    proj_path
    + "include/%s/entities/sample_interactor_response.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/use_cases/i_sample_interactor_input.h",
    proj_path
    + "include/%s/use_cases/i_sample_interactor_input.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/use_cases/i_sample_interactor_output.h",
    proj_path
    + "include/%s/use_cases/i_sample_interactor_output.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/use_cases/sample_interactor.h",
    proj_path
    + "include/%s/use_cases/sample_interactor.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/controller/sample_controller.h",
    proj_path
    + "include/%s/controller/sample_controller.h" % (project_def["LIB"]["DIR"]),
)

create(
    "include/lib/presenter/sample_presenter.h",
    proj_path
    + "include/%s/presenter/sample_presenter.h" % (project_def["LIB"]["DIR"]),
)
# ----------------------------------------------------------------------------
# Initialize Git Repositories
# ----------------------------------------------------------------------------
GitInit("./tmp")

if is_fmt:
    GitAddSubModule("./tmp", "https://github.com/fmtlib/fmt.git", "extern/fmt")
    GitCheckoutSubModule("./tmp/extern/fmt", "b6f4ceae")

if is_spdlog:
    GitAddSubModule("./tmp", "https://github.com/gabime/spdlog.git", "extern/spdlog")
    GitCheckoutSubModule("./tmp/extern/spdlog", "76fb40d9")
