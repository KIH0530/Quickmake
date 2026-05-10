# Quickmake

A command-line tool for quickly generating Makefiles, designed specifically for C/C++ projects.

## Features

- Supports multiple compilers: gcc, g++, clang, clang++
- Chinese charset support: Automatic GBK/UTF-8 encoding conversion
- One-click generation of standard Makefiles
- Simple command-line interface

## Usage

```bash
# Generate default Makefile (gcc compiler)
quickmake.exe -filename Makefile

# Generate Makefile with Chinese charset support
quickmake.exe -filename Makefile -mode cn -cc gcc

# Use g++ compiler
quickmake.exe -filename Makefile -cc g++
```

## Command Line Arguments

| Argument | Description | Values | Default |
|----------|-------------|--------|--------|
| `-filename` | Specify output filename | Any filename | Makefile |
| `-mode` | Charset mode | cn, en | en |
| `-cc` | Compiler selection | gcc, g++, clang, clang++ | gcc |

## Compiler Support

| Compiler | Chinese Mode Support | Notes |
|----------|---------------------|-------|
| gcc | ✓ | Supports -fexec-charset/-finput-charset |
| g++ | ✓ | Supports -fexec-charset/-finput-charset |
| clang | ✗ | Does not support charset parameters |
| clang++ | ✗ | Does not support charset parameters |

## Generated Makefile Example

```makefile
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -fexec-charset=GBK -finput-charset=UTF-8
LDFLAGS := -lm

app: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f app.exe
```

## Compilation

```bash
# Compile using existing Makefile
make

# Or compile directly
gcc -o quickmake.exe quick-make.c
```

## Notes

1. `cn` mode only works with gcc/g++, clang does not support charset parameters
2. Default target name is `app`, source file is `main.c` or `main.cpp`
3. Generated Makefile uses Tab indentation, ensure your editor is configured correctly

## License

MIT License
