cc_test(
    name = "zmq_spec",
    srcs = ["zmq_spec.cpp"],
    deps = [
        "//:zmq_pub_sub",
        "@gtest_http_archive//:gtest",
    ],
)

cc_test(
    name = "zmq_blocking_close_spec",
    srcs = ["zmq_blocking_close_spec.cpp"],
    deps = [
        "@cppzmq",
        "@gtest_http_archive//:gtest",
    ],
)
