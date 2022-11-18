const std = @import("std");

pub fn build(b: *std.build.Builder) void {
  const target = b.standardTargetOptions(.{});
  const mode = b.standardReleaseOptions();

  const hello = b.addExecutable("hello", null);
  hello.setTarget(target);
  hello.setBuildMode(mode);
  hello.install();
  hello.linkLibC();
  hello.linkLibCpp();
  hello.addCSourceFiles(&.{
    "hello.cpp",
  }, &.{
    "-std=c++17", "-Wall"
  });
}
