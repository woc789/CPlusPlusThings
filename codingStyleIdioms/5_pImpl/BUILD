# please run `bazel run //codingStyleIdioms/5_pImpl:pimpl`
# please run `bazel run //codingStyleIdioms/5_pImpl:pimplTime`
# please run `bazel run //codingStyleIdioms/5_pImpl:noPimpl`

load("@rules_cc//cc:defs.bzl", "cc_binary","cc_library")

cc_binary(
    name = "pimpl",
    srcs = ["pimpl.cpp"],
    copts = ["-std=c++11"],
)
cc_binary(
    name = "pimplTime",
    srcs = ["pimplTime.cpp"],
    copts = ["-std=c++11"],
)
cc_binary(
    name = "noPimpl",
    srcs = ["noPimpl.cpp"],
    copts = ["-std=c++11"],
)

cc_library(
    name = "logger_lib",
    srcs = ["Logger.cpp"],
    hdrs = ["Logger.h"],  # <-- **关键步骤**：Bazel 知道这是一个需要暴露的头文件
    copts = ["-std=c++11"],
    visibility = ["//visibility:public"], # 允许其他目标使用
)
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = ["-std=c++11"],
    deps = [
        ":logger_lib", 
    ],
)

