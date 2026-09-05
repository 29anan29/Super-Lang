# JavaScript

- **Formatter**: `prettier`
- **Indent**: 2 spaces
- **Naming**: `camelCase`, `PascalCase` classes/constructors
- **Error handling**: exceptions; `async`/`await`; no bare `catch`
- **Concurrency**: `async`/`await`, Promises, Web Workers / `worker_threads`
- **Feature gate**: env flags / bundler config

## Guidance

- Prefer `const` over `let` unless rebinding is required; avoid `var`.
- Use modern `async`/`await` over raw Promise chains/callbacks for readable
  control flow; reject with `Error` (or typed error subclasses), never bare
  strings.
- Always handle rejection/failures; no empty `catch {}` that swallows errors.
- Keep functions pure and small; avoid deep nesting and implicit mutation of
  arguments.
- Validate external/input data at the boundary (schemas/guards) before use.
- Run `prettier` and `eslint` before committing; no trailing whitespace.