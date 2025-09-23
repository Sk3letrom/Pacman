add_rules("mode.debug", "mode.release")

set_languages("cxx17")

add_requires("sfml >=3.0")

target("Engine")
    set_kind("static")
    add_files(
        "src/entity.cpp",
        "src/objects.cpp",
        "src/sensor.cpp"
    )

    add_packages("sfml")

    add_includedirs("src")


target("Pacman")
    set_kind("binary")
    add_files("src/main.cpp")

    add_deps("Engine")

    add_packages("sfml")

    add_includedirs("src")