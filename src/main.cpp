// 占位入口：只是为了验证「头文件路径 + OpenMP + 可执行文件」这条链路是通的。
// Aufgabe 7 写自己的命令行入口时，直接用你的 src/main.cpp 覆盖它即可。
#include <cstdio>

#include <omp.h>

#include "border/BorderPolicy.h"  // 验证 target_include_directories 生效

int main() {
    std::printf("OpenMP 最大线程数 = %d\n", omp_get_max_threads());
    std::puts("MiniCV 构建成功：include/ 能找到，OpenMP 已链接。");
    return 0;
}
