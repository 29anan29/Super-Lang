# Kotlin

- **Formatter**: `ktlint`
- **Indent**: 4 spaces
- **Naming**: `camelCase`, `PascalCase` types, `SCREAMING_SNAKE_CASE` constants
  in `companion object` / top-level
- **Error handling**: exceptions / sealed classes / `Result`; no exceptions for
  control flow
- **Concurrency**: coroutines (`suspend`, `Dispatchers`, `Flow`)
- **Feature gate**: Gradle + build config / expect-actual

## Guidance

- Prefer `val` over `var`; use data classes, sealed classes, and `sealed
  interface` for expressive domain modeling.
- Use null-safe idioms (`?`, `let`/`run`, `?:`) instead of platform types or
  forced `!!`; avoid `!!` unless invariants guarantee non-null.
- Release resources with `use {}` / `close()` / `finally`.
- Keep the happy path in the main flow; propagate failures via `Result` or
  sealed results rather than exceptions where idiomatic.
- Use coroutines for concurrency with explicit `Dispatchers` and structured
  concurrency (scopes/cancellation). Run `ktlint` before committing.