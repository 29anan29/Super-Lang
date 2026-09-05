# Scala

- **Formatter**: `scalafmt`
- **Indent**: 2 spaces
- **Naming**: `lowerCamelCase`, `UpperCamelCase` types,
  `UPPER_SNAKE_CASE` constants
- **Error handling**: `Try`/`Either`/`Option`; no exceptions for control flow
- **Concurrency**: futures / actors (Akka)
- **Feature gate**: `build.sbt` / config

## Guidance

- Prefer functional style: immutable `val`, pure functions, and expressive
  `Option`/`Either`/`Try` over exceptions for expected failure paths.
- Use `Future`/effect types for concurrency with explicit error handling; keep
  shared state immutable or behind actors.
- Prefer ADTs (case classes/sealed traits) for domain modeling.
- Keep functions pure and small; validate input at boundaries.
- Run `scalafmt` and the compiler (`scalac`/`sbt`) warnings clean before
  committing.