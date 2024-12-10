const std = @import("std");
const data = @embedFile("in_6.txt");
const Complex = std.math.Complex;

pub fn inGrid(point: Complex(i32), grid:*std.ArrayList(std.ArrayList(u8))) bool {
    return 0 <= point.re and point.re < grid.items.len and 0 <= point.im and point.im < grid.items[0].items.len;
}
pub fn main() !void {
    std.debug.print("AOC 2024 sol 6\n-------------\n", .{});
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var lines = std.mem.splitScalar(u8, data, '\n');
    var blocks = std.AutoHashMap(Complex(i32), void).init(allocator);
    var grid = std.ArrayList(std.ArrayList(u8)).init(allocator);
    var start: Complex(i32) = undefined;
    
    // read the input
    var r: i32 = 0;
    while (lines.next()) |line| : (r += 1) {
        if(line.len == 0) break;
        for (line, 0..) |ch, c| {
            switch (ch) {
                '#' => { try blocks.put(Complex(i32).init(r, @intCast(c)), {}); },
                '^' => { start = Complex(i32).init(r, @intCast(c)); },
                else => {continue;},
            }
        }
        var al = std.ArrayList(u8).init(allocator);
        try al.appendSlice(line);
        try grid.append(al);
    }
    // for(grid.items)|line|{
    //     std.debug.print("{s}\n", .{line.items});
    // }
    // std.debug.print("\n", .{});

    // walk!
    var uniq_walk = std.AutoHashMap(Complex(i32), void).init(allocator);
    var dir = Complex(i32).init(-1, 0);
    var cur = start;

    while(inGrid(cur, &grid)) : (cur = cur.add(dir)) {
        // rotate?
        if(blocks.contains(cur)) {
            // last one doesn't count
            _ = uniq_walk.remove(cur);
            cur = cur.sub(dir);
            // rotate to the right
            dir = dir.mulbyi().mulbyi().mulbyi();
        }
        try uniq_walk.put(cur, {});
    }

    // for(grid.items)|line|{
    //     std.debug.print("{s}\n", .{line.items});
    // }
    // std.debug.print("\n", .{});

    // part 2! Re walk, but put obstacles
    var count: usize = 0;
    var uw_it = uniq_walk.iterator();
    while(uw_it.next()) |entry| {
        const loop_block = entry.key_ptr;
        try blocks.put(loop_block.*, {});

        // try to walk again!
        // any position that's been hit more than 4 times = loop
        var walk = std.AutoHashMap(Complex(i32), i32).init(allocator);
        dir = Complex(i32).init(-1, 0);
        cur = start;

        walking: while(inGrid(cur, &grid)) : (cur = cur.add(dir)) {
            // rotate?
            if(blocks.contains(cur)) {
                // last one doesn't count
                cur = cur.sub(dir);
                // rotate to the right
                dir = dir.mulbyi().mulbyi().mulbyi();
            } else {
                if(!walk.contains(cur)) {
                    try walk.put(cur, 0);
                }
                const old = walk.get(cur).?;
                try walk.put(cur, old + 1);
                if(old + 1 > 4) {
                    count += 1;
                    break :walking;
                }
            }
        }

        _ = blocks.remove(loop_block.*);
    }

    std.debug.print("{}\n", .{uniq_walk.count()});
    std.debug.print("{}\n", .{count});
}
