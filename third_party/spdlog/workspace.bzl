"""Loads the cpuinfo library, used by XNNPACK."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def repo():
    http_archive(
        name = "spdlog",
        strip_prefix = "spdlog-1.8.2",
        urls = ["https://github.com/gabime/spdlog/archive/v1.8.2.tar.gz"],
        sha256 = "e20e6bd8f57e866eaf25a5417f0a38a116e537f1a77ac7b5409ca2b180cec0d5",
        build_file = "@//third_party/spdlog:spdlog.BUILD",
    )
