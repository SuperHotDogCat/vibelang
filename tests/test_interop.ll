; ModuleID = 'novus'
source_filename = "novus"

%Vector = type { ptr, i64, i64 }
%HashSet = type { ptr, i64, i64 }
%HashMap = type { ptr, ptr, i64, i64 }

@0 = private unnamed_addr constant [10 x i8] c"Developer\00", align 1
@1 = private unnamed_addr constant [12 x i8] c"Result: %d\0A\00", align 1

declare ptr @malloc(i64)

declare void @free(ptr)

declare i64 @printf(ptr, ...)

define void @Vector_init(ptr %self, i64 %cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %cap2 = alloca i64, align 8
  store i64 %cap, ptr %cap2, align 4
  %self3 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %Vector, ptr %self3, i32 0, i32 0
  %cap4 = load i64, ptr %cap2, align 4
  %1 = mul i64 %cap4, 8
  %2 = call ptr @malloc(i64 %1)
  store ptr %2, ptr %0, align 8
  %self5 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %Vector, ptr %self5, i32 0, i32 1
  store i64 0, ptr %3, align 4
  %self6 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %Vector, ptr %self6, i32 0, i32 2
  %cap7 = load i64, ptr %cap2, align 4
  store i64 %cap7, ptr %4, align 4
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
  ret void

ifcont:                                           ; preds = %entry
  %self5 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %Vector, ptr %self5, i32 0, i32 0
  %data = load ptr, ptr %3, align 8
  %self6 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %Vector, ptr %self6, i32 0, i32 1
  %size7 = load i64, ptr %4, align 4
  %5 = getelementptr inbounds i64, ptr %data, i64 %size7
  %val8 = load i64, ptr %val2, align 4
  store i64 %val8, ptr %5, align 4
  %self9 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %Vector, ptr %self9, i32 0, i32 1
  %self10 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %Vector, ptr %self10, i32 0, i32 1
  %size11 = load i64, ptr %7, align 4
  %8 = add i64 %size11, 1
  store i64 %8, ptr %6, align 4
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
  %self3 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashSet, ptr %self3, i32 0, i32 0
  %cap4 = load i64, ptr %cap2, align 4
  %1 = mul i64 %cap4, 8
  %2 = call ptr @malloc(i64 %1)
  store ptr %2, ptr %0, align 8
  %self5 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %HashSet, ptr %self5, i32 0, i32 1
  store i64 0, ptr %3, align 4
  %self6 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %HashSet, ptr %self6, i32 0, i32 2
  %cap7 = load i64, ptr %cap2, align 4
  store i64 %cap7, ptr %4, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %whilecond

whilecond:                                        ; preds = %whilebody, %entry
  %i8 = load i64, ptr %i, align 4
  %cap9 = load i64, ptr %cap2, align 4
  %5 = icmp slt i64 %i8, %cap9
  br i1 %5, label %whilebody, label %whileafter

whilebody:                                        ; preds = %whilecond
  %self10 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %HashSet, ptr %self10, i32 0, i32 0
  %buckets = load ptr, ptr %6, align 8
  %i11 = load i64, ptr %i, align 4
  %7 = getelementptr inbounds ptr, ptr %buckets, i64 %i11
  %8 = call ptr @malloc(i64 0)
  store ptr %8, ptr %7, align 8
  %i12 = load i64, ptr %i, align 4
  %9 = add i64 %i12, 1
  store i64 %9, ptr %i, align 4
  br label %whilecond

whileafter:                                       ; preds = %whilecond
  ret void
}

define i64 @HashSet_hash(ptr %self, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %val2 = alloca i64, align 8
  store i64 %val, ptr %val2, align 4
  %val3 = load i64, ptr %val2, align 4
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashSet, ptr %self4, i32 0, i32 2
  %capacity = load i64, ptr %0, align 4
  %1 = srem i64 %val3, %capacity
  ret i64 %1
}

define void @HashSet_add(ptr %self, i64 %val) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %val2 = alloca i64, align 8
  store i64 %val, ptr %val2, align 4
  %h = alloca i64, align 8
  %val3 = load i64, ptr %val2, align 4
  %0 = call i64 @HashSet_hash(ptr %self1, i64 %val3)
  store i64 %0, ptr %h, align 4
  %self4 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %HashSet, ptr %self4, i32 0, i32 1
  %self5 = load ptr, ptr %self1, align 8
  %2 = getelementptr inbounds %HashSet, ptr %self5, i32 0, i32 1
  %size = load i64, ptr %2, align 4
  %3 = add i64 %size, 1
  store i64 %3, ptr %1, align 4
  ret void
}

define void @HashMap_init(ptr %self, i64 %cap) {
entry:
  %self1 = alloca ptr, align 8
  store ptr %self, ptr %self1, align 8
  %cap2 = alloca i64, align 8
  store i64 %cap, ptr %cap2, align 4
  %self3 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashMap, ptr %self3, i32 0, i32 0
  %cap4 = load i64, ptr %cap2, align 4
  %1 = mul i64 %cap4, 8
  %2 = call ptr @malloc(i64 %1)
  store ptr %2, ptr %0, align 8
  %self5 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %HashMap, ptr %self5, i32 0, i32 1
  %cap6 = load i64, ptr %cap2, align 4
  %4 = mul i64 %cap6, 8
  %5 = call ptr @malloc(i64 %4)
  store ptr %5, ptr %3, align 8
  %self7 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %HashMap, ptr %self7, i32 0, i32 2
  store i64 0, ptr %6, align 4
  %self8 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %HashMap, ptr %self8, i32 0, i32 3
  %cap9 = load i64, ptr %cap2, align 4
  store i64 %cap9, ptr %7, align 4
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
  %self4 = load ptr, ptr %self1, align 8
  %0 = getelementptr inbounds %HashMap, ptr %self4, i32 0, i32 0
  %keys = load ptr, ptr %0, align 8
  %self5 = load ptr, ptr %self1, align 8
  %1 = getelementptr inbounds %HashMap, ptr %self5, i32 0, i32 2
  %size = load i64, ptr %1, align 4
  %2 = getelementptr inbounds i64, ptr %keys, i64 %size
  %key6 = load i64, ptr %key2, align 4
  store i64 %key6, ptr %2, align 4
  %self7 = load ptr, ptr %self1, align 8
  %3 = getelementptr inbounds %HashMap, ptr %self7, i32 0, i32 1
  %values = load ptr, ptr %3, align 8
  %self8 = load ptr, ptr %self1, align 8
  %4 = getelementptr inbounds %HashMap, ptr %self8, i32 0, i32 2
  %size9 = load i64, ptr %4, align 4
  %5 = getelementptr inbounds i64, ptr %values, i64 %size9
  %val10 = load i64, ptr %val3, align 4
  store i64 %val10, ptr %5, align 4
  %self11 = load ptr, ptr %self1, align 8
  %6 = getelementptr inbounds %HashMap, ptr %self11, i32 0, i32 2
  %self12 = load ptr, ptr %self1, align 8
  %7 = getelementptr inbounds %HashMap, ptr %self12, i32 0, i32 2
  %size13 = load i64, ptr %7, align 4
  %8 = add i64 %size13, 1
  store i64 %8, ptr %6, align 4
  ret void
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

define void @greet(ptr %name) {
entry:
  %name1 = alloca ptr, align 8
  store ptr %name, ptr %name1, align 8
  ret void
}

define i64 @add_numbers(i64 %a, i64 %b) {
entry:
  %a1 = alloca i64, align 8
  store i64 %a, ptr %a1, align 4
  %b2 = alloca i64, align 8
  store i64 %b, ptr %b2, align 4
  %a3 = load i64, ptr %a1, align 4
  %b4 = load i64, ptr %b2, align 4
  %0 = add i64 %a3, %b4
  ret i64 %0
}

define i64 @novus_main() {
entry:
  call void @greet(ptr @0)
  %res = alloca i64, align 8
  %0 = call i64 @add_numbers(i64 5, i64 7)
  store i64 %0, ptr %res, align 4
  %res1 = load i64, ptr %res, align 4
  %1 = call i64 (ptr, ...) @printf(ptr @1, i64 %res1)
  ret i64 0
}
