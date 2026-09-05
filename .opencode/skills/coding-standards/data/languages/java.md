# Java

- **Formatter**: `google-java-format` / Spotless
- **Indent**: 4 spaces
- **Naming**: `camelCase` methods/variables, `PascalCase` classes,
  `SCREAMING_SNAKE_CASE` constants
- **Error handling**: checked/unchecked exceptions; `Optional`; never swallow
- **Concurrency**: `java.util.concurrent`
- **Feature gate**: build config / annotations

## Guidance

- Rely on the JDK collections and libraries; prefer `var` where the type is
  obvious from the RHS.
- Use `Optional` / `Objects.requireNonNull` for null-safety; prefer records
  and sealed types for data carriers.
- Catch exceptions at the boundary and translate to meaningful, typed errors;
  never `catch (Exception e) {}` empty blocks; do not use exceptions for
  ordinary control flow.
- Prefer `java.util.concurrent` primitives (`ConcurrentHashMap`, `Executor`,
  `CompletableFuture`) over bare `synchronized` where appropriate.
- Keep methods small; use expressive, intention-revealing names.