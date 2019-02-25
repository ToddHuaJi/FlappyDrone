#include <stdio.h>
#include <unistd.h>

#include <AP_Common/AP_Common.h>
#include <AP_HAL_Linux/AP_HAL_Linux.h>
#include <AP_Menu/AP_Menu.h>

void setup();
void loop();
int parse_gpio_pin_number(uint8_t argc, const Menu::arg *argv);

#define MENU_FUNC(func) FUNCTOR_BIND(&commands, &MenuCommands::func, int8_t, uint8_t, const Menu::arg *)

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

int parse_gpio_pin_number(uint8_t argc, const Menu::arg *argv) {
    if (argc != 2) {
        fprintf(stderr, "Input and output commands take only one argument, which is the port number\n");
        return -1;
    }

    long int port = argv[1].i;
    if (port < 0 || port>7) {
        fprintf(stderr, "Invalid port number: %ld\n", pin);
        return -1;
    }

    return port;
}

static int8_t test_gpio_input(uint8_t argc, const Menu::arg *argv, bool use_channel) {
    AP_HAL::DigitalSource *ch = nullptr;
    int pin = parse_gpio_pin_number(argc, argv);

    if (pin <= 0) return -1;

    if (use_channel) {
        ch = hal.gpio->channel(pin);
        ch->mode(HAL_GPIO_INPUT);
    } else {
        hal.gpio->pinMode(pin, HAL_GPIO_INPUT);
    }

    hal.console->printf("Ok, I'll start reading pin number %d  and printing the value read on intervals of 1 second.", pin);
    while (1) {
        hal.console->printf("%u ", use_channel ? ch->read() : hal.gpio->read(pin));
        sleep(1);
    }
    return 0;
}

static int8_t test_gpio_output(uint8_t argc, const Menu::arg *argv, bool use_channel) {
    AP_HAL::DigitalSource *ch1 = nullptr;
    AP_HAL::DigitalSource *ch2 = nullptr;
    AP_HAL::DigitalSource *ch3 = nullptr;
    int port = parse_gpio_pin_number(argc, argv);

    if (port < 0) return -1;

    if (use_channel) {
        ch1 = hal.gpio->channel(7);
        ch1->mode(HAL_GPIO_OUTPUT);
        ch2 = hal.gpio->channel(8);
        ch2->mode(HAL_GPIO_OUTPUT);
        ch3 = hal.gpio->channel(9);
        ch3->mode(HAL_GPIO_OUTPUT);
    } else {
        hal.gpio->pinMode(7, HAL_GPIO_OUTPUT);
        hal.gpio->pinMode(8, HAL_GPIO_OUTPUT);
        hal.gpio->pinMode(9, HAL_GPIO_OUTPUT);
    }

    hal.console->printf("Now I'll start toggling the signal on the port number %d ."
            " It's recommended to verify that the signal is reaching it (e.g. by using a LED)\n", port);

    switch (port) {
        // trivial , need to be defined
        case 0: hal.gpio->write(7,0); hal.gpio->write(8,0); hal.gpio->write(9,0); hal.gpio->write(10,0);break;
        case 1: hal.gpio->write(7,0); hal.gpio->write(8,0); hal.gpio->write(9,0); hal.gpio->write(10,1);break;
        case 2: hal.gpio->write(7,0); hal.gpio->write(8,0); hal.gpio->write(9,1); hal.gpio->write(10,0);break;
        case 3: hal.gpio->write(7,0); hal.gpio->write(8,0); hal.gpio->write(9,1); hal.gpio->write(10,1);break;
        case 4: hal.gpio->write(7,0); hal.gpio->write(8,1); hal.gpio->write(9,0); hal.gpio->write(10,0);break;
        case 5: hal.gpio->write(7,0); hal.gpio->write(8,1); hal.gpio->write(9,0); hal.gpio->write(10,1);break;
        case 6: hal.gpio->write(7,0); hal.gpio->write(8,1); hal.gpio->write(9,1); hal.gpio->write(10,0);break;
        case 7: hal.gpio->write(7,0); hal.gpio->write(8,1); hal.gpio->write(9,1); hal.gpio->write(10,1);break;
        case 8: hal.gpio->write(7,1); hal.gpio->write(8,0); hal.gpio->write(9,0); hal.gpio->write(10,0);break;
        case 9: hal.gpio->write(7,1); hal.gpio->write(8,0); hal.gpio->write(9,0); hal.gpio->write(10,1);break;
        case 10: hal.gpio->write(7,1); hal.gpio->write(8,0); hal.gpio->write(9,1); hal.gpio->write(10,0);break;
        case 11: hal.gpio->write(7,1); hal.gpio->write(8,0); hal.gpio->write(9,1); hal.gpio->write(10,1);break;
        case 12: hal.gpio->write(7,1); hal.gpio->write(8,1); hal.gpio->write(9,0); hal.gpio->write(10,0);break;
        case 13: hal.gpio->write(7,1); hal.gpio->write(8,1); hal.gpio->write(9,0); hal.gpio->write(10,1);break;
        case 14: hal.gpio->write(7,1); hal.gpio->write(8,1); hal.gpio->write(9,1); hal.gpio->write(10,0);break;
        case 15: hal.gpio->write(7,0); hal.gpio->write(8,0); hal.gpio->write(9,1); hal.gpio->write(10,1);break;


    }
    return 0;
}

class MenuCommands {
public:
    int8_t gpio_input(uint8_t argc, const Menu::arg *argv) {
        return ::test_gpio_input(argc, argv, false);
    }

    int8_t gpio_output(uint8_t argc, const Menu::arg *argv) {
        return ::test_gpio_output(argc, argv, false);
    }

    int8_t gpio_input_channel(uint8_t argc, const Menu::arg *argv) {
        hal.console->printf("GPIO Input using digital source\n");
        return test_gpio_input(argc, argv, true);
    }

    int8_t gpio_output_channel(uint8_t argc, const Menu::arg *argv) {
        hal.console->printf("GPIO Output using digital source\n");
        return test_gpio_output(argc, argv, true);
    }

};

MenuCommands commands;

const struct Menu::command test_menu_commands[] = {
    {"input",          MENU_FUNC(gpio_input)},
    {"output",         MENU_FUNC(gpio_output)},
    {"input_ch",       MENU_FUNC(gpio_input_channel)},
    {"output_ch",      MENU_FUNC(gpio_output_channel)}
};

MENU(main_menu, "GPIOTest: Please select one of the operations followed by the mux port number", test_menu_commands);

void setup(void)
{
    Menu::set_port(hal.console);
    hal.console->set_blocking_writes(true);

    while (1) {
        main_menu.run();
    }
}

void loop(void)
{
}

AP_HAL_MAIN();
