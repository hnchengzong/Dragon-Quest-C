set_project("Dragon-Quest-C")
set_version("1.0.0")

set_languages("c11")
set_toolchains("clang")

includes("@builtin/xpack")
add_rules("mode.debug", "mode.release")


target("Dragon-Quest-C")
    set_kind("binary")
    add_files("src/*.c")
    add_includedirs("src/include")
    set_warnings("everything", "error")
    set_targetdir("build")

    if is_mode("debug") then
        set_targetdir("build/debug")
        set_symbols("debug")
        set_optimize("none")
        add_defines("DEBUG")
    end

    if is_mode("release") then
        set_targetdir("build/release")
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
        set_warnings("none")
        add_defines("RELEASE")
    end

xpack("Dragon-Quest-C")
    set_formats("zip", "targz", "nsis")
    set_title("Dragon-Quest-C")
    set_author("hnchengzong")
    set_homepage("https://github.com/hnchengzong/Dragon-Quest-C")
    set_description("Dragon-Quest-C program")
    add_targets("Dragon-Quest-C")
