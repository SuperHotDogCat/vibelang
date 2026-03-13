# Standard Library Reference

The Novus standard library (`lib/std.nov`) provides essential data structures and system utilities.

## System Utilities

Novus provides direct access to several C standard library functions via `extern fn`.

-   `malloc(size: int) -> void*`: Allocates `size` bytes of memory on the heap.
-   `free(ptr: void*) -> void`: Deallocates memory previously allocated by `malloc`.
-   `printf(fmt: string, ...) -> int`: Prints formatted output to `stdout`.
-   `strlen(s: string) -> int`: Returns the length of a null-terminated string.

## Hashing Functions

-   `hash_int(val: int) -> int`: Returns a hash value for an integer.
-   `hash_float(val: float) -> int`: Returns a hash value for a float.
-   `hash_string(val: string) -> int`: Returns a hash value for a string (using the djb2 algorithm).

## Data Structures

### Vector

A dynamic array that grows automatically.

-   `init(cap: int) -> void`: Initializes the vector with an initial capacity.
-   `push(val: int) -> void`: Appends an element to the end.
-   `get(idx: int) -> int`: Retrieves the element at the specified index.
-   `resize(new_cap: int) -> void`: (Internal) Increases the capacity of the vector.

### HashSet

A collection of unique integers.

-   `init(cap: int) -> void`: Initializes the set with an initial capacity.
-   `add(val: int) -> void`: Adds an element to the set if it's not already present.
-   `contains(val: int) -> bool`: Returns `true` if the element is in the set.

### HashMap

A collection of key-value pairs (integers to integers).

-   `init(cap: int) -> void`: Initializes the map with an initial capacity.
-   `put(key: int, val: int) -> void`: Associates a value with a key.
-   `get(key: int) -> int`: Retrieves the value associated with a key, or `0` if not found.

### Stack

A Last-In, First-Out (LIFO) collection.

-   `init(cap: int) -> void`: Initializes the stack.
-   `push(val: int) -> void`: Pushes an element onto the stack.
-   `pop() -> int`: Removes and returns the top element.
-   `peek() -> int`: Returns the top element without removing it.
-   `is_empty() -> bool`: Returns `true` if the stack is empty.

### Queue

A First-In, First-Out (FIFO) collection using a circular buffer.

-   `init(cap: int) -> void`: Initializes the queue.
-   `push(val: int) -> void`: Adds an element to the rear.
-   `pop() -> int`: Removes and returns the element from the front.
-   `is_empty() -> bool`: Returns `true` if the queue is empty.

### Deque

A double-ended queue.

-   `init(cap: int) -> void`: Initializes the deque.
-   `push_back(val: int) -> void`: Adds an element to the rear.
-   `push_front(val: int) -> void`: Adds an element to the front.
-   `pop_front() -> int`: Removes and returns the element from the front.
-   `pop_back() -> int`: Removes and returns the element from the rear.

### PriorityQueue

A max-heap implementation.

-   `init(cap: int) -> void`: Initializes the priority queue.
-   `push(val: int) -> void`: Inserts an element into the queue.
-   `pop() -> int`: Removes and returns the largest element.
