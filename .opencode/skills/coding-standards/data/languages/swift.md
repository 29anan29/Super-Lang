# Swift

- **Formatter**: `swift-format`
- **Indent**: 4 spaces
- **Naming**: `lowerCamelCase` functions/variables, `UpperCamelCase` types
- **Error handling**: `do`/`catch`, `Result`, optionals (no force-unwrap)
- **Concurrency**: GCD / actors (`actor`), `async`/`await`
- **Feature gate**: `#if canImport` / build config

## Guidance

- Prefer value types (`struct`) and immutability (`let`) where natural; use
  optionals safely (`if let`/`guard let`), never `!` force-unwrap on
  fallible paths.
- Throw typed errors and catch them at the boundary; use `Result` for
  async-style failure signalling.
- Release/manage resources with `defer {}` regardless of return path.
- Use actors and `<Swift 5.5+` `async`/`await` for safe concurrency; avoid
  sharing mutable state across actors without isolation.
- Run `swift-format` and `swiftlint` before committing.