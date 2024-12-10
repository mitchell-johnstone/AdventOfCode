const std = @import("std");
const data = @embedFile("in_2.txt");

const report = struct {
    data: []i32,
    fn _safe(self: *const report, inc:bool, skip:?usize) bool {
        var prev:usize = if (skip != 0) 0 else 1;
        for (1..self.data.len) |cur| {
            if(prev == cur or cur == skip) continue;
            if ((self.data[prev] < self.data[cur]) == inc) {
                return false;
            }
            const diff = @abs(self.data[prev]-self.data[cur]);
            if (!(1<=diff and diff<=3)) {
                return false;
            }
            prev = cur;
        }
        return true;
    }
    pub fn safe(self: *const report) bool {
        return self._safe(true, null) or self._safe(false, null);
    }
    fn _fuzzy_safe(self: *const report, inc:bool) bool {
        var prev:usize = 0;
        for (1..self.data.len) |cur| {
            if ((self.data[prev] < self.data[cur]) == inc) {
                return self._safe(inc, prev) or self._safe(inc, cur);
            }
            const diff = @abs(self.data[prev]-self.data[cur]);
            if (!(1<=diff and diff<=3)) {
                return self._safe(inc, prev) or self._safe(inc, cur);
            }
            prev = cur;
        }
        return true;
    }
    pub fn fuzzy_safe(self: *const report) bool {
        return self._fuzzy_safe(true) or self._fuzzy_safe(false);
    }
};
pub fn main() !void {
    std.debug.print("AOC 2024 sol 2\n-------------\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var lines = std.mem.tokenizeScalar(u8, data, '\n');
    var reports = std.ArrayList(report).init(allocator);
    defer reports.deinit();

    while(lines.next()) |line| {
        var vals = std.mem.splitScalar(u8, line, ' ');
        var temp_vals = std.ArrayList(i32).init(allocator);
        defer temp_vals.deinit();
        while(vals.next()) |val| {
            try temp_vals.append(try std.fmt.parseInt(i32, val, 10));
        }

        try reports.append(report{
            .data = try temp_vals.toOwnedSlice(),
        });
    }

    var safe_reps:u20 = 0;
    for (reports.items) |r| {
        // std.debug.print("{any} - {}\n", .{r.data, r.safe()});
        if (r.safe()) {
            safe_reps += 1;
        }
    }
    std.debug.print("{}\n", .{safe_reps});


    var wonky_safe_reps:u20 = 0;
    for (reports.items) |r| {
        // std.debug.print("{any} - {}\n", .{r.data, r.fuzzy_safe()});
        if (r.fuzzy_safe()) {
            wonky_safe_reps += 1;
        }
    }
    std.debug.print("{}\n", .{wonky_safe_reps});
}
