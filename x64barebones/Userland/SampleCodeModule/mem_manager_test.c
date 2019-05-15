#include "include/mem_manager_test.h"

void mem_manager_test(){
    for(int i = 0; i<4; i++){
        void * alloc1 = sys_my_malloc(100);
        print_f("Alloc1 = %d\n", alloc1);
        void * alloc2 = sys_my_malloc(200);
        print_f("Alloc2 = %d\n", alloc2);
        void * alloc3 = sys_my_malloc(300);
        print_f("Alloc3 = %d\n", alloc3);
        sys_my_free(alloc3);
        sys_my_free(alloc2);
        sys_my_free(alloc1);
    }
}
