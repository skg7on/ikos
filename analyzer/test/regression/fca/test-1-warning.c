#include <stdio.h>

extern void __ikos_assert(int);
extern int __ikos_nondet_int(void);

// void(int)
static void a(int x) {}

// void(double)
static void b(double x) {}

// void(int*)
static void c(int* x) {}

// void(int*)
typedef void (*fun_ptr_t)(int*);

int main() {
  void* vtable[3];
  vtable[0] = (void*)a;
  vtable[1] = (void*)b;
  vtable[2] = (void*)c;

  int nd = __ikos_nondet_int();
  if (nd >= 0 && nd <= 2) {
    fun_ptr_t f = (fun_ptr_t)vtable[nd];
    f(NULL); // can only call c() because other functions have a wrong signature
  }

  return 0;
}
