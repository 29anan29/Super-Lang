# C++

- **Formatter**: `clang-format`
- **Indent**: 2–4 spaces (per project)
- **Naming**: `snake_case` variables/functions, `PascalCase` types,
  `SCREAMING_SNAKE_CASE` constants
- **Error handling**: exceptions or typed `Result`; RAII and smart pointers
- **Concurrency**: `std::thread` / `std::mutex` / `std::atomic`
- **Feature gate**: `#ifdef` / `constexpr`

## Guidance

- Prefer RAII (`std::unique_ptr`/`shared_ptr`, containers, scope guards) over
  raw `new`/`delete`; release resources exactly once on every path.
- Keep `constexpr` and `const` pervasive; use `namespace` and feature-test
  macros for portability.
- Use the C++ standard library algorithms/containers instead of hand-rolled
  loops where idiomatic.
- Keep `unsafe`-style reinterpret/low-level casts minimal and documented.
- **Check pointers/nullable references before dereferencing** (`std::unique_ptr`,
  raw pointers, `std::optional`): validate on entry and right after allocation;
  fail fast instead of dereferencing the empty/null case.
- Group `#include`s clearly; avoid circular dependency cycles.
- Operator/user-visible strings must not be split across lines.
- **File header (lines 1-2):** a short comment stating the file's purpose, plus
  any required license/`SPDX` tag.