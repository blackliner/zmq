
cc_library(
    name = "zmq_pub_sub",
    srcs = ["src/zmq_pub_sub.cpp"],
    hdrs = ["public/zmq_pub_sub.h"],
    deps = ["@system_libs//:zmq"],
    copts = ["-Ipublic"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "zmq_raw",
    srcs = ["src/zmq_raw.cpp"],
    deps = ["@system_libs//:zmq"],
    linkopts = ["-pthread"]
)

