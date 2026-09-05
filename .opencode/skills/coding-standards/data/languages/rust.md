# Rust

- **Formatter**: `rustfmt`
- **Indent**: 4 spaces
- **Naming**: `snake_case` items, `CamelCase` types, `SCREAMING_SNAKE_CASE`
  constants
- **Error handling**: `Result<T, E>` + `?`, `Option`; no `unwrap`/`expect`/
  `panic` on library failure paths
- **Concurrency**: `Arc`, `Mutex`, `mpsc`/channels; ownership + borrowing
- **Feature gate**: Cargo features + `cfg`

## Guidance

- Leverage ownership, borrowing, lifetimes, and `Drop`; avoid raw pointers and
  `unsafe` unless unavoidable. Confine `unsafe` to small, documented wrappers
  with safety invariants on the enclosing item.
- Make fallible functions return `Result`, not `panic`; use `?` to propagate.
- Prefer enums for related constants; document public items with `///`.
- Use `cargo clippy` as the linter before committing; run `rustfmt`.
- Keep types explicit and idiomatic (`Option`/`Result`, newtypes over raw
  primitives where meaning is non-obvious).