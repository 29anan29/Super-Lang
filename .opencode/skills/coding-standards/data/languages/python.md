# Python

- **Formatter**: `black`
- **Indent**: 4 spaces (significant whitespace — keep block levels uniform)
- **Naming**: `snake_case` functions/variables, `CamelCase` classes,
  `UPPER_SNAKE` constants, `_leading` private
- **Error handling**: exceptions; define custom exceptions; never `except: pass`
- **Concurrency**: `asyncio`, `threading`, `multiprocessing`
- **Feature gate**: env flags; `TYPE_CHECKING` guards

## Guidance

- Use type hints (PEP 484) plus `dataclass`/`TypedDict` for self-documenting
  structures. Run `mypy`/`pyright` where practical.
- Raise meaningful custom exceptions; catch narrowly; do not silently swallow
  (`except: pass`); release resources with context managers (`with`).
- Prefer `async`/`await` with `asyncio` over threads for I/O concurrency; keep
  locking explicit with `asyncio.Lock`/`threading.Lock`.
- Keep functions short and pure; validate input at the boundary.
- Run `black` and a linter (`ruff`/`pylint`) before committing; no trailing
  whitespace; no `TYPE_CHECKING` imports leaking into runtime scope.