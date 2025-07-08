const std = @import("std");

pub fn main() !void {
    const nx: u8 = 200;
    const ny: u8 = 100;

    const stdout = std.io.getStdOut().writer();
    try stdout.print("P3\n{} {}\n255\n", .{ nx, ny });

    for (0..ny) |j_unflipped| {
        const j_flipped = ny - 1 - j_unflipped;
        for (0..nx) |i| {
            const r: f32 = @as(f32, @floatFromInt(i)) / @as(f32, @floatFromInt(nx));
            const g: f32 = @as(f32, @floatFromInt(j_flipped)) / @as(f32, @floatFromInt(ny));
            const b = 0.2;

            const ir: u8 = @intFromFloat(255.99 * r);
            const ig: u8 = @intFromFloat(255.99 * g);
            const ib: u8 = @intFromFloat(255.99 * b);

            try stdout.print("{} {} {}\n", .{ ir, ig, ib });
        }
    }
}
