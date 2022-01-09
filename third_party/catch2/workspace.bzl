load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def repo():
    http_archive(
        name = "catch2",
        strip_prefix = "Catch2-2.13.4",
        urls = ["https://github.com/catchorg/Catch2/archive/v2.13.4.tar.gz"],
        sha256 = "e7eb70b3d0ac2ed7dcf14563ad808740c29e628edde99e973adad373a2b5e4df",
    )
