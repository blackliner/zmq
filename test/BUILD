

cc_test(
    name = "zmq_spec",
    srcs = ["zmq_spec.cpp"],
    copts = ["-Iexternal/gtest/include",
             "-Ipublic"],
    deps = [
        "@gtest_http_archive//:gtest",
        "//:zmq_pub_sub",
    ],
    visibility = ["//visibility:public"]
)