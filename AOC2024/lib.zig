const std = @import("std");
const testing = std.testing;

pub export fn add(a: i32, b: i32) i32 {
    return a + b;
}

test "basic add functionality" {
    try testing.expect(add(3, 7) == 10);
}
//
// pub export fn in_rect(point: std.math.Complex(i32), boundary:std.math.Complex(usize)) bool {
//     return point.re >= 0 and point.re < boundary.re and point.im >= 0 and point.im < boundary.im;
// }
