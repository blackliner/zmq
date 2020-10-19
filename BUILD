load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_library(
    name = "zmq_pub_sub",
    srcs = ["src/zmq_pub_sub.cpp"],
    hdrs = ["public/zmq_pub_sub.h"],
    includes = ["public"],
    visibility = ["//visibility:public"],
    deps = ["@cppzmq"],
)

cc_binary(
    name = "zmq_raw",
    srcs = ["src/zmq_raw.cpp"],
    deps = ["@cppzmq"],
)

cc_binary(
    name = "zmq_monitor",
    srcs = ["src/zmq_monitor.cpp"],
    deps = ["@cppzmq"],
)

cmake_external(
    name = "libzmq",
    cmake_options = [
        "-GNinja",
    ],
    lib_source = "@libzmq//:all",
    make_commands = [
        "ninja",
        "ninja install",
    ],
    shared_libraries = [
        "libzmq.so",
    ],
    visibility = ["//visibility:public"],
)
