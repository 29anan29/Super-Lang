# Ruby

- **Formatter**: `rubocop`
- **Indent**: 2 spaces
- **Naming**: `snake_case`, `CamelCase` classes/modules,
  `SCREAMING_SNAKE_CASE` constants
- **Error handling**: exceptions; `rescue`/`ensure`
- **Concurrency**: threads (Mutex/Queue); mostly request-scoped
- **Feature gate**: — (feature flags via config)

## Guidance

- Prefer expressive, minimialist Ruby: small methods, blocks, and
  `each`/map over manual loops; keep classes cohesive.
- Use exceptions with meaningful custom error classes; `rescue` narrowly and
  `ensure` to release resources; never swallow errors with an empty `rescue`.
- Prefer immutable data and no surprises from global state; validate inputs.
- Keep `do...end` for blocks spanning lines, `{}` for single-line.
- Run `rubocop -A` (autocorrect) before committing; no trailing whitespace.