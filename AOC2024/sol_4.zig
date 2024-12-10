const std = @import("std");
const print = std.debug.print;
const data = @embedFile("in_4.txt");

pub fn main() !void {
    std.debug.print("AOC 2024 sol 4\n-------------\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var lines = std.mem.tokenize(u8, data, "\n");
    var all_lines = std.ArrayList([]const u8).init(allocator);
    defer all_lines.deinit();

    while(lines.next()) |line| {
        try all_lines.append(line);
    }
    const grid = try all_lines.toOwnedSlice();

    var sum: u32 = 0;
    const search = "XMAS";
    const dirs = [_]i32{-1,0,1};
    for (0..grid.len) |r| {
        for (0..grid[r].len) |c| {
            for(dirs) |dr| {
                dir: for(dirs) |dc| {
                    for(search, 0..) |ch, dist| {
                        const nr = @as(i32,@intCast(r)) + @as(i32,@intCast(dr))*@as(i32,@intCast(dist));
                        const nc = @as(i32,@intCast(c)) + @as(i32,@intCast(dc))*@as(i32,@intCast(dist));
                        if(nc < 0 or nr < 0) continue :dir;
                        const unr:usize = @intCast(nr);
                        const unc:usize = @intCast(nc);
                        if(!(unr<grid.len and unc<grid[unr].len)) continue :dir;
                        if(ch != grid[unr][unc]) continue :dir;
                    }
                    sum += 1;
                }
            }
        }
    }
    std.debug.print("xmas found {} times\n", .{sum});

    var count:u32 = 0;
    for (1..grid.len-1) |r| {
        for (1..grid[r].len-1) |c| {
            if(grid[r][c] != 'A') continue;
            if(grid[r+1][c+1] == 'M' and grid[r+1][c-1] == 'M' and grid[r-1][c-1] == 'S' and grid[r-1][c+1] == 'S') count+=1;
            if(grid[r+1][c+1] == 'M' and grid[r+1][c-1] == 'S' and grid[r-1][c-1] == 'S' and grid[r-1][c+1] == 'M') count+=1;
            if(grid[r+1][c+1] == 'S' and grid[r+1][c-1] == 'S' and grid[r-1][c-1] == 'M' and grid[r-1][c+1] == 'M') count+=1;
            if(grid[r+1][c+1] == 'S' and grid[r+1][c-1] == 'M' and grid[r-1][c-1] == 'M' and grid[r-1][c+1] == 'S') count+=1;
        }
    }
    std.debug.print("x-mas found {} times\n", .{count});
}
