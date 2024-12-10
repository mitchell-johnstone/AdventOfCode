const std = @import("std");
const data = @embedFile("in_3.txt");

pub fn is_num(c:u8) bool {
    return '0' <= c and c <= '9';
}
pub fn processLine(line:[]const u8) u32 {
    const pattern = "mul(_,_)";
    var idx: usize = 0;
    var sum: u32 = 0;
    while(true){
        if (idx >= line.len) break;
        // std.debug.print("\n{s}", .{line[idx..idx+1]});
        var a: u32 = 0;
        var b: u32 = 0;
        var first = true;
        var complete = false;

        // try to parse the pattern!
        for(pattern) |chr| {
            if(chr == '_') {
                while(idx < line.len and is_num(line[idx])) : (idx += 1) {
                    // std.debug.print("{s}", .{line[idx..idx+1]});
                    if(first) { a = 10*a + line[idx]-'0'; }
                    else {b = 10*b + line[idx]-'0';}
                }
                first = false;
                continue;
            }
            if(chr != line[idx]) break;
            if(chr == ')') complete = true;
            // std.debug.print("{s}", .{line[idx..idx+1]});
            idx += 1;
        }
        if (complete){
            // std.debug.print("\n\t{}*{}\n", .{a,b});
            sum += a*b;
        } else {
            idx += 1;
        }
    }
    return sum;
}
pub fn processLine2(line:[]const u8) u32 {
    const pattern = "mul(_,_)";
    const on = "do()";
    const off = "don't()";
    var state = true;
    var idx: usize = 0;
    var sum: u32 = 0;
    while(true){
        if (idx >= line.len) break;
        if(line.len - idx >= on.len and std.mem.eql(u8,line[idx..idx+on.len],on)){
            state = true;
            idx += on.len;
            continue;
        }
        if(line.len - idx >= off.len and std.mem.eql(u8,line[idx..idx+off.len],off)){
            state = false;
            idx += off.len;
            continue;
        }
        var a: u32 = 0;
        var b: u32 = 0;
        var first = true;
        var complete = false;

        // try to parse the pattern!
        for(pattern) |chr| {
            if(chr == '_') {
                while(idx < line.len and is_num(line[idx])) : (idx += 1) {
                    // std.debug.print("{s}", .{line[idx..idx+1]});
                    if(first) { a = 10*a + line[idx]-'0'; }
                    else {b = 10*b + line[idx]-'0';}
                }
                first = false;
                continue;
            }
            if(chr != line[idx]) break;
            if(chr == ')') complete = true;
            // std.debug.print("{s}", .{line[idx..idx+1]});
            idx += 1;
        }
        if (complete){
            // std.debug.print("\n\t{}*{}\n", .{a,b});
            if(state){
                sum += a*b;
            }
        } else {
            idx += 1;
        }
    }
    return sum;
}
pub fn main() !void {
    std.debug.print("AOC 2024 sol 3\n-------------\n", .{});
    
    // var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    // defer arena.deinit();
    // const allocator = arena.allocator();

    // var lines = std.mem.tokenizeScalar(u8, data, '\n');
    // var sum : u32 = 0;
    // while (lines.next()) |line| {
    //     sum += processLine(line);
    // }
    //
    // std.debug.print("{}\n", .{sum});
    std.debug.print("{}\n", .{processLine(data)});
    std.debug.print("{}\n", .{processLine2(data)});
}
