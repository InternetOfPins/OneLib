// #include <OneLib/src/OneLib.h>
#include <OneLib/src/OneSimba.h>

using namespace OneLib;
using namespace OneLib::Simba;

int main()
{
    struct pin_driver_t led;

    /* Start the system. */
    sys_start();

    /* Initialize the LED pin as output and set its value to 1. */
    pin_init(&led, &pin_led_dev, PIN_OUTPUT);
    pin_write(&led, 1);

    while (1) {
        /* Wait half a second. */
        thrd_sleep_ms(500);

        /* Toggle the LED on/off. */
        pin_toggle(&led);
    }

    return (0);
}
