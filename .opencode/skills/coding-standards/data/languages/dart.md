# Dart

- **Formatter**: `dart format`
- **Indent**: 2 spaces
- **Naming**: `lowerCamelCase`, `PascalCase` types,
  `SCREAMING_SNAKE_CASE` constants
- **Error handling**: exceptions; `Future`/`Stream`; sealed types
- **Concurrency**: isolates; `async`/`await`
- **Feature gate**: compile-time / build config

## Guidance

- Prefer `final`/`const` and value objects (records, sealed classes) for
  expressive modeling; keep classes small.
- Use `async`/`await` with `Future`/`Stream`; handle errors with typed
  exceptions and `try`/`catch`/`finally`; never silently swallow.
- Manage resources with `try`/`finally` or the appropriate guards.
- Use isolates (spawn/ports) for CPU-bound work; avoid sharing mutable state
  directly across isolates.
- Run `dart format` and the analyzer (`dart analyze`) before committing.