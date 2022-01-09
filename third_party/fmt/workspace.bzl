load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def repo():
    http_archive(
        name = "fmt",
        strip_prefix = "fmt-7.1.3",
        urls = ["https://github.com/fmtlib/fmt/releases/download/7.1.3/fmt-7.1.3.zip"],
        sha256 = "5d98c504d0205f912e22449ecdea776b78ce0bb096927334f80781e720084c9f",
        build_file = "@//third_party/fmt:fmt.BUILD",
    )
