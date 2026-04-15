set_project("Dragon-Quest-C")
set_version("1.0.0")

set_languages("c11")
set_toolchains("clang")


add_rules("mode.debug", "mode.release")


target("./Dragon-Quest-C")
    set_kind("binary")
    add_files("src/*.c")
    add_includedirs("src/include")
    set_warnings("all", "extra", "error")
    set_targetdir("bin")

    if is_mode("debug") then
        set_targetdir("bin/debug")
        set_symbols("debug")
        set_optimize("none")
        set_warnings("all")
        add_defines("DEBUG")
    end

    if is_mode("release") then
        set_targetdir("bin/release")
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
        set_warnings("none")
    end