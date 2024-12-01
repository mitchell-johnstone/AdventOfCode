const std = @import("std");
const data = @embedFile("in_1.txt");
pub fn main() !void {
    var lines = std.mem.tokenize(u8, data, "\n");
    std.debug.print("hello, sol 1\n\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var l1 = std.ArrayList(i32).init(allocator);
    var l2 = std.ArrayList(i32).init(allocator);
    defer l1.deinit();
    defer l2.deinit();

    while (lines.next()) |line| {
        var it = std.mem.split(u8, line, " ");
        while (it.next()) |x| {
            if (x.len > 0) {
                const i = try std.fmt.parseInt(i32, x, 10);
                if (l1.items.len == l2.items.len) {
                    try l1.append(i);
                } else {
                    try l2.append(i);
                }
            }
        }
    }
    const s1 = try l1.toOwnedSlice();
    const s2 = try l2.toOwnedSlice();

    std.mem.sort(i32, s1, {}, comptime std.sort.asc(i32));
    std.mem.sort(i32, s2, {}, comptime std.sort.asc(i32));
    
    var sum: u32 = 0;
    for (s1, s2) |v1, v2| {
        sum += @abs(v1 - v2);
    }

    std.debug.print("{}\n", .{sum});

    var map = std.AutoHashMap(i32, i32).init(allocator);
    defer map.deinit();

    for (s2) |v| {
        if (map.get(v)) |mv| {
            try map.put(v, mv+1);
        } else {
            try map.put(v, 1);
        }
    }
    
    var sim: i32 = 0;
    for (s1) |v| {
        if (map.get(v)) |mv| {
            sim += v * mv;
        }
    }
    std.debug.print("\n{}", .{sim});
}
