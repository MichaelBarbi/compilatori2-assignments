; ModuleID = '../test/Loop.ll'
source_filename = "../test/Loop.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@g = dso_local global i32 0, align 4

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @g_incr(i32 noundef %0) #0 {
  %2 = load i32, ptr @g, align 4
  %3 = add nsw i32 %2, %0
  store i32 %3, ptr @g, align 4
  %4 = load i32, ptr @g, align 4
  ret i32 %4
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @loop(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %13, %3
  %.01 = phi i32 [ %0, %3 ], [ %14, %13 ]
  %.0 = phi i32 [ %0, %3 ], [ %.1, %13 ]
  %5 = icmp slt i32 %.01, %1
  br i1 %5, label %6, label %15

6:                                                ; preds = %4
  %7 = call i32 @g_incr(i32 noundef %2)
  br label %8

8:                                                ; preds = %10, %6
  %.1 = phi i32 [ %.0, %6 ], [ %11, %10 ]
  %9 = icmp sle i32 0, 10
  br i1 %9, label %10, label %12

10:                                               ; preds = %8
  %11 = add nsw i32 %.1, 1
  br label %8, !llvm.loop !6

12:                                               ; preds = %8
  br label %13

13:                                               ; preds = %12
  %14 = add nsw i32 %.01, 1
  br label %4, !llvm.loop !8

15:                                               ; preds = %4
  %16 = load i32, ptr @g, align 4
  %17 = add nsw i32 0, %16
  ret i32 %17
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 19.1.7 (/home/runner/work/llvm-project/llvm-project/clang cd708029e0b2869e80abe31ddb175f7c35361f90)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
