; ModuleID = 'novus'
source_filename = "novus"

%Vector = type { ptr, i64, i64 }
%HashSet = type { ptr, ptr, i64, i64 }
%HashMap = type { ptr, ptr, i64, i64 }

@0 = private unnamed_addr constant [33 x i8] c"HashSet and HashMap test passed\0A\00", align 1

declare ptr @malloc(i64)

declare void @free(ptr)

declare i64 @printf(ptr, ...)

define void @Vector_init(ptr %self, i64 %cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %cap2 = alloca i64, align 8
  store i64 %cap, ptr %cap2, align 4
  %c = alloca i64, align 8
  %cap3 = load i64, ptr %cap2, align 4
  store i64 %cap3, ptr %c, align 4
  %c4 = load i64, ptr %c, align 4
  %0 = icmp sle i64 %c4, 0
  br i1 %0, label %then, label %ifcont

then:                                             ; preds = %entry
  store i64 10, ptr %c, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %self5 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %Vector, ptr %self5, i32 0, i32 0
  %c6 = load i64, ptr %c, align 4
  %2 = mul i64 %c6, 8
  %3 = call ptr @malloc(i64 %2)
  store ptr %3, ptr %1, align 8
  %self7 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %Vector, ptr %self7, i32 0, i32 1
  store i64 0, ptr %4, align 4
  %self8 = load ptr, ptr %self1, align 8
  %5 = getelementptr inbounds %Vector, ptr %self8, i32 0, i32 2
  %c9 = load i64, ptr %c, align 4
  store i64 %c9, ptr %5, align 4
  ret void
}

define void @Vector_resize(ptr %self, i64 %new_cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %new_cap2 = alloca i64, align 8
  store i64 %new_cap, ptr %new_cap2, align 4
  %new_cap3 = load i64, ptr %new_cap2, align 4
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Vector, ptr %self4, i32 0, i32 2
  %capacity = load i64, ptr %0, align 4
  %1 = icmp sle i64 %new_cap3, %capacity
  br i1 %1, label %then, label %ifcont

then:                                             ; preds = %entry
  ret void

ifcont:                                           ; preds = %entry
  %new_data = alloca ptr, align 8
  %new_cap5 = load i64, ptr %new_cap2, align 4
  %2 = mul i64 %new_cap5, 8
  %3 = call ptr @malloc(i64 %2)
  store ptr %3, ptr %new_data, align 8
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %whilebody, %ifcont
  %i6 = load i64, ptr %i, align 4
  %self7 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %Vector, ptr %self7, i32 0, i32 1
  %size = load i64, ptr %4, align 4
  %5 = icmp slt i64 %i6, %size
  br i1 %5, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %new_data8 = load ptr, ptr %new_data, align 8
  %i9 = load i64, ptr %i, align 4
  %6 = getelementptr inbounds i64, ptr %new_data8, i64 %i9
  %self10 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %Vector, ptr %self10, i32 0, i32 0
  %data = load ptr, ptr %7, align 8
  %i11 = load i64, ptr %i, align 4
  %8 = getelementptr inbounds i64, ptr %data, i64 %i11
  %9 = load i64, ptr %8, align 4
  store i64 %9, ptr %6, align 4
  %i12 = load i64, ptr %i, align 4
  %10 = add i64 %i12, 1
  store i64 %10, ptr %i, align 4
  br label %whilecond

whileafter:                                       ; preds = %whilecond
  %self13 = load ptr, ptr %self1, align 8
  %11 = getelementptr inbounds %Vector, ptr %self13, i32 0, i32 0
  %data14 = load ptr, ptr %11, align 8
  call void @free(ptr %data14)
  %self15 = load ptr, ptr %self1, align 8
  %12 = getelementptr inbounds %Vector, ptr %self15, i32 0, i32 0
  %new_data16 = load ptr, ptr %new_data, align 8
  store ptr %new_data16, ptr %12, align 8
  %self17 = load ptr, ptr %self1, align 8
  %13 = getelementptr inbounds %Vector, ptr %self17, i32 0, i32 2
  %new_cap18 = load i64, ptr %new_cap2, align 4
  store i64 %new_cap18, ptr %13, align 4
  ret void
}

define void @Vector_push(ptr %self, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %val2 = alloca i64, align 8
  store i64 %val, ptr %val2, align 4
  %self3 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Vector, ptr %self3, i32 0, i32 1
  %size = load i64, ptr %0, align 4
  %self4 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %Vector, ptr %self4, i32 0, i32 2
  %capacity = load i64, ptr %1, align 4
  %2 = icmp eq i64 %size, %capacity
  br i1 %2, label %then, label %ifcont

then:                                             ; preds = %entry
  %self5 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %Vector, ptr %self5, i32 0, i32 2
  %capacity6 = load i64, ptr %3, align 4
  %4 = mul i64 %capacity6, 2
  call void @Vector_resize(ptr %self1, i64 %4)
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %self7 = load ptr, ptr %self1, align 8
  %5 = getelementptr inbounds %Vector, ptr %self7, i32 0, i32 0
  %data = load ptr, ptr %5, align 8
  %self8 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %Vector, ptr %self8, i32 0, i32 1
  %size9 = load i64, ptr %6, align 4
  %7 = getelementptr inbounds i64, ptr %data, i64 %size9
  %val10 = load i64, ptr %val2, align 4
  store i64 %val10, ptr %7, align 4
  %self11 = load ptr, ptr %self1, align 8
  %8 = getelementptr inbounds %Vector, ptr %self11, i32 0, i32 1
  %self12 = load ptr, ptr %self1, align 8
  %9 = getelementptr inbounds %Vector, ptr %self12, i32 0, i32 1
  %size13 = load i64, ptr %9, align 4
  %10 = add i64 %size13, 1
  store i64 %10, ptr %8, align 4
  ret void
}

define i64 @Vector_get(ptr %self, i64 %idx) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %idx2 = alloca i64, align 8
  store i64 %idx, ptr %idx2, align 4
  %self3 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Vector, ptr %self3, i32 0, i32 0
  %data = load ptr, ptr %0, align 8
  %idx4 = load i64, ptr %idx2, align 4
  %1 = getelementptr inbounds i64, ptr %data, i64 %idx4
  %2 = load i64, ptr %1, align 4
  ret i64 %2
}

define void @HashSet_init(ptr %self, i64 %cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %cap2 = alloca i64, align 8
  store i64 %cap, ptr %cap2, align 4
  %c = alloca i64, align 8
  %cap3 = load i64, ptr %cap2, align 4
  store i64 %cap3, ptr %c, align 4
  %c4 = load i64, ptr %c, align 4
  %0 = icmp sle i64 %c4, 0
  br i1 %0, label %then, label %ifcont

then:                                             ; preds = %entry
  store i64 10, ptr %c, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %self5 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %HashSet, ptr %self5, i32 0, i32 0
  %c6 = load i64, ptr %c, align 4
  %2 = mul i64 %c6, 8
  %3 = call ptr @malloc(i64 %2)
  store ptr %3, ptr %1, align 8
  %self7 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %HashSet, ptr %self7, i32 0, i32 1
  %c8 = load i64, ptr %c, align 4
  %5 = mul i64 %c8, 1
  %6 = call ptr @malloc(i64 %5)
  store ptr %6, ptr %4, align 8
  %self9 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %HashSet, ptr %self9, i32 0, i32 2
  store i64 0, ptr %7, align 4
  %self10 = load ptr, ptr %self1, align 8
  %8 = getelementptr inbounds %HashSet, ptr %self10, i32 0, i32 3
  %c11 = load i64, ptr %c, align 4
  store i64 %c11, ptr %8, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %whilebody, %ifcont
  %i12 = load i64, ptr %i, align 4
  %c13 = load i64, ptr %c, align 4
  %9 = icmp slt i64 %i12, %c13
  br i1 %9, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %self14 = load ptr, ptr %self1, align 8
  %10 = getelementptr inbounds %HashSet, ptr %self14, i32 0, i32 1
  %used = load ptr, ptr %10, align 8
  %i15 = load i64, ptr %i, align 4
  %11 = getelementptr inbounds i1, ptr %used, i64 %i15
  store i1 false, ptr %11, align 1
  %i16 = load i64, ptr %i, align 4
  %12 = add i64 %i16, 1
  store i64 %12, ptr %i, align 4
  br label %whilecond

whileafter:                                       ; preds = %whilecond
  ret void
}

define void @HashSet_add(ptr %self, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %val2 = alloca i64, align 8
  store i64 %val, ptr %val2, align 4
  %val3 = load i64, ptr %val2, align 4
  %0 = call i1 @HashSet_contains(ptr %self1, i64 %val3)
  br i1 %0, label %then, label %ifcont

then:                                             ; preds = %entry
  ret void

ifcont:                                           ; preds = %entry
  %self4 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %HashSet, ptr %self4, i32 0, i32 0
  %data = load ptr, ptr %1, align 8
  %self5 = load ptr, ptr %self1, align 8
  %2 = getelementptr inbounds %HashSet, ptr %self5, i32 0, i32 2
  %size = load i64, ptr %2, align 4
  %3 = getelementptr inbounds i64, ptr %data, i64 %size
  %val6 = load i64, ptr %val2, align 4
  store i64 %val6, ptr %3, align 4
  %self7 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %HashSet, ptr %self7, i32 0, i32 2
  %self8 = load ptr, ptr %self1, align 8
  %5 = getelementptr inbounds %HashSet, ptr %self8, i32 0, i32 2
  %size9 = load i64, ptr %5, align 4
  %6 = add i64 %size9, 1
  store i64 %6, ptr %4, align 4
  ret void
}

define i1 @HashSet_contains(ptr %self, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %val2 = alloca i64, align 8
  store i64 %val, ptr %val2, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %ifcont, %entry
  %i3 = load i64, ptr %i, align 4
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashSet, ptr %self4, i32 0, i32 2
  %size = load i64, ptr %0, align 4
  %1 = icmp slt i64 %i3, %size
  br i1 %1, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %self5 = load ptr, ptr %self1, align 8
  %2 = getelementptr inbounds %HashSet, ptr %self5, i32 0, i32 0
  %data = load ptr, ptr %2, align 8
  %i6 = load i64, ptr %i, align 4
  %3 = getelementptr inbounds i64, ptr %data, i64 %i6
  %4 = load i64, ptr %3, align 4
  %val7 = load i64, ptr %val2, align 4
  %5 = icmp eq i64 %4, %val7
  br i1 %5, label %then, label %ifcont

whileafter:                                       ; preds = %whilecond
  ret i1 false

then:                                             ; preds = %whilebody
  ret i1 true

ifcont:                                           ; preds = %whilebody
  %i8 = load i64, ptr %i, align 4
  %6 = add i64 %i8, 1
  store i64 %6, ptr %i, align 4
  br label %whilecond
}

define void @HashMap_init(ptr %self, i64 %cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %cap2 = alloca i64, align 8
  store i64 %cap, ptr %cap2, align 4
  %c = alloca i64, align 8
  %cap3 = load i64, ptr %cap2, align 4
  store i64 %cap3, ptr %c, align 4
  %c4 = load i64, ptr %c, align 4
  %0 = icmp sle i64 %c4, 0
  br i1 %0, label %then, label %ifcont

then:                                             ; preds = %entry
  store i64 10, ptr %c, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %self5 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %HashMap, ptr %self5, i32 0, i32 0
  %c6 = load i64, ptr %c, align 4
  %2 = mul i64 %c6, 8
  %3 = call ptr @malloc(i64 %2)
  store ptr %3, ptr %1, align 8
  %self7 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %HashMap, ptr %self7, i32 0, i32 1
  %c8 = load i64, ptr %c, align 4
  %5 = mul i64 %c8, 8
  %6 = call ptr @malloc(i64 %5)
  store ptr %6, ptr %4, align 8
  %self9 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %HashMap, ptr %self9, i32 0, i32 2
  store i64 0, ptr %7, align 4
  %self10 = load ptr, ptr %self1, align 8
  %8 = getelementptr inbounds %HashMap, ptr %self10, i32 0, i32 3
  %c11 = load i64, ptr %c, align 4
  store i64 %c11, ptr %8, align 4
  ret void
}

define void @HashMap_put(ptr %self, i64 %key, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %key2 = alloca i64, align 8
  store i64 %key, ptr %key2, align 4
  %val3 = alloca i64, align 8
  store i64 %val, ptr %val3, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %ifcont, %entry
  %i4 = load i64, ptr %i, align 4
  %self5 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashMap, ptr %self5, i32 0, i32 2
  %size = load i64, ptr %0, align 4
  %1 = icmp slt i64 %i4, %size
  br i1 %1, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %self6 = load ptr, ptr %self1, align 8
  %2 = getelementptr inbounds %HashMap, ptr %self6, i32 0, i32 0
  %keys = load ptr, ptr %2, align 8
  %i7 = load i64, ptr %i, align 4
  %3 = getelementptr inbounds i64, ptr %keys, i64 %i7
  %4 = load i64, ptr %3, align 4
  %key8 = load i64, ptr %key2, align 4
  %5 = icmp eq i64 %4, %key8
  br i1 %5, label %then, label %ifcont

whileafter:                                       ; preds = %whilecond
  %self13 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %HashMap, ptr %self13, i32 0, i32 0
  %keys14 = load ptr, ptr %6, align 8
  %self15 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %HashMap, ptr %self15, i32 0, i32 2
  %size16 = load i64, ptr %7, align 4
  %8 = getelementptr inbounds i64, ptr %keys14, i64 %size16
  %key17 = load i64, ptr %key2, align 4
  store i64 %key17, ptr %8, align 4
  %self18 = load ptr, ptr %self1, align 8
  %9 = getelementptr inbounds %HashMap, ptr %self18, i32 0, i32 1
  %values19 = load ptr, ptr %9, align 8
  %self20 = load ptr, ptr %self1, align 8
  %10 = getelementptr inbounds %HashMap, ptr %self20, i32 0, i32 2
  %size21 = load i64, ptr %10, align 4
  %11 = getelementptr inbounds i64, ptr %values19, i64 %size21
  %val22 = load i64, ptr %val3, align 4
  store i64 %val22, ptr %11, align 4
  %self23 = load ptr, ptr %self1, align 8
  %12 = getelementptr inbounds %HashMap, ptr %self23, i32 0, i32 2
  %self24 = load ptr, ptr %self1, align 8
  %13 = getelementptr inbounds %HashMap, ptr %self24, i32 0, i32 2
  %size25 = load i64, ptr %13, align 4
  %14 = add i64 %size25, 1
  store i64 %14, ptr %12, align 4
  ret void

then:                                             ; preds = %whilebody
  %self9 = load ptr, ptr %self1, align 8
  %15 = getelementptr inbounds %HashMap, ptr %self9, i32 0, i32 1
  %values = load ptr, ptr %15, align 8
  %i10 = load i64, ptr %i, align 4
  %16 = getelementptr inbounds i64, ptr %values, i64 %i10
  %val11 = load i64, ptr %val3, align 4
  store i64 %val11, ptr %16, align 4
  ret void

ifcont:                                           ; preds = %whilebody
  %i12 = load i64, ptr %i, align 4
  %17 = add i64 %i12, 1
  store i64 %17, ptr %i, align 4
  br label %whilecond
}

define i64 @HashMap_get(ptr %self, i64 %key) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %key2 = alloca i64, align 8
  store i64 %key, ptr %key2, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %ifcont, %entry
  %i3 = load i64, ptr %i, align 4
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashMap, ptr %self4, i32 0, i32 2
  %size = load i64, ptr %0, align 4
  %1 = icmp slt i64 %i3, %size
  br i1 %1, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %self5 = load ptr, ptr %self1, align 8
  %2 = getelementptr inbounds %HashMap, ptr %self5, i32 0, i32 0
  %keys = load ptr, ptr %2, align 8
  %i6 = load i64, ptr %i, align 4
  %3 = getelementptr inbounds i64, ptr %keys, i64 %i6
  %4 = load i64, ptr %3, align 4
  %key7 = load i64, ptr %key2, align 4
  %5 = icmp eq i64 %4, %key7
  br i1 %5, label %then, label %ifcont

whileafter:                                       ; preds = %whilecond
  ret i64 0

then:                                             ; preds = %whilebody
  %self8 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %HashMap, ptr %self8, i32 0, i32 1
  %values = load ptr, ptr %6, align 8
  %i9 = load i64, ptr %i, align 4
  %7 = getelementptr inbounds i64, ptr %values, i64 %i9
  %8 = load i64, ptr %7, align 4
  ret i64 %8

ifcont:                                           ; preds = %whilebody
  %i10 = load i64, ptr %i, align 4
  %9 = add i64 %i10, 1
  store i64 %9, ptr %i, align 4
  br label %whilecond
}

define i64 @main() {
entry:
  %map = alloca %HashMap, align 8
  call void @HashMap_init(ptr %map, i64 10)
  call void @HashMap_put(ptr %map, i64 1, i64 100)
  call void @HashMap_put(ptr %map, i64 2, i64 200)
  %0 = call i64 @HashMap_get(ptr %map, i64 1)
  %1 = icmp eq i64 %0, 100
  br i1 %1, label %then, label %ifcont2

then:                                             ; preds = %entry
  %2 = call i64 @HashMap_get(ptr %map, i64 2)
  %3 = icmp eq i64 %2, 200
  br i1 %3, label %then1, label %ifcont

then1:                                            ; preds = %then
  %4 = call i64 (ptr, ...) @printf(ptr @0)
  ret i64 0

ifcont:                                           ; preds = %then
  br label %ifcont2

ifcont2:                                          ; preds = %ifcont, %entry
  ret i64 1
}
