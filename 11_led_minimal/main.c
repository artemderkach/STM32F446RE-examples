int main(void) {
    // Enable clock access
    (*(volatile unsigned int *) (0x40023830)) |= 0x1;
    // set PA5 as output pin
    (*(volatile unsigned int *) (0x40020000)) |=  (1U<<10); // 10 pin to 1
    (*(volatile unsigned int *) (0x40020000)) &= ~(1U<<11); // 11 pin to 0

    // write 1 to pin5 to turn on the LED
    (*(volatile unsigned int *) (0x40020014)) |=  (1U<<5);
}