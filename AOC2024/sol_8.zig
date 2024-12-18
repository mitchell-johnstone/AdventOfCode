const std = @import("std");
const data = @embedFile("in_8.txt");
const lib = @import("lib.zig");

pub fn in_rect(point: std.math.Complex(i32), boundary:std.math.Complex(usize)) bool {
    return point.re >= 0 and point.re < boundary.re and point.im >= 0 and point.im < boundary.im;
}

pub fn main() !void {
    std.debug.print("AOC 2024 sol 8\n-------------\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var antennas = std.AutoHashMap(u8, std.ArrayList(std.math.Complex(i32))).init(allocator);

    var lines = std.mem.tokenize(u8, data, "\n");
    var row:i32 = 0;
    var col:i32 = 0;
    while(lines.next()) |line| {
        col = 0;
        for(line) |ch| {
            if(ch != '.') {
                if(!antennas.contains(ch)) {
                    const al = std.ArrayList(std.math.Complex(i32)).init(allocator);
                    try antennas.put(ch, al);
                }
                const cur = std.math.Complex(i32).init(row, col);
                try antennas.getPtr(ch).?.append(cur);
            }
            col += 1;
        }
        row += 1;
    }
    const boundary = std.math.Complex(usize).init(@intCast(row), @intCast(col));

    var uniq_pts = std.AutoHashMap(std.math.Complex(i32), void).init(allocator);
    var all_uniq_pts = std.AutoHashMap(std.math.Complex(i32), void).init(allocator);
    var it = antennas.iterator();
    while(it.next()) |entry| {
        const items = entry.value_ptr.*.items;
        for(0..items.len-1) |a| {
            for(a+1..items.len) |b| {
                const u = items[a];
                const v = items[b];

                var cur = u.add(u.sub(v));
                if (in_rect(cur, boundary)) {
                    try uniq_pts.put(cur, {});
                }
                cur = v.add(v.sub(u));
                if (in_rect(cur, boundary)) {
                    try uniq_pts.put(cur, {});
                }

                const diff = u.sub(v);
                cur = u;
                while(in_rect(cur, boundary)):(cur = cur.add(diff)) {
                    try all_uniq_pts.put(cur, {});
                }
                cur = v;
                while(in_rect(cur, boundary)):(cur = cur.sub(diff)) {
                    try all_uniq_pts.put(cur, {});
                }
            }
        }
    }
    std.debug.print("{}\n", .{uniq_pts.count()});
    std.debug.print("{}\n", .{all_uniq_pts.count()});
    // const boundary = std.math.Complex(usize).init(row, col);
}
