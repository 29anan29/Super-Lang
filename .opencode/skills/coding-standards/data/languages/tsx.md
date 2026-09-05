# TSX / React

- **Formatter**: `prettier`
- **Indent**: 2 spaces
- **Naming**: `PascalCase` components; `camelCase` props/utils/hooks
- **Error handling**: as TypeScript plus React error boundaries for the UI
- **Concurrency**: async; render/update concurrency (Suspense, transitions)
- **Feature gate**: env figures / feature flags

## Guidance

- Follow TypeScript conventions (see `ts.md`) plus React idioms: prefer
  function components and hooks; keep components small and focused.
- Model props with explicit `interface`/`type`; do not use `any` on props.
- Extract pure logic/hooks out of render bodies; keep effects minimal and
  cleanup-aware.
- Use error boundaries to keep the UI from crashing on expected input errors;
  show helpful, localized fallbacks.
- Theming/labels and user-visible strings must not be broken across lines.