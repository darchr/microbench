# Note: we should probably have a name parameter
def bench(randArr=False):
    dps = ["//:common"]
    if randArr:
        dps += ["libRandArr"]

    # It would probably be better to have a unique name.
    native.cc_binary(
        name = "bench",
        srcs = ["bench.c"],
        deps = dps
    )

    native.cc_library(
        name = "libRandArr",
        hdrs = ["randArr.h"],
        visibility = ["//visibility:private"]
    )

    native.genrule(
        name = "randArr",
        srcs = ["rand_arr_args.txt"],
        outs = ["randArr.h"],
        tools = ["//:rand_c_arr"],
        cmd = "./$(location //:rand_c_arr) `cat $(location rand_arr_args.txt)` > $@",
    )
