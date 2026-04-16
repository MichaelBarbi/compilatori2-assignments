; ModuleID = 'testSR.ll'
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
  %14 = load i32, ptr %2, align 4   ; k = 10
  %15 = shl i32 %14, 3    ; = k * 8
  %16 = sub i32 0, %15    ; k1 = k * -8
  store i32 %16, ptr %3, align 4
  %17 = load i32, ptr %2, align 4
  %18 = shl i32 %17, 3
  %19 = add i32 %18, %17
  %20 = sub i32 0, %19
  store i32 %20, ptr %4, align 4
  store i32 160, ptr %5, align 4
  %21 = load i32, ptr %5, align 4
  %22 = shl i32 %21, 4
  store i32 %22, ptr %6, align 4
  %23 = load i32, ptr %5, align 4
  %24 = shl i32 %23, 4
  %25 = add i32 %24, %23
  store i32 %25, ptr %7, align 4
  %26 = load i32, ptr %5, align 4
  %27 = shl i32 %26, 4
  %28 = sub i32 %27, %26
  store i32 %28, ptr %8, align 4
  %29 = load i32, ptr %5, align 4
  %30 = shl i32 %29, 4
  %31 = add i32 %29, %29
  %32 = add i32 %30, %31
  store i32 %32, ptr %9, align 4
  %33 = load i32, ptr %5, align 4
  %34 = shl i32 %33, 4
  %35 = add i32 %33, %33
  %36 = sub i32 %34, %35
  store i32 %36, ptr %10, align 4
  %37 = load i32, ptr %5, align 4
  %38 = lshr i32 %37, 5
  store i32 %38, ptr %11, align 4
  store i32 80, ptr %12, align 4
  %39 = load i32, ptr %12, align 4
  %40 = ashr i32 %39, 2
  store i32 %40, ptr %13, align 4
  %41 = load i32, ptr %13, align 4
  %42 = ashr i32 %41, 1
  %43 = sub i32 0, %42
  store i32 %43, ptr %13, align 4
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
