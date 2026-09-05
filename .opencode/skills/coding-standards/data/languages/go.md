# Go

- **Formatter**: `gofmt`
- **Indent**: tabs (8 display)
- **Naming**: `camelCase` unexported, `CamelCase` exported; package names short
  lowercase
- **Error handling**: `(T, error)` returns; explicit `err != nil`; no `panic`
  for expected conditions
- **Concurrency**: goroutines, channels, `sync`
- **Feature gate**: build tags

## Guidance

- Let `gofmt` own formatting (tabs, line length) — do not fight it.
- Handle every error explicitly; use `errors.Is`/`errors.As` for
  unwrapping; never `_ = err` on fallible calls.
- Use `defer` for resource teardown (`Close()`, unlock) regardless of return
  path; account for goroutine lifecycles to avoid leaks.
- Use `sync.Mutex` / `RWMutex`, channels, or `atomic` — GC is not
  synchronization.
- Prefer small interfaces, meaningful errors (wrapped with context), and clean
  naming; run `golint`/`staticcheck` before committing.