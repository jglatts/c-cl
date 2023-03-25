#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint16_t tt;
    ((uint8_t*)&tt)[0] = 0x55;
    ((uint8_t*)&tt)[1] = 0xA4;
    printf("%d\n", tt);
    return 0;
}
