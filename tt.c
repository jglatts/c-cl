#include <stdio.h>
#include <stdint.h>

#define print_b(s, n, len)  printf("%s", s); \
                            for (int i = len-1; i >= 0; i--) \
                                printf("%d", n & (1 << i) ? 1 : 0); \
                             printf("\n");    

int main(void) {
    uint32_t tt = 0;
    ((uint8_t*)&tt)[0] = 0xFF;
    ((uint8_t*)&tt)[3] = 0xFF;
    print_b("tt: ", tt, 32);
    print_b("tt[0]: ", ((uint8_t*)&tt)[0], 8);
}