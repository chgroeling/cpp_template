from jinja2 import Environment, PackageLoader, select_autoescape
env = Environment(
    loader=PackageLoader("cpp_proj"),
    autoescape=select_autoescape()
)

print("HELLO world")

template = env.get_template("CMakeLists.txt")

out_template = template.render(PROJECT_NAME="variables", go="here")

print(out_template)

# to save the results
with open("tmp/CMakeLists.txt", "w") as fh:
    fh.write(out_template)
