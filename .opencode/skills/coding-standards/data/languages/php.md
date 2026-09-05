# PHP

- **Formatter**: `php-cs-fixer` / Laravel `pint`
- **Indent**: 4 spaces (PSR-12)
- **Naming**: `snake_case`/`camelCase` (framework-dependent), `CamelCase` classes
- **Error handling**: exceptions; nullable returns; `strict_types`
- **Concurrency**: — (mostly request-scoped)
- **Feature gate**: composer / env config

## Guidance

- Declare `declare(strict_types=1)`; use typed parameters/returns and nullable
  types for null-safety.
- Throw and catch domain exceptions; never `catch (...) {}` silently;
  release/close resources (PDO, streams) with `finally`/`try-finally`.
- Follow PSR-12 (4-space indent, braces, spacing) and the framework's
  conventions (Laravel etc.); prefer dependency injection over globals.
- Validate external input at the boundary; keep methods small and
  single-purpose. Run `php-cs-fixer`/`pint` before committing.