# TypeScript

- **Formatter**: `prettier`
- **Indent**: 2 spaces
- **Naming**: `camelCase`, `PascalCase` interfaces/types/classes
- **Error handling**: typed errors / discriminated unions; **no `any`**
- **Concurrency**: `async`/`await`, Promises, Workers
- **Feature gate**: env flags / bundler / `tsconfig`

## Guidance

- Prefer explicit types over implicit/`any`; model unions and control flow with
  discriminated unions and `type`/`interface` narrowing.
- Prefer `unknown` over `any` where a value is genuinely dynamic; use type
  guards for narrowing.
- Use typed errors (`class XError extends Error`) or result unions instead of
  `any`-typed `catch` handlers; no bare `catch {}`.
- Keep `strict: true`-style compiler settings in mind: handle `null`/`undefined`
  explicitly.
- Keep components/functions small and pure; validate runtime input at the
  boundary. Run `prettier`, `eslint`, and `tsc --noEmit` before committing.