from jinja2 import Environment, PackageLoader, select_autoescape
from pathlib import Path
import os
import subprocess


project_def = {
    "PROJECT_NAME": "Bitstream",
    "PROJECT_VERSION": "0.1",
    "PROJECT_DESCRIPTION": "Bitstream library",
    "APP": {
        "DIR": "app_bs",  # The project will be generated with one app in the given directory
        "TARGET": "app_bs",  # Thats the name of the target
    },
    "LIB": {  # The project will be generated with one library
        "DIR": "bitstream",  # This is the name of the library directory
        "FILENAME": "bitstream",  # The library directory contains one cpp module with this name
        "CLASS": "BitStream",  # This is the name of the class defined in the generated cpp module
    },
    "GENERATOR": {
        "cleanarchitecture": False,
    },
    "EXTERN": {
        "doxygen": False,
        "googletest": True,
        "cxx_opts": False,
        "fmt": True,
        "spdlog": True,
        "PCRE2": False,
        "wxWidgets": False,
    },
}

def GitInit(repoDir):
    cmd = ["git", "init"]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()

def GitAddSubModule(repoDir, url, path):
    cmd = ["git", "submodule", "add", url, path]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()

def GitInitSubModule(repoDir):
    cmd = ["git", "submodule", "init"]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()

def GitUpdateSubModule(repoDir):
    cmd = ["git", "submodule", "update"]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()

def GitCheckoutSubModule(repoDir, hash):
    cmd = ["git", "checkout", hash]
    p = subprocess.Popen(cmd, cwd=repoDir)
    p.wait()

def create(template_name, filepos):
    template_ = env.get_template(template_name)
    out_template = template_.render(project_def)

    # to save the results
    with open(filepos, "w") as fh:
        fh.write(out_template)


env = Environment(
    loader=PackageLoader("cpp_proj"), trim_blocks=True, lstrip_blocks=True
)

# ----------------------------------------------------------------------------
# SHORT NAMES
# ----------------------------------------------------------------------------

proj_path = "./tmp/"
app_dir = project_def["APP"]["DIR"]
lib_dir = project_def["LIB"]["DIR"]
is_fmt = project_def["EXTERN"]["fmt"]
is_spdlog = project_def["EXTERN"]["spdlog"]
is_wxwidgets = project_def["EXTERN"]["wxWidgets"]
is_googletest = project_def["EXTERN"]["googletest"]
is_cleanarchitecture = project_def["GENERATOR"]["cleanarchitecture"]

# ----------------------------------------------------------------------------
# RENDER TEMPLATES AND WRITE THEM INTO THE STRUCTURE
# ----------------------------------------------------------------------------
FILES_TO_RENDER = [
    ("gitignore", proj_path + ".gitignore"),
    ("CMakeLists.txt", proj_path + "CMakeLists.txt"),
    ("app/CMakeLists.txt", proj_path + "%s/CMakeLists.txt" % (app_dir)),
    ("src/CMakeLists.txt", proj_path + "src/CMakeLists.txt"),
    ("app/main.cpp", proj_path + "%s/main.cpp" % (app_dir)),
    (
        "ycm_extra_conf.py",
        proj_path + ".ycm_extra_conf.py",
    ),
    (
        "src/lib/lib.cpp",
        proj_path + "src/%s/%s.cpp" % (lib_dir, project_def["LIB"]["FILENAME"]),
    ),
    (
        "include/lib/lib.h",
        proj_path + "include/%s/%s.h" % (lib_dir, project_def["LIB"]["FILENAME"]),
    ),
    (
        "tests/CMakeLists.txt",
        proj_path + "tests/CMakeLists.txt",
    ),
]


for from_, to_ in FILES_TO_RENDER:
    to_dir = os.path.dirname(to_)
    Path(to_dir).mkdir(parents=True, exist_ok=True)
    create(from_, to_)

if is_cleanarchitecture:
    CA_TO_RENDER = [
        (
            "src/lib/use_cases/sample_interactor.cpp",
            proj_path + "src/%s/use_cases/sample_interactor.cpp" % (lib_dir),
        ),
        (
            "src/lib/controller/sample_controller.cpp",
            proj_path + "src/%s/controller/sample_controller.cpp" % (lib_dir),
        ),
        (
            "src/lib/presenter/sample_presenter.cpp",
            proj_path + "src/%s/presenter/sample_presenter.cpp" % (lib_dir),
        ),
        (
            "include/lib/entities/sample_interactor_request.h",
            proj_path + "include/%s/entities/sample_interactor_request.h" % (lib_dir),
        ),
        (
            "include/lib/entities/sample_interactor_response.h",
            proj_path + "include/%s/entities/sample_interactor_response.h" % (lib_dir),
        ),
        (
            "include/lib/use_cases/i_sample_interactor_input.h",
            proj_path + "include/%s/use_cases/i_sample_interactor_input.h" % (lib_dir),
        ),
        (
            "include/lib/use_cases/i_sample_interactor_output.h",
            proj_path + "include/%s/use_cases/i_sample_interactor_output.h" % (lib_dir),
        ),
        (
            "include/lib/use_cases/i_sample_repository.h",
            proj_path + "include/%s/use_cases/i_sample_repository.h" % (lib_dir),
        ),
        (
            "include/lib/db/sample_repository.h",
            proj_path + "include/%s/db/sample_repository.h" % (lib_dir),
        ),
        (
            "include/lib/use_cases/sample_interactor.h",
            proj_path + "include/%s/use_cases/sample_interactor.h" % (lib_dir),
        ),
        (
            "include/lib/controller/sample_controller.h",
            proj_path + "include/%s/controller/sample_controller.h" % (lib_dir),
        ),
        (
            "include/lib/presenter/sample_presenter.h",
            proj_path + "include/%s/presenter/sample_presenter.h" % (lib_dir),
        ),
    ]

    for from_, to_ in CA_TO_RENDER:
        to_dir = os.path.dirname(to_)
        Path(to_dir).mkdir(parents=True, exist_ok=True)
        create(from_, to_)


if is_googletest:
    TESTS_TO_RENDER = [
        (
            "tests/test1.cpp",
            proj_path + "tests/test1.cpp",
        ),
        (
            "tests/test2.cpp",
            proj_path + "tests/test2.cpp",
        ),
    ]
    if is_cleanarchitecture:
        TESTS_TO_RENDER += [
            (
                "tests/lib/use_cases/test_sample_interactor.cpp",
                proj_path + "tests/%s/use_cases/test_sample_interactor.cpp" % (lib_dir),
            ),
        ]

    for from_, to_ in TESTS_TO_RENDER:
        to_dir = os.path.dirname(to_)
        Path(to_dir).mkdir(parents=True, exist_ok=True)
        create(from_, to_)

# create extern directory when libraries are selected
if is_fmt or is_spdlog or is_googletest or is_wxwidgets:
    Path(proj_path + "extern").mkdir(parents=True, exist_ok=True)


# ----------------------------------------------------------------------------
# Initialize Git Repositories
# ----------------------------------------------------------------------------
GitInit("./tmp")

if is_fmt:
    GitAddSubModule("./tmp", "https://github.com/fmtlib/fmt.git", "extern/fmt")
    GitCheckoutSubModule("./tmp/extern/fmt", "8.1.1")

if is_spdlog:
    GitAddSubModule("./tmp", "https://github.com/gabime/spdlog.git", "extern/spdlog")
    GitCheckoutSubModule("./tmp/extern/spdlog", "v1.10.0")

if is_wxwidgets:
    GitAddSubModule(
        "./tmp", "https://github.com/wxWidgets/wxWidgets.git", "extern/wxWidgets"
    )
    GitCheckoutSubModule("./tmp/extern/wxWidgets", "v3.2.0")
    GitInitSubModule("./tmp/extern/wxWidgets")
    GitUpdateSubModule("./tmp/extern/wxWidgets")

if is_googletest:
    GitAddSubModule(
        "./tmp", "https://github.com/google/googletest.git", "extern/googletest"
    )
    GitCheckoutSubModule("./tmp/extern/googletest", "release-1.12.1")
