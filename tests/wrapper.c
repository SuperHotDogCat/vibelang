#include <stdio.h>

// Declare Novus functions
// Note: Novus 'int' is i64, 'string' is i8*
extern long long add_numbers(long long a, long long b);
extern void greet(const char* name);
extern long long novus_main();

int main() {
    printf("--- C Wrapper calling Novus ---\n");

    novus_main();

    long long sum = add_numbers(10, 20);
    printf("C received sum from Novus: %lld\n", sum);

    greet("C Programmer");

    printf("--- End of C Wrapper ---\n");
    return 0;
}
