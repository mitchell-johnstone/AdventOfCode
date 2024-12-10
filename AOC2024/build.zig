const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const regex_pkg = b.dependency("regex", .{
        .target = target,
        .optimize = optimize,
    });

    const lib = b.addStaticLibrary(.{
        .name = "AOC2024",
        .root_source_file = b.path("lib.zig"),
        .target = target,
        .optimize = optimize,
    });
    lib.root_module.addImport("regex", regex_pkg.module("regex"));
    b.installArtifact(lib);

    advent: for (1..26) |day| {
        var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
        defer arena.deinit();
        const allocator = arena.allocator();

        _ = std.fs.cwd().openFile(try std.fmt.allocPrint(allocator, "sol_{}.zig", .{day}), .{}) catch {continue:advent;};

        const exe = b.addExecutable(.{
            .name = try std.fmt.allocPrint(allocator, "AOC2024_d{}", .{day}),
            .root_source_file = b.path(try std.fmt.allocPrint(allocator,"sol_{}.zig", .{day})),
            .target = target,
            .optimize = optimize,
        });
        exe.root_module.addImport("regex", regex_pkg.module("regex"));
        b.installArtifact(exe);
        const run_cmd = b.addRunArtifact(exe);
        run_cmd.step.dependOn(b.getInstallStep());
        const run_step = b.step(try std.fmt.allocPrint(allocator, "d{}", .{day}), try std.fmt.allocPrint(allocator,"Advent of Code Day {}", .{day}));
        run_step.dependOn(&run_cmd.step);
    }

    const main = b.addExecutable(.{
        .name = "AOC2024_main",
        .root_source_file = b.path("main.zig"),
        .target = target,
        .optimize = optimize,
    });
    main.root_module.addImport("regex", regex_pkg.module("regex"));
    b.installArtifact(main);
    const main_run_cmd = b.addRunArtifact(main);
    main_run_cmd.step.dependOn(b.getInstallStep());
    const main_run_step = b.step("main", "Advent of Code main");
    main_run_step.dependOn(&main_run_cmd.step);
}
