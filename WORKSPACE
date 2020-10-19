workspace(
    name = "zmq",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

http_archive(
    name = "gtest_http_archive",
    build_file = "gtest.BUILD",
    sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
    strip_prefix = "googletest-release-1.8.0",
    url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
)

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

new_git_repository(
    name = "libzmq",
    build_file_content = all_content,
    commit = "97b5f8560d9ce561949537b6c4c98e8eb2138148",
    remote = "https://github.com/zeromq/libzmq.git",
    shallow_since = "1602270485 +0100",
)

new_git_repository(
    name = "cppzmq",
    build_file_content = """
cc_library(
    name = "cppzmq",
    srcs = ["zmq.hpp"],
    deps = ["@zmq//:libzmq"],
    visibility = ["//visibility:public"]
)""",
    commit = "03243ad64db652c43d150e9fb5a80a13c1a1a4a9",
    remote = "https://github.com/zeromq/cppzmq.git",
    shallow_since = "1601902098 +0200",
)

git_repository(
    name = "rules_foreign_cc",
    commit = "ed95b95affecaa3ea3bf7bab3e0ab6aa847dfb06",
    remote = "https://github.com/bazelbuild/rules_foreign_cc",
    shallow_since = "1599808059 +0200",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()
