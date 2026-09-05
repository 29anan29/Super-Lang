# scripts/

Small, dependency-free helpers to apply and verify formatting.

| Script | Purpose |
|--------|---------|
| `apply-format.sh` | Run the idiomatic formatter (`gofmt`/`rustfmt`/`clang-format`/`black`/`prettier`/…) on the given files or directories. |
| `check-style.sh` | Dependency-free style lint: flags trailing whitespace, over-long lines, mixed indentation, editor modelines, and missing file headers. Exits non-zero on issues. |

## Format

```bash
sh scripts/apply-format.sh src/
sh scripts/apply-format.sh main.rs model.go parse.c
```

## Verify

```bash
sh scripts/check-style.sh src/          # defaults, width 80, requires header
sh scripts/check-style.sh --skip-header src/   # don't require file comments
sh scripts/check-style.sh --width=100 src/
```

No network calls, no package installs.