const std = @import("std");
const Regex = @import("regex").Regex;
const lib = @import("lib.zig");

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    
    var re = try Regex.compile(allocator, "\\w (there) (Mitchell)");
    if(try re.captures("hi there Mitchell ")) |capture| {
        var cap:usize = 0;
        while(capture.sliceAt(cap)) |found| : (cap+=1){
            std.debug.print("{s}", .{found});
        }
    }
    std.debug.print("{}", .{lib.add(3,2)});
}
