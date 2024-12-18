const std = @import("std");
const Regex = @import("regex").Regex;
const data = @embedFile("in_7.txt");

pub fn concat(a:usize, b:usize) usize {
    if (b == 0) return 10*a+b;
    return a*std.math.pow(usize, 10, 1+std.math.log10(b))+b;
}
pub fn test_target(target:usize, vals:[]usize, cur:usize, idx:usize, p2:bool) bool {
    if(cur > target) return false;
    if(idx >= vals.len) return cur == target;
    return test_target(target, vals, cur+vals[idx], idx+1, p2) or test_target(target, vals, cur*vals[idx], idx+1, p2) or (if (p2) test_target(target, vals, concat(cur, vals[idx]), idx+1, p2) else false);
}
pub fn test_target_wrapper(target:usize, vals:[]usize, p2:bool) bool {
    return test_target(target, vals, vals[0], 1, p2);
}
pub fn process(line: []const u8, p2:bool) !usize {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var args = std.mem.splitScalar(u8, line, ' ');
    var idx:usize = 0;
    var target:usize = 0;
    var opts = std.ArrayList(usize).init(allocator);
    while(args.next()) |arg|:(idx+=1) {
        if (idx == 0) {
            // first item is "val:", so get rid of ':'
            target = try std.fmt.parseInt(usize, arg[0..arg.len-1], 10);
        } else {
            try opts.append(try std.fmt.parseInt(usize, arg, 10));
        }
    }
    return if (test_target_wrapper(target, opts.items, p2)) target else 0;
}
pub fn main() !void {
    std.debug.print("AOC 2024 sol 7\n-------------\n", .{});

    var lines = std.mem.tokenize(u8, data, "\n");
    var sum : usize = 0;
    while (lines.next()) |line| {
        const res = try process(line, false);
        // std.debug.print("{s} -> {}\n", .{line, res});
        sum += res;
    }
    std.debug.print("{}\n", .{sum});

    sum = 0;
    lines = std.mem.tokenize(u8, data, "\n");
    while (lines.next()) |line| {
        const res = try process(line, true);
        sum += res;
    }
    std.debug.print("{}\n", .{sum});
}
