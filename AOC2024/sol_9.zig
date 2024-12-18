const std = @import("std");
const data = @embedFile("in_9.txt");
var d1 = init: {
    var initial = [_]u8 {' '} ** (data.len-1);
    @setEvalBranchQuota(1_000_000);
    for (&initial,0..) |*pt, i|{
        pt.* = data[i];
    }
    break :init initial;
};
const file = struct {
    pos: usize,
    len: usize,
    id: usize,
    moved: bool,

    fn checksum(self: file) usize {
        var sum:usize = 0;
        for(0..self.len) |i| {
            sum += self.id * (self.pos+i);
        }
        return sum;
    }
};
fn asc_file(_: void, l:file, r:file) bool {
    return l.pos < r.pos;
}
var d2 = init: {
    var initial: [((data.len)/2)]file = undefined;
    @setEvalBranchQuota(1_000_000);
    var pos: usize = 0;
    for (0..(data.len-1)) |i|{
        const cur = data[i]-'0';
        if (@mod(i, 2) == 0) {
            // We found a file! Make the struct
            initial[i/2] = file{
                .pos = pos,
                .len = cur,
                .id = i/2,
                .moved = false,
            };
        }
        // otherwise, it's just empty space
        pos += cur;
    }
    break :init initial;
};

pub fn main() !void {
    std.debug.print("AOC 2024 sol 9\n-------------\n", .{});
    
    try std.testing.expect(@mod(d1.len, 2) == 1);

    // var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    // defer arena.deinit();
    // const allocator = arena.allocator();

    var checksum:u100 = 0;
    var l:usize = 0;
    var r:usize = d1.len-1;
    // _ = &checksum;
    // _ = &l;
    // _ = &r;
    for(0..1_000_000_000) |pos| {
        while(d1[l] == '0' and l <= r) l+=1;
        while(d1[r] == '0' and l <= r) r-=2;
        if(l > r) break;
        if(@mod(l, 2) == 0) {
            // even, so a file w/ d1[l] blocks!
            checksum += pos * l/2;
            d1[l]-=1;
        } else {
            // odd, so found d1[l] empty blocks!
            //  fill them with blocks from d1[r]!
            checksum += pos * r/2;
            d1[l]-=1;
            d1[r]-=1;
        }
    }
    std.debug.print("{}\n", .{checksum});
    // std.debug.print("{any}\n", .{d2});
    var cur = d2.len-1;
    while (cur > 0) {
        // have we moved already?
        if(!d2[cur].moved) {
            // loop through the files before it!
            place: for(0..cur) |i| {
                const start = d2[i].pos+d2[i].len;
                const space = d2[i+1].pos-start;
                if(space >= d2[cur].len) {
                    // we can fit it in!
                    d2[cur].pos = start;
                    d2[cur].moved = true;
                    // sort the files
                    std.mem.sort(file, &d2, {}, asc_file);
                    cur += 1; // add 1 to go to newly placed
                    break :place;
                }
            }
        }
        cur -= 1;
    }
    // std.debug.print("{any}", .{d2});
    // for(d2) |f| std.debug.print("{}x{} ", .{f.id,f.len});
    checksum = 0;
    for(d2) |f| checksum += f.checksum();
    std.debug.print("{}\n", .{checksum});
}
