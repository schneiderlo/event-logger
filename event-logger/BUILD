load(
    "//settings:configure_copts.bzl",
    "PROJECT_DEFAULT_COPTS",
    "PROJECT_TEST_COPTS",
)

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "event-logger",
    hdrs = [
        "event_logger.h",
    ],
    srcs = [],
    deps = [
        "@fmt//:fmt",
        "@spdlog//:spdlog"
    ],
    copts = PROJECT_DEFAULT_COPTS,
)

cc_test(
    name = "event-logger-test",
    srcs = [
        "event_logger_test.cc",
    ],
    copts = PROJECT_TEST_COPTS,
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":event-logger",
        "@catch2//:catch2"
    ],
)

