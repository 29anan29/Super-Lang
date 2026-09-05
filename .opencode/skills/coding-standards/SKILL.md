---
name: "coding-standards"
description: "A cross-language engineering coding standard guiding AI coding agents when writing, reviewing, or refactoring code. Invoke when the user asks for clean, consistent, maintainable, idiomatic code, or code review. Covers C, C++, Rust, Go, Java, Kotlin, JavaScript, TypeScript, TSX and more."
---

# Engineering Coding Standards

These standards produce code that is easy to read, reason about, and review,
across many languages: C, C++, Rust, Go, Java, Kotlin, JavaScript,
TypeScript, TSX/React, Python, C#/.NET, Swift, PHP, Ruby, Dart, Scala,
Zig, and more. They reflect widely accepted, reviewer-friendly conventions:
keep it simple, be explicit, and stay consistent.

Principles are grouped below. Items marked **hard** are mandatory for any
submitted work; items marked **soft** are strong recommendations.

When a specific language has an official style guide or default formatter
(see [Automated formatting](#9-automated-formatting)) or formatting rule
(see [Language conventions](#language-conventions)), that official style
takes precedence over the general guidance here for conflicting details.

---

## 1 Indentation

- Use a consistent indentation unit. **Prefer tabs set to 8 columns by
  default**; only a language whose official formatter mandates fewer spaces
  (2/4) uses that instead. Never mix tabs and spaces, and follow the official
  style when it disagrees (see the [Language conventions](#language-conventions)
  table).
- Rewrite code that nests more than ~3 levels deep; do not widen the
  indentation to accommodate nesting. Deep nesting is a design smell.
- One statement per line. Do not put multiple assignments or statements on a
  single line to save space.
- Python and other significant-whitespace languages rely on indentation for
  grouping; keep block levels uniform — no stray spaces or tabs.

## 2 Line Length & Strings

- Keep lines reasonably short (commonly up to 80-100 columns; the notorious
  exceptions like Go's style are covered by `gofmt`).
- Break overlong statements into sensible pieces; indent continuations clearly
  and consistently (commonly aligned under the opening parenthesis).
- **Never break user-visible strings** (log messages, error strings, UI text).
  Splitting them breaks searching/grepping and localization.

## 3 Braces & Spacing

### Braces
- Use a consistent brace style. The widely used, reviewer-friendly style is
  K&R: the **opening brace at the end of the line** for statement blocks
  (`if`/`for`/`while`/`switch`), the closing brace on its own line.
- Keep multi-line conformations compact: `} else {`, `} while (…)`, etc.
- For single statements, braces are optional; if **any** branch of a
  conditional or any iteration body needs braces, use them on **all** branches
  of that construct for symmetry.
- The per-language dependent openings: brace-on-same-line is idiomatic in C,
  C++, Go, Java, Kotlin, JS/TS, C#, PHP; **Python uses indentation, not
  braces**; Ruby pairs `do…end`; Scala uses `{…}` block expressions.

```c
	if (condition) {
		do_this();
		do_that();
	} else if (other) {
		…;
	} else {
		otherwise();
	}

	while (condition) {
		if (test)
			do_something();
	}
```

### Spacing
- Put a space after flow-control keywords (`if`, `switch`, `for`, `while`,
  `do`, `case`), but **not** after call-like keywords/operators
  (`sizeof`, `typeof`, unary `&`/`*`/`!`).
- No space just inside parentheses: `sizeof( x )` is wrong.
- One space around binary operators and the ternary `?:`.
- No space between a prefix/postfix `++` / `--` and its operand.
- No space around member-access operators `.` and `->` (or `::`).
- **Never leave trailing whitespace** at end of lines.

## 4 Naming

- Local variables: short and to the point (`i` for loop counters, `tmp` for
  throwaway values). Do not over-name obvious locals.
- Globals and public symbols: descriptive. A public function that counts
  active users should be `count_active_users`, never `cntusr` or `foo`.
- **No Hungarian notation** (encoding the type into the name). Let the
  language/compiler carry type information; rely on real types, generics, and
  IDE tooling instead.
- Follow the language naming conventions in the
  [Language conventions](#language-conventions) table (e.g. Go `camelCase`/`CamelCase`,
  Python `snake_case` + `CamelCase` classes, Java/Kotlin/JS/TS `camelCase` +
  `PascalCase` types, C#/C++/Swift/UPPER_SNAKE constants).
- For TS/TSX, prefer explicit types over `any`; keep interfaces/type aliases
  focused. For JS, prefer `const` over `let` unless rebinding is required.
- Avoid new usage of `master/slave` and `blacklist/whitelist` terminology;
  prefer `{primary,main}/{secondary,replica}` and `denylist/allowlist`
  (or platform/language-preferred terms).

### Variable naming rules

- **Locals are short and meaningful.** Prefer `i`/`idx`/`j` for loop counters,
  `tmp`/`buf`/`len` for throwaways — never opaque names like `x1`, `data`,
  `thing`, or `foo`. Abbreviate only for obvious, tightly-scoped counters.
- **One concept, one name.** Reuse the same identifier for the same concept;
  do not introduce near-duplicates (`user`, `userObj`, `tempUser`).
- **Encode units/roles only where it removes ambiguity**, e.g. `timeout_ms`,
  `buf_len`, `rx`/`tx`, `off_begin`/`off_end`. Do **not** encode types
  (Hungarian) — `strCount`, `arrUsers`, `intN` are banned.
- **Scope scales name length.** A one-line local can be `i`; a widely-shared
  global or public symbol must be descriptive (`count_active_users`, never
  `cntusr`).
- Match the language case convention (see the
  [Language conventions](#language-conventions) index): `snake_case`,
  `camelCase`, `CamelCase` types, `SCREAMING_SNAKE_CASE` constants.
- Constants: `SCREAMING_SNAKE_CASE`; private/package symbols use `_x` or
  `x` per language; booleans read as predicates (`is_open`, `has_lock`,
  `*_present`).

## 5 Type Abstractions

- Prefer explicit, self-describing types (e.g. `struct Account *a` over an
  opaque `acc_t`). Do not create typedefs purely for convenience.
- Use the language's own kind of type abstraction where it adds clarity or
  safety, not as decoration:
  - C/C++: `typedef`/`using` for meaningful aliases only.
  - Rust: generics, `type` aliases, traits.
  - Java/Kotlin/C#/Swift: `interface`/`protocol`/`enum`.
  - TS/TSX: `interface`/`type`, generics, `discriminated union`.
  - Python: type hints + `dataclass`/`TypedDict`.

## 6 Functions & Scope

- Keep functions short, focused, and responsible for **one thing**.
- If a function exceeds roughly a screen or needs more than ~5-10 locals,
  split it into helper functions with descriptive names.
- Declare signatures with meaningful parameter names, not just types.
- Do not use unnecessary `extern` (C) or `export`/`pub` noise where the
  symbol is only used locally — keep names/scope as tight as the language
  allows (`private`/`static`/`pub(crate)`/module `-` visibility).

## 7 Centralized Control Flow & Cleanup

- When a function can exit from many points and shared cleanup is needed,
  centralize it rather than duplicating it at every exit.
- C-style: descriptive `goto` labels (`out_free_*`, `err_*`) only for cleanup.
- Go-style / C#-style: use `defer`/`using` for resource teardown regardless of
  return path.
- Rust/Python/C++-style: rely on RAII, `Drop`, context managers (`with`),
  and smart pointers over manual cleanup.
- Kotlin-style: `use{}`/`close()`/`finally`; Swift-style: `defer{}`.
- Beware of partial-failure cleanup bugs: each resource must be released
  exactly once, even when earlier steps failed.

## 8 Comments

- Comment **WHAT** (purpose) and **WHY** (rationale), not **HOW**
  (mechanism). If the mechanism is not obvious, improve the code first.
- Avoid excessive comments inside function bodies; prefer a short header that
  states what and why.
- Use the multi-line comment style favored by the language (a leading
  `*` column for C-family):

```c
	/*
	 * Describe the purpose and rationale here,
	 * one idea per paragraph.
	 */
```

- For public APIs, use the language/ecosystem's doc comment convention
  (Rust `///`, Go `//`, JS/TS `JSDoc`, Python docstrings, Java/Kotlin/C#/Swift
  `///`/`/** */`). Avoid boilerplate that merely repeats the signature.
- **File header (lines 1-2).** Start every source file with a short comment
  that states what the file is/does at a glance, so a reader knows its purpose
  before reading code:

```c
	/*
	 * matrix_ops.c — dense matrix multiply and LU factorization.
	 */
```

  Put a required license tag (`SPDX-License-Identifier: …`) directly above or
  below it as the project dictates.
- **Comment in blocks, not line-by-line.** Explain a cohesive piece — a
  function, a struct, an algorithm — with one multi-line comment placed above
  it. Do not scatter isolated one-line asides through the body. Write several
  lines explaining a fragment together, never one terse line per statement:

```c
	/*
	 * Accumulate partial products into the accumulator row.
	 * Offsets are scaled by 16 for fixed-point; see layout in
	 * the struct below. Rows must already be zero-initialized.
	 */
	for (j = 0; j < k; j++)
		acc[i * k + j] += a[i * lda] * b[j * ldb];
```

## 9 Automated Formatting

- Adopt the language's canonical formatter and run it before committing:
  - C/C++: `clang-format`;  Go: `gofmt`;  Rust: `rustfmt`.
  - Java: `google-java-format` (or Spotless);  Kotlin: `ktlint`;
    C#/.NET: `dotnet format` / `csharpier`.
  - JS/TS/TSX: `prettier`;  Python: `black`;  Swift: `swift-format`.
  - PHP: `php-cs-fixer` / Laravel `pint`;  Ruby: `rubocop`;
    Dart: `dart format`;  Scala: `scalafmt`;  Zig: `zig fmt`.
- Use linters/analyzers for stylistic and correctness feedback:
  `clang-tidy`, `cargo clippy`, `golint/staticcheck`, `eslint`,
  `pylint/ruff`, `pylint`, `spotbugs`, etc.
- Version-control diffs should contain **no formatting-only noise** beyond the
  change at hand.

## 10 Memory, Ownership & Resource Management

- Be deliberate about ownership, lifetime, and teardown of every resource.
  - Rust: leverage ownership, borrowing, lifetimes, and `Drop`; avoid raw
    pointers and `unsafe` unless unavoidable.
  - Go: account for `Close()`, `defer`, and goroutine lifetimes; avoid leaks.
  - C: pair each allocation/acquire with a matching release on **every** path.
  - C++: prefer smart pointers (`unique_ptr`/`shared_ptr`); no raw
    `new`/`delete` unless necessary.
  - Python/Java/Kotlin/JS/TS/C#/Swift: manage I/O, sockets,
    connections, and native resources explicitly (`with`, `using`, `try/finally`).
- For shared, externally-visible state, use explicit lifecycle management
  (RAII / reference counting / closures) and keep the object alive for as long
  as any user may hold it.
- Do not silently swallow errors; release resources even on early returns.

## 11 Data Structures & Concurrency

- Design concurrent access with clear ownership rules. GC alone is not a
  substitute for synchronization; pair the right primitives with the
  lifecycle contract.
- Prefer language-native/idiomatic primitives over hand-rolled ones:
  - Go: goroutines + channels + `sync`.
  - Rust: `Arc`, `Mutex`, `mpsc`.
  - C++/Java/Kotlin/C#/Swift/Python: `mutex`/`lock`/`synchronized`/`async`.
  - JS/TS: `async`/`await`, `Web Worker`/node `worker_threads`.
- Never mutate shared state without the appropriate synchronization, and make
  the locking/lifetime contract explicit and local.

## 12 Constants, Enums & Idiomatic Abstractions

- Name constants in `SCREAMING_SNAKE_CASE` (C/C++/Rust/Java/K/C#/Go/Python,
  with language-specific nuances; e.g. Java/Kotlin/C# often use it for
  `static final` / `companion object` constants).
- Prefer enums/sealed types for a group of related constants:
  `enum` (C/C++/Java/K/C#/TS), `enum` strictly typed (TS), `enum` (Rust),
  `Enum` (Python), constants in `object` (Kotlin).
- **Prefer functions over macros and stringly-typed values.** In C, make
  function-like macros `static inline`; wrap multi-statement macros in
  `do { … } while (0)`.
- Wrap macro/expression parameters in parentheses to avoid precedence bugs.
- Do not write macros that alter control flow, depend on magic local names, or
  are used as l-values — these are fragile and surprising.

## 13 Logging & Diagnostics

- Use the project's logging facility with proper levels
  (debug/info/warn/error). Structured logging is preferred where idiomatic
  (Go `log/slog`, Rust `tracing`/`log`, Java/Kotlin SLF4J, C# `ILogger`,
  Python `logging`, JS `console`/`pino`).
- Write concise, clear, unambiguous messages; correct spelling matters.
- Match diagnostics to the right component/context (request ID, entity name)
  so they can be correlated.
- Keep the happy path quiet; emit most detail at debug level.

## 14 Performance

- Do not add `inline`/micro-optimization speculatively. Prefer readable code
  and let the optimizer/JIT/compiler work.
- In C/C++/Rust/Zig, avoid premature `inline`/`unsafe`; in GC languages, avoid
  premature object pooling or exotic structures.
- Optimize only after profiling shows a need, and document why.

## 15 Return Values & Error Handling

- Make the return convention follow the name:
  - **Action / imperative** function name → return an **error**-signaling
    result (error code, `Result`, `Optional`, `Throw`/`raised`).
  - **Predicate** function name (`is_*`/`has_*`/`*_present`) → return a
    **boolean** (succeeded semantics).
- Do not mix "error code" and "boolean" semantics for the same function.
- Idiomatic handling per language:
  - Rust: `Result<T, E>` + `?`, `Option`; no `panic!`/`unwrap`/`expect` on the
    failure path of library code.
  - Go: `(value, error)`, handle `err != nil`; no `panic` for expected cases.
  - C: `-Exxx`/`NULL`/`ERR_PTR` sentinels; C++: exceptions or typed `Result`.
  - Java/Kotlin/C#/Swift: exceptions; use `Optional`/`Result`/sealed classes;
    never swallow; do not use exceptions for ordinary control flow.
  - JS/TS: exceptions + `async`//`await`; use typed failures / discriminated
    unions instead of `any` errors; no bare `catch {}`.
  - Python: exceptions + well-defined custom exceptions; do not `except: pass`.
  - PHP/Ruby/Dart/Scala: exceptions + `Result`/`Try`/`Either`/`Option` idiom.
- A function returning a computed value (e.g. a collection or entity) generally
  reports failure via an out-of-band signal (`null`/`None`/`Optional.empty()`
  or `Result`), not a success/failed boolean buried in a numeric value.

## 16 Booleans

- Use a real boolean type (`bool`/`Boolean`/`boolean`) and `true`/`false`, not
  `1`/`0` integers.
- Do not add `!!`-style coercions (Python, JS, etc.); languages with proper
  booleans already produce `true`/`false`.
- Where data has many flags, prefer a single `flags` argument, a bitfield, or
  an enum set over several naked booleans.

## 17 Reuse Standard Library

- Do not reinvent utilities the ecosystem already provides (sorting,
  `min`/`max`, data-structure helpers, string/collection functions).
- Reuse tested standard libraries and idiomatic helpers over hand-rolled
  copies; it is faster, safer, and easier to review.

## 18 Editor / Format Metadata Hygiene

- **Do not** embed editor-specific configuration in source files
  (`-*- mode: c -*-`, `vim: sw=8`, Emacs `Local Variables`). Users have their
  own editor settings.
- Put project-wide formatting rules in `.editorconfig` / formatter config
  files instead (see bundled `data/`).

## 19 Low-Level / Unsafe Constructs

- Prefer safe constructs over `unsafe`/raw pointers when the language offers a
  safe alternative.
- Rust: confine `unsafe` to small, well-documented wrappers with safety
  invariants on the enclosing item.
- C/C++/Zig: prefer portable, well-reviewed code; extract low-level idioms
  into helper functions; document any inline assembly.
- **Check pointers before every dereference** in C/C++/Zig. Validate `NULL` at
  entry points, right after allocation, and before following external handles;
  fail fast with a clear error/return code rather than dereferencing in a nil
  or dangling state. Prefer functions that take pointers to already-validated
  data internally and document the preconditions.
- Java/Kotlin/Python/JS/TS: avoid `sun.misc.Unsafe`/`ctypes`/reflection hacks
  unless truly necessary.

## 20 Feature Gating & Conditional Code

- Prefer runtime/explicit feature checks over scattering preprocessor
  conditionals through source.
  - C/C++: use `IS_ENABLED`-style compile-time booleans / `constexpr` in
    ordinary conditionals; only use `#ifdef` when referenced symbols do not
    exist without it. Annotate non-trivial `#endif` with the condition.
  - Rust: use Cargo features + `cfg` consistently, keeping gating localized.
  - Go: use build tags / feature flags at the module level.
  - Java/Kotlin/C#/Swift: use build config / annotations / `#if` for
    platform-specific code.
  - JS/TS: use feature flags / bundler environment variables / tree-shaking.
  - Python: use environment flags and `TYPE_CHECKING` guards; keep `#if`
    preprocessing out of normal code.
- Delete truly-unused code rather than wrapping it in conditionals.

## 21 Robustness: Fail Safely

- Unexpected-condition handlers must not take down the whole program.
  - C: prefer `WARN*`-style warnings with recovery over hard
    `BUG()`/`abort()`; use compile-time `BUILD_BUG_ON` at zero runtime cost.
  - Go/Rust/Python/Java/Kotlin/JS/TS/C#/Swift: do not crash/abort for expected,
    user- or input-driven conditions — `panic!`/`log.Fatal`/`os.Exit`/`exit()`
    are last resorts; validate inputs instead.

---

## Deliverable Checklist

Check every item before delivering code:

- [ ] Consistent indentation (one unit type, no tabs/spaces mix); no trailing
  whitespace.
- [ ] Lines within the target width; continuations aligned; user-visible
  strings not broken.
- [ ] Consistent brace & spacing style (K&R statement blocks; symmetric braces
  when any branch is multi-statement; indentation grouping for Python).
- [ ] Naming: short locals, descriptive globals/publics, language-native case
  convention, one-concept-one-name, no Hungarian, no
  `master/slave`/`blacklist` terms.
- [ ] No opaque typedefs hiding directly-accessible types; explicit TS types
  (no `any`).
- [ ] Functions short, single-purpose, ≤ ~5-10 locals; meaningful parameter
  names.
- [ ] Cleanup centralized (`goto`/`defer`/RAII/`using`/`with`/`finally`) and
  released exactly once on all paths.
- [ ] **File header (lines 1-2)** states what the file is/does; license tag
  present where required.
- [ ] Comments state what/why, not how; **written in multi-line blocks** over
  cohesive fragments (function/struct), not line-by-line; idiomatic doc
  comments without boilerplate.
- [ ] Formatter/linter pass (gofmt, rustfmt, clang-format, black, prettier,
  google-java-format, ktlint, dotnet format, swift-format, php-cs-fixer,
  rubocop, dart format, scalafmt, zig fmt); no formatting noise.
- [ ] Memory/ownership/teardown correct on every path; shared state
  synchronized with a documented contract.
- [ ] In C/C++/Zig: **pointers checked (`NULL`) before every dereference**;
  entry points and allocation results validated; fail fast with a clear code.
- [ ] Constants/enums/sealed types idiomatic; functions preferred over macros;
  multi-statement macros wrapped.
- [ ] Logging: appropriate levels, concise, context-tagged; quiet happy path.
- [ ] Return convention matches name (action → error/`Result`; predicate →
  boolean); errors handled, not swallowed; no crash/panic/abort for expected
  inputs.
- [ ] Booleans use `bool`/`Boolean`/`boolean` + `true`/`false`.
- [ ] Reuses standard library; no reinventing helpers.
- [ ] Editor modelines absent; formatting rules in `.editorconfig`/config.
- [ ] `unsafe`/low-level code minimized and documented; conditional gating
  localized.
- [ ] Fail-safe error handling for expected inputs; unambiguous cleanup on
  failure paths.

## Language Conventions

This section is a **compact index**. Before writing or reviewing a specific
language, read its dedicated file under `data/languages/<lang>.md` and apply the
recommendations there — official formatters/guides still win on detail.

| Language | Doc | Formatter | Indent |
|----------|-----|-----------|--------|
| C | [`data/languages/c.md`](data/languages/c.md) | `clang-format` | Tabs (8) |
| C++ | [`data/languages/cpp.md`](data/languages/cpp.md) | `clang-format` | 2–4 spaces |
| Rust | [`data/languages/rust.md`](data/languages/rust.md) | `rustfmt` | 4 spaces |
| Go | [`data/languages/go.md`](data/languages/go.md) | `gofmt` | Tabs (8) |
| Java | [`data/languages/java.md`](data/languages/java.md) | `google-java-format` | 4 spaces |
| Kotlin | [`data/languages/kotlin.md`](data/languages/kotlin.md) | `ktlint` | 4 spaces |
| JavaScript | [`data/languages/js.md`](data/languages/js.md) | `prettier` | 2 spaces |
| TypeScript | [`data/languages/ts.md`](data/languages/ts.md) | `prettier` | 2 spaces |
| TSX/React | [`data/languages/tsx.md`](data/languages/tsx.md) | `prettier` | 2 spaces |
| Python | [`data/languages/python.md`](data/languages/python.md) | `black` | 4 spaces |
| C#/.NET | [`data/languages/csharp.md`](data/languages/csharp.md) | `dotnet format` | 4 spaces |
| Swift | [`data/languages/swift.md`](data/languages/swift.md) | `swift-format` | 4 spaces |
| PHP | [`data/languages/php.md`](data/languages/php.md) | `php-cs-fixer`/`pint` | 4 spaces |
| Ruby | [`data/languages/ruby.md`](data/languages/ruby.md) | `rubocop` | 2 spaces |
| Dart | [`data/languages/dart.md`](data/languages/dart.md) | `dart format` | 2 spaces |
| Scala | [`data/languages/scala.md`](data/languages/scala.md) | `scalafmt` | 2 spaces |
| Zig | [`data/languages/zig.md`](data/languages/zig.md) | `zig fmt` | 4 spaces |

### Cross-cutting guidance per family

- **C-like (C, C++, Go, Rust, Zig):** be explicit about ownership and lifetime;
  release resources on every path; keep low-level/unsafe code minimal.
- **JVM/.NET-family (Java, Kotlin, C#):** rely on the platform collections and
  authorities; use `null`-safe idioms (`Optional`, nullable types) and avoid
  swallowing exceptions.
- **Scripting / web (JS, TS, TSX, Python, PHP, Ruby):** keep functions pure and
  short; use the async/await (or generator) model; validate input as the first
  thing each public entry point does; never ignore errors.
- **Swift/Dart/Scala:** prefer value types / immutability where natural, use
  the platform's strongly-typed error/option idioms, and lean on the standard
  concurrency model (actors/isolates/futures).

---

## Repository (skill package)

The installable package is **`coding-standards-cli`** on npm. See
[`cli/README.md`](../../cli/README.md) for installation into Claude Code,
OpenCode, Codex CLI, Cursor, Windsurf, Trae, and the `.agents/skills` standard.

### Bundled tools

- `data/languages/<lang>.md` — per-language conventions (read the relevant one
  before writing that language).
- `scripts/apply-format.sh` — run the canonical formatter on files/dirs.
- `scripts/check-style.sh` — dependency-free style lint (trailing whitespace,
  over-long lines, mixed indentation, editor modelines, file headers); use it
  to self-check before delivering code.