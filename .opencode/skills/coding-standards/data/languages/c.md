# C

* **Formatter**: `clang-format` (+ `indent -kr -i8`)

* **Indent**: tabs (8)

* **Naming**: `snake_case` for identifiers; global symbols descriptive

* **Error handling**: return codes / `NULL` / `ERR_PTR` sentinels; `goto` cleanup on failure paths

* **Concurrency**: `mutex` / atomics; manual lifetime management

* **Feature gate**: `#ifdef` / `IS_ENABLED` style; annotate non-trivial `#endif`

## Guidance

* Pair every allocation/acquire with a matching release on **every** path,
  including early returns; centralize cleanup with descriptive `goto`
  labels (`out_free_*`, `err_*`) used only for cleanup.

* Use `bool` from `<stdbool.h>` with `true`/`false`, not `1`/`0` integers.

* **Check pointers before every dereference**: validate `NULL` at function
  entry, right after `malloc`/`calloc`/`realloc`, and before following
  external handles; on failure return a clear error code, never dereference a
  nil/dangling pointer.

* Make function-like macros `static inline`; wrap multi-statement macros in
  `do { … } while (0)`; parenthesize macro parameters; never write macros that
  alter control flow or are used as l-values.

* Use `static` for file-local functions/variables; keep exported symbols few
  and descriptive.

* Do not hide a directly-accessible type behind an opaque typedef.

* Prefer `WARN*`-style recovery over `BUG()`/`abort()` for unexpected input;
  use `BUILD_BUG_ON` for zero-cost compile-time invariants.

* Follow Linux K\&R style: opening brace at end of line for statements, closing
  brace on its own line; one space around binary operators and after flow
  keywords; no space inside parentheses.

* **File header (lines 1-2)**: start the file with a short comment stating its
  purpose, e.g. `/* matrix_ops.c — dense matrix multiply and LU factorization. */`,
  plus any required `SPDX-License-Identifier` tag.

