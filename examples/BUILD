load(
    "//settings:configure_copts.bzl",
    "PROJECT_DEFAULT_COPTS",
)

package(default_visibility = ["//visibility:public"])


cc_test(
    name = "example-1",
    srcs = [
        "example_1.cc",
    ],
    copts = PROJECT_DEFAULT_COPTS,
    deps = [
        "//event-logger:event-logger"
    ],
)
