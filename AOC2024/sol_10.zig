const std = @import("std");
const file_data = @embedFile("in_10.txt");
var grid = init: {
    @setEvalBranchQuota(1_000_000);
    var nl_count = 0;
    for(file_data) |ch| nl_count += if (ch == '\n') 1 else 0;
    var first_nl = 0;
    while(file_data[first_nl] != '\n') first_nl+=1;

    var initial:[nl_count][first_nl]u8 = undefined;
    var row:usize = 0;
    var col:usize = 0;
    for (0..file_data.len) |i|{
        if(file_data[i] == '\n') {
            row += 1;
            col = 0;
        } else {
            initial[row][col] = file_data[i];
            col += 1;
        }
    }
    break :init initial;
};

inline fn inGrid(point: std.math.Complex(i32), map: anytype) bool {
    return 0 <= point.re and point.re < map.len and 0 <= point.im and point.im < map[0].len;
}

const Peak = std.AutoHashMap(std.math.Complex(i32), void);
pub fn score(point: std.math.Complex(i32), map: anytype, cur: u8, peaks: *Peak) !void {
    if(cur == '9') {
        try peaks.put(point, {});
        return;
    }
    // try the 4 dir
    var dir = std.math.Complex(i32).init(1, 0);
    for(0..4)|_| {
        const next_pt = point.add(dir);
        dir = dir.mulbyi();
        if(!inGrid(next_pt, map)) continue; // out of bounds! bad
        // std.debug.print("trying {any}\n", .{next_pt});
        if(map[@intCast(next_pt.re)][@intCast(next_pt.im)] == cur+1) {
            try score(next_pt, map, cur+1, peaks);
        }
    }
}

pub fn score2(point: std.math.Complex(i32), map: anytype, cur: u8, ) usize {
    if(cur == '9') return 1;
    // try the 4 dir
    var dir = std.math.Complex(i32).init(1, 0);
    var sum: usize = 0;
    for(0..4)|_| {
        const next_pt = point.add(dir);
        dir = dir.mulbyi();
        if(!inGrid(next_pt, map)) continue; // out of bounds! bad
        // std.debug.print("trying {any}\n", .{next_pt});
        if(map[@intCast(next_pt.re)][@intCast(next_pt.im)] == cur+1) {
            sum += score2(next_pt, map, cur+1);
        }
    }
    return sum;
}

pub fn main() !void {
    std.debug.print("AOC 2024 sol 10\n-------------\n", .{});
    
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var sum: usize = 0;
    var sum2: usize = 0;
    for(grid,0..) |line, row| {
        for(line,0..) |ch, col| {
            if(ch == '0'){
                const point = std.math.Complex(i32).init(@intCast(row), @intCast(col));
                // std.debug.print("at {} {}\n", .{row, col});
                var peak = Peak.init(allocator);
                try score(point, grid, '0', &peak);
                // std.debug.print("\n\t{}\n", .{peak.count()});
                sum += peak.count();
                sum2 += score2(point, grid, '0');
            }
        }
    }
    std.debug.print("{}\n", .{sum});
    std.debug.print("{}\n", .{sum2});
}
