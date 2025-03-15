const std = @import("std");
const data = @embedFile("in_11.txt");

const stone_iter = struct {
    num:usize,
    iters:usize,
};
var memoize:std.AutoHashMap(stone_iter, usize) = undefined;

fn count_digits(num:usize) usize {
    return std.math.log10(num) + 1;
}
fn split(num:usize) @Vector(2, usize) {
    const d = count_digits(num);
    const p = std.math.pow(usize, 10, d/2);
    return @Vector(2, usize){num/p, @mod(num, p)};
}
fn count_stones(stone_num:usize, iters:usize) !usize {
    if(iters==0) {
        // std.debug.print("{} ", .{stone_num});
        return 1;
    }
    const cur_stone = stone_iter{
        .num = stone_num,
        .iters = iters,
    };
    if(memoize.contains(cur_stone)) return memoize.get(cur_stone).?;
    
    const res:usize = cs:{
        if(stone_num == 0) {
            break :cs try count_stones(1, iters-1);
        } else if(@mod(count_digits(stone_num), 2) == 0){
            const vec = split(stone_num);
            break :cs try count_stones(vec[0], iters-1) + try count_stones(vec[1], iters-1);
        } else {
            break :cs try count_stones(stone_num*2024, iters-1);
        }
    };
    try memoize.put(cur_stone, res);
    return res;
}

pub fn main() !void {
    std.debug.print("AOC 2024 sol 11\n-------------\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    memoize = std.AutoHashMap(stone_iter, usize).init(allocator);
    var stones = std.mem.splitScalar(u8, data[0..data.len-1], ' ');

    var sum:usize = 0;
    var sum2:usize = 0;
    while (stones.next()) |stone| {
        const num = try std.fmt.parseInt(usize, stone, 10);
        sum += try count_stones(num, 25);
        sum2 += try count_stones(num, 75);
    }
    std.debug.print("\n{}\n", .{sum});
    std.debug.print("\n{}\n", .{sum2});
}
