# Zig

- **Formatter**: `zig fmt`
- **Indent**: 4 spaces
- **Naming**: `snake_case`, `CamelCase` types, `SCREAMING_SNAKE_CASE` constants
- **Error handling**: error unions (`!T`); explicit handling, no silent ignore
- **Concurrency**: `std.Thread`, `std.atomic`
- **Feature gate**: compile-time `comptime`

## Guidance

- Use error unions (`!T`) to propagate failures explicitly; handle errors at
  the boundary; never ignore an error silently.
- Pin resource lifetimes: pair `allocator.alloc`/`defer allocator.free` on
  every path; prefer arena/`std.heap` allocators deliberately.
- Use `comptime` for compile-time computation and feature gating; keep
  low-level/unsafe idioms minimal and documented.
- Prefer slices over raw pointers; make ownership explicit.
- **Check pointers/slices before use**: validate `null`/empty slices on entry
  and after allocation; prefer `if (ptr) |p| …` / error unions over silent
  dereference of a null/dangling value.
- Run `zig fmt` and `zig build test` before committing.
- **File header (lines 1-2):** a short comment stating the file's purpose, plus
  any required license/`SPDX` tag.