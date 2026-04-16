; ModuleID = './testSR.c'
source_filename = "./testSR.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 10, ptr %2, align 4
  %14 = load i32, ptr %2, align 4
  %15 = mul nsw i32 %14, -8
  store i32 %15, ptr %3, align 4
  %16 = load i32, ptr %2, align 4
  %17 = mul nsw i32 %16, -9
  store i32 %17, ptr %4, align 4
  store i32 160, ptr %5, align 4
  %18 = load i32, ptr %5, align 4
  %19 = mul i32 %18, 16
  store i32 %19, ptr %6, align 4
  %20 = load i32, ptr %5, align 4
  %21 = mul i32 %20, 17
  store i32 %21, ptr %7, align 4
  %22 = load i32, ptr %5, align 4
  %23 = mul i32 %22, 15
  store i32 %23, ptr %8, align 4
  %24 = load i32, ptr %5, align 4
  %25 = mul i32 %24, 18
  store i32 %25, ptr %9, align 4
  %26 = load i32, ptr %5, align 4
  %27 = mul i32 %26, 14
  store i32 %27, ptr %10, align 4
  %28 = load i32, ptr %5, align 4
  %29 = udiv i32 %28, 32
  store i32 %29, ptr %11, align 4
  store i32 80, ptr %12, align 4
  %30 = load i32, ptr %12, align 4
  %31 = sdiv i32 %30, 4
  store i32 %31, ptr %13, align 4
  %32 = load i32, ptr %13, align 4
  %33 = sdiv i32 %32, -2
  store i32 %33, ptr %13, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 19.1.7 (/home/runner/work/llvm-project/llvm-project/clang cd708029e0b2869e80abe31ddb175f7c35361f90)"}
