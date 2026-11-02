# BuildX

A simple and extendible build system in C++.

## Introduction

BuildX is a new approach to build systems.

```
.
├── src
│   └── main.cpp
└── build.cpp
```

### `build.cpp`
```C++
#include <buildx/build.hpp>

void bx::build(context& ctx) {
  auto& main = ctx
      .add<executable>("main")
      .file(ctx.path("src") / "main.cpp");

  auto& run = main.run();

  ctx.use<gxx>(std::in_place, gxx::std(23));
  ctx.install(run);
}
```

### `src/main.cpp`
```C++
#include <print>

int main() {
  std::println("Hello, BuildX!");
}
```

### Invoking `bx`,
```bash
$ bx build.cpp
+ g++ compile bx-cache/targets/bx/build.cpp.o
+ g++ link bx-cache/targets/bx/bx
+ running build script
+ g++ compile bx-cache/targets/main/src/main.cpp.o
+ g++ link bx-out/bin/main
+ run main
Hello, BuildX!
```

## Inspirations

This would not be possible if not for hardworking people that came before me.

1. CMake
2. XMake
3. Zig Build
4. nob.h
