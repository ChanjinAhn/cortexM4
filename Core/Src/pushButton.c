#include "main.h"
#include "pushButton.h"
// 4)
// return the first detected button
// return -1 => no detection
int PushBtnRead()
{
int i;
for ( i = 0; i < nPUSH_BTN ; i++ )
{
if(!HAL_GPIO_ReadPin(GPIOC, (0x0001 << i)))       // PushButton Normal High, Push Low
return i;
}
return -1;
}

unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set != 0) {
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }
    return p;
}
