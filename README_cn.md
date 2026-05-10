# Quickmake

快速生成 Makefile 的命令行工具，专为 C/C++ 项目设计。

## 功能特点

- 支持多种编译器：gcc、g++、clang、clang++
- 中文编码支持：自动处理 GBK/UTF-8 编码转换
- 一键生成标准 Makefile
- 简洁的命令行界面

## 使用方法

```bash
# 生成默认 Makefile（gcc 编译器）
quickmake.exe -filename Makefile

# 生成支持中文输出的 Makefile
quickmake.exe -filename Makefile -mode cn -cc gcc

# 使用 g++ 编译器
quickmake.exe -filename Makefile -cc g++
```

## 命令行参数

| 参数 | 说明 | 可选值 | 默认值 |
|------|------|--------|--------|
| `-filename` | 指定输出文件名 | 任意文件名 | Makefile |
| `-mode` | 编码模式 | cn, en | en |
| `-cc` | 编译器选择 | gcc, g++, clang, clang++ | gcc |

## 编译器支持

| 编译器 | 中文模式支持 | 说明 |
|--------|-------------|------|
| gcc | ✓ | 支持 -fexec-charset/-finput-charset |
| g++ | ✓ | 支持 -fexec-charset/-finput-charset |
| clang | ✗ | 不支持中文编码参数 |
| clang++ | ✗ | 不支持中文编码参数 |

## 生成的 Makefile 示例

```makefile
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -fexec-charset=GBK -finput-charset=UTF-8
LDFLAGS := -lm

app: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f app.exe
```

## 编译安装

```bash
# 使用已有的 Makefile 编译
make

# 或者直接编译
gcc -o quickmake.exe quick-make.c
```

## 注意事项

1. `cn` 模式仅对 gcc/g++ 有效，clang 不支持编码参数
2. 默认目标文件名为 `app`，源文件名为 `main.c` 或 `main.cpp`
3. 生成的 Makefile 使用 Tab 缩进，请确保编辑器配置正确

## 许可证

MIT License
