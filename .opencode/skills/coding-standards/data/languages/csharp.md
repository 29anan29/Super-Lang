# C# / .NET

- **Formatter**: `dotnet format` / `csharpier`
- **Indent**: 4 spaces
- **Naming**: `PascalCase` types/methods/properties, `camelCase` locals,
  `_camelCase` private fields
- **Error handling**: exceptions; `Result` patterns; `async Task`/`ValueTask`
- **Concurrency**: `async`/`await`, `lock`, TPL
- **Feature gate**: `#if` directives / build props

## Guidance

- Rely on the BCL (collections, LINQ) and idiomatic async (`Task`/`ValueTask`);
  avoid sync-over-async anti-patterns (`.Result`/`.Wait()`).
- Use null-safe idioms: nullable reference types, `?.`, `??`, and
  `required`/records for data models.
- Release disposable resources with `using`/`using var` regardless of return
  path; never swallow exceptions.
- Use `lock`/`ConcurrentDictionary`/TPL for shared state; GC is not
  synchronization.
- Run `dotnet format` and analyzers before committing.