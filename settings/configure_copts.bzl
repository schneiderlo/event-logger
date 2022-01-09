"""Set compilation flags for the project."""

load(
    "//settings:copts.bzl",
    "CLANG_WARNINGS",
    "GCC_WARNINGS",
    "MSVC_WARNINGS",
)

MSVC_WERROR = ["/WX"]

CLANG_WERROR = ["-Werror"]

MSVC_FLAGS = (
    ["/std:c++20"] +
    MSVC_WARNINGS +
    MSVC_WERROR
)

CLANG_FLAGS = (
    ["-std=c++20"] +
    CLANG_WARNINGS +
    CLANG_WERROR
)

GCC_FLAGS = (
    ["-std=c++20"] +
    GCC_WARNINGS +
    CLANG_WERROR
)

PROJECT_DEFAULT_COPTS = select({
    "//:msvc_compiler": MSVC_FLAGS,
    "//:clang-cl_compiler": MSVC_FLAGS,  # Previously CLANG_CL_FLAGS
    "//:clang_compiler": CLANG_FLAGS,
    "//conditions:default": GCC_WARNINGS,
})

PROJECT_TEST_COPTS = select({
    "//:msvc_compiler": MSVC_FLAGS,
    "//:clang-cl_compiler": MSVC_FLAGS,  # Previously CLANG_CL_FLAGS
    "//:clang_compiler": CLANG_FLAGS,
    "//conditions:default": GCC_FLAGS,
})
