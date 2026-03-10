; ModuleID = 'novus'
source_filename = "novus"

%Point = type { i64, i64 }

define void @Point_set(ptr %self, i64 %x, i64 %y) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %x2 = alloca i64, align 8
  store i64 %x, ptr %x2, align 4
  %y3 = alloca i64, align 8
  store i64 %y, ptr %y3, align 4
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Point, ptr %self4, i32 0, i32 0
  %x5 = load i64, ptr %x2, align 4
  store i64 %x5, ptr %0, align 4
  %self6 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %Point, ptr %self6, i32 0, i32 1
  %y7 = load i64, ptr %y3, align 4
  store i64 %y7, ptr %1, align 4
  ret void
}

define i64 @Point_area(ptr %self) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %self2 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Point, ptr %self2, i32 0, i32 0
  %x = load i64, ptr %0, align 4
  %self3 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %Point, ptr %self3, i32 0, i32 1
  %y = load i64, ptr %1, align 4
  %2 = mul i64 %x, %y
  ret i64 %2
}

define i64 @main() {
entry:
  %p = alloca %Point, align 8
  call void @Point_set(ptr %p, i64 10, i64 20)
  %0 = call i64 @Point_area(ptr %p)
  %1 = icmp eq i64 %0, 200
  br i1 %1, label %then, label %ifcont

then:                                             ; preds = %entry
  ret i64 0

ifcont:                                           ; preds = %entry
  ret i64 1
}
