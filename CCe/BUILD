cc_binary(
    name = "bench",
    srcs = ["bench.c"],
    deps = [
        "//:common",
        "libRandArr"
    ]
)

cc_library(
    name = "libRandArr",
    hdrs = ["randArr.h"],
    visibility = ["//visibility:private"]
)

genrule(
    name = "randArr",
    srcs = ["rand_arr_args.txt"],
    outs = ["randArr.h"],
    tools = ["//:rand_c_arr"],
    cmd = "./$(location //:rand_c_arr) `cat $(location rand_arr_args.txt)` > $@",
)
