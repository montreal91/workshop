const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardReleaseOptions();

    const clox = b.addExecutable("clox", null);
    clox.setTarget(target);
    clox.setBuildMode(mode);
    clox.install();
    clox.linkLibC();
    clox.addIncludeDir("src/");
    clox.addCSourceFiles(&.{
        "src/main.c",
    }, &.{
        "-std=c11",
        "-pedantic",
        "-Wall",
        "-W",
        "-Wno-missing-field-initializers"
    });

}
