if [ ! -d AOC$1 ]
then
	mkdir AOC$1
fi

cookie="53616c7465645f5fd129dd0b0775e35edc2266d6977cb41b36708bdcadc8a33d8c228a4c6c428bb75bab1397cf0c85f7de345bce5f8137a2832c7080460bca76"

file="AOC$1/in_$2.txt"
if [ ! -f $file ]
then
	curl https://adventofcode.com/$1/day/$2/input --cookie "session=$cookie" > $file
fi

file="AOC$1/sol_$2.zig"
if [ ! -f $file ]
then
    cat > ./AOC$1/sol_$2.zig << EOL
const std = @import("std");
const print = std.debug.print;
const data = @embedFile("in_$2.txt");

pub fn main() !void {
    var lines = std.mem.tokenize(u8, data, "\n");
    std.debug.print("AOC $1 sol $2\n-------------\n", .{});

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

}
EOL
fi

nvim ./AOC$1/sol_$2.zig ./AOC$1/ex_$2.txt -O +12
