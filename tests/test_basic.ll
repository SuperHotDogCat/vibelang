; ModuleID = 'novus'
source_filename = "novus"

define i64 @main() {
entry:
  %x = alloca i64, align 8
  store i64 10, ptr %x, align 4
  %y = alloca i64, align 8
  store i64 20, ptr %y, align 4
  %z = alloca i64, align 8
  %x1 = load i64, ptr %x, align 4
  %y2 = load i64, ptr %y, align 4
  %0 = mul i64 %y2, 2
  %1 = add i64 %x1, %0
  store i64 %1, ptr %z, align 4
  %z3 = load i64, ptr %z, align 4
  %2 = icmp eq i64 %z3, 50
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  ret i64 0

else:                                             ; preds = %entry
  ret i64 1
}
