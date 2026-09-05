# data/

Bundled, plug-and-play formatting/editor assets referenced by this skill.

| File | Applies to | Notes |
|------|-----------|-------|
| `.editorconfig` | All languages | Universal editor defaults; copy to project root. |
| `clang-format` | C / C++ | `clang-format` config (tabs, 8-wide, K&R). Copy and rename `.clang-format`. |
| `rustfmt.toml` | Rust | Optional; rustfmt defaults are already idiomatic. |
| `languages/` | 17 languages | Per-language convention docs (`<lang>.md`) read on demand (see index in `SKILL.md`). |

Install any of these into your project as needed:

```bash
cp data/.editorconfig ../../.editorconfig
cp data/clang-format ../../.clang-format
cp data/rustfmt.toml ../../rustfmt.toml
```

Paths above are relative to a project-local install of the skill.