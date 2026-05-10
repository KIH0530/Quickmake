// Fast Makefile Generator for C/C++
// Support: gcc g++ clang clang++
// Charset fix only works for gcc/g++ (Windows GBK)
// Clang does NOT support -fexec-charset / -finput-charset
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Compiler configuration structure
typedef struct
{
    const char *cc_name;
    const char *base_cflags;
    const char *cn_charset_flags;
    bool        support_cn_mode;
    bool        is_cpp_compiler;
} CompilerCfg;

// Predefined compiler list (easy to extend)
static CompilerCfg compilers[] =
{
    {"gcc",     "-Wall -Wextra -Wpedantic", " -fexec-charset=GBK -finput-charset=UTF-8", true,  false},
    {"g++",     "-Wall -Wextra -Wpedantic", " -fexec-charset=GBK -finput-charset=UTF-8", true,  true},
    {"clang",   "-Wall -Wextra -Wpedantic", "",                                         false, false},
    {"clang++", "-Wall -Wextra -Wpedantic", "",                                         false, true}
};

#define COMPILER_COUNT (sizeof(compilers) / sizeof(compilers[0]))
#define MAX_PATH_LEN 256

int main(int argc, char *argv[])
{
    char mode[10] = {0};
    char cc_sel[10] = "gcc";
    char target[30] = "app";
    char src_file[30] = "main.c";
    char src_file_cpp[30] = "main.cpp";
    bool is_compiler_found = false;
    char makefile[MAX_PATH_LEN] = "Makefile";

    // Show usage if no arguments
    if (argc < 2)
    {
        fprintf(stderr, "Error: Insufficient arguments!\n");
        fprintf(stderr, "Usage: %s -filename <Makefile_name> [-mode cn/en] [-cc gcc/g++/clang/clang++]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse command line arguments with strict error checking
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-filename") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Error: -filename requires a output filename argument!\n");
                return EXIT_FAILURE;
            }
            strncpy(makefile, argv[++i], sizeof(makefile) - 1);
            makefile[sizeof(makefile) - 1] = '\0';
        }
        else if (strcmp(argv[i], "-mode") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Error: -mode requires 'cn' or 'en' argument!\n");
                return EXIT_FAILURE;
            }
            strncpy(mode, argv[++i], sizeof(mode) - 1);
            mode[sizeof(mode) - 1] = '\0';
        }
        else if (strcmp(argv[i], "-cc") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Error: -cc requires a compiler name argument!\n");
                return EXIT_FAILURE;
            }
            strncpy(cc_sel, argv[++i], sizeof(cc_sel) - 1);
            cc_sel[sizeof(cc_sel) - 1] = '\0';
        }
        else
        {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            fprintf(stderr, "Valid options: -filename, -mode, -cc\n");
            return EXIT_FAILURE;
        }
    }

    // Match selected compiler
    CompilerCfg *cfg = &compilers[0];
    for (int i = 0; i < COMPILER_COUNT; ++i)
    {
        if (strcmp(cc_sel, compilers[i].cc_name) == 0)
        {
            cfg = &compilers[i];
            is_compiler_found = true;
            break;
        }
    }

    if (!is_compiler_found) {
        fprintf(stderr, "Warning: Compiler '%s' not found. Falling back to gcc.\n", cc_sel);
    }

    // Open Makefile for writing
    FILE *fp = fopen(makefile, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Failed to create file '%s'\n", makefile);
        perror("Details");
        return EXIT_FAILURE;
    }

    // Build final CFLAGS dynamically with buffer overflow protection
    char final_cflags[256] = {0};
    if (strlen(cfg->base_cflags) >= sizeof(final_cflags))
    {
        fprintf(stderr, "Error: Compiler flags too long, buffer overflow risk!\n");
        fclose(fp);
        return EXIT_FAILURE;
    }
    strcpy(final_cflags, cfg->base_cflags);

    // Add charset flags only for cn mode & supported compiler
    if (strcmp(mode, "cn") == 0 && cfg->support_cn_mode)
    {
        if (strlen(final_cflags) + strlen(cfg->cn_charset_flags) >= sizeof(final_cflags))
        {
            fprintf(stderr, "Error: Too many flags, buffer overflow detected!\n");
            fclose(fp);
            return EXIT_FAILURE;
        }
        strcat(final_cflags, cfg->cn_charset_flags);
    } else {
        printf("Warning: cn mode is not supported by this compiler\n");
    }

    // Write Makefile content with error checking for each write
    if (fprintf(fp, "CC := %s\n", cfg->cc_name) < 0 ||
        fprintf(fp, "CFLAGS := %s\n", final_cflags) < 0 ||
        fprintf(fp, "LDFLAGS := -lm\n\n") < 0)
    {
        fprintf(stderr, "Error: Failed to write Makefile content\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (cfg->is_cpp_compiler)
    {
        strcpy(src_file, src_file_cpp);
    }

    if (fprintf(fp, "%s: %s\n", target, src_file) < 0 ||
        fprintf(fp, "\t$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)\n\n") < 0 ||
        fprintf(fp, "clean:\n") < 0 ||
        fprintf(fp, "\trm -f %s.exe\n", target) < 0)
    {
        fprintf(stderr, "Error: Failed to write Makefile rules\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Close file and verify success
    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Error: Failed to close file properly\n");
        return EXIT_FAILURE;
    }

    printf("Success: Makefile '%s' generated correctly.\n", makefile);
    return EXIT_SUCCESS;
}
