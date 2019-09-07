load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest_http_archive",
    url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
    sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
    build_file = "gtest.BUILD",
    strip_prefix = "googletest-release-1.8.0"
)

new_local_repository(
    name = "system_libs",
    # pkg-config --variable=libdir x11
    path = "/usr/local/lib",
    build_file_content = """
cc_library(
    name = "zmq",
    srcs = glob(["libzmq*"]),
    visibility = ["//visibility:public"],
)
""",
)

#/usr/local/lib/libzmq.so