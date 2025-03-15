const std = @import("std");
const file_data = @embedFile("in_12.txt");
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
var visited = init: {
    @setEvalBranchQuota(1_000_000);
    var nl_count = 0;
    for(file_data) |ch| nl_count += if (ch == '\n') 1 else 0;
    var first_nl = 0;
    while(file_data[first_nl] != '\n') first_nl+=1;

    const initial:[first_nl][nl_count]bool = .{.{false} ** first_nl} ** nl_count;
    break :init initial;
};
var visited2 = init: {
    @setEvalBranchQuota(1_000_000);
    var nl_count = 0;
    for(file_data) |ch| nl_count += if (ch == '\n') 1 else 0;
    var first_nl = 0;
    while(file_data[first_nl] != '\n') first_nl+=1;

    const initial:[first_nl][nl_count]bool = .{.{false} ** first_nl} ** nl_count;
    break :init initial;
};
var side_counted = init: {
    @setEvalBranchQuota(1_000_000);
    var nl_count = 0;
    for(file_data) |ch| nl_count += if (ch == '\n') 1 else 0;
    var first_nl = 0;
    while(file_data[first_nl] != '\n') first_nl+=1;

    const initial:[first_nl][nl_count]u8 = .{.{0} ** first_nl} ** nl_count;
    break :init initial;
};

pub fn price(r:usize, c:usize, signature:u8) std.math.Complex(usize) {
    // return is {area, perim}
    // if outside or found new patch, add 1 to perimeter
    if(r >= grid.len or c >= grid[0].len or grid[r][c] != signature) return std.math.Complex(usize).init(0, 1);

    // if we've already visited here, then return nothing
    if(visited[r][c]) return std.math.Complex(usize).init(0, 0);
    // otherwise, mark we've gotten here!
    visited[r][c] = true;

    // Otherwise, we're adding to the area!
    var res = std.math.Complex(usize).init(1, 0);
    // recurse to neighbors.
    res = res.add(price(r+%1, c, signature));
    res = res.add(price(r-%1, c, signature));
    res = res.add(price(r, c+%1, signature));
    res = res.add(price(r, c-%1, signature));

    return res;
}

pub fn price2(r:usize, c:usize, signature:u8) std.math.Complex(usize) {
    // return is {area, perim}

    // if outside or found new patch, quit
    if(r >= grid.len or c >= grid[0].len or grid[r][c] != signature or visited2[r][c]) return std.math.Complex(usize).init(0, 0);

    // otherwise, mark we've gotten here!
    visited2[r][c] = true;

    // Otherwise, we're adding to the area!
    var res = std.math.Complex(usize).init(1, 0);
    // recurse to neighbors.
    res = res.add(price(r+%1, c, signature));
    res = res.add(price(r-%1, c, signature));
    res = res.add(price(r, c+%1, signature));
    res = res.add(price(r, c-%1, signature));
}

pub fn main() !void {
    std.debug.print("AOC 2024 sol 12\n-------------\n", .{});

    // for(visited)|line|{
    //     std.debug.print("{any}\n", .{line});
    // }

    var total_price:usize = 0;
    for(grid,0..)|line,r|{
        for(line,0..)|ch,c|{
            if(!visited[r][c]){
                const p = price(r, c, ch);
                total_price += p.re*p.im;
            }
        }
    }
    std.debug.print("{}\n", .{total_price});
}
