load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_library(
    name = "zmq_pub_sub",
    srcs = ["src/zmq_pub_sub.cpp"],
    hdrs = ["public/zmq_pub_sub.h"],
    deps = ["@cppzmq"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "zmq_raw",
    srcs = ["src/zmq_raw.cpp"],
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
    out_include_dir = "include/libzmq",
    shared_libraries = [
        "libzmq.so",
    ],
    visibility = ["//visibility:public"],
)
