package(default_visibility = ["//visibility:public"])

config_setting(
    name = "clang_compiler",
    flag_values = {
        "@bazel_tools//tools/cpp:compiler": "clang",
    },
    visibility = [":__subpackages__"],
)

config_setting(
    name = "msvc_compiler",
    flag_values = {
        "@bazel_tools//tools/cpp:compiler": "msvc-cl",
    },
    visibility = [":__subpackages__"],
)

config_setting(
    name = "clang-cl_compiler",
    flag_values = {
        "@bazel_tools//tools/cpp:compiler": "clang-cl",
    },
    visibility = [":__subpackages__"],
)
