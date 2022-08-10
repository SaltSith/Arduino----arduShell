#include "arduShell_commands.h"
#include "system.h"

static const String arduShell_command_names[COMMAND_LAST]{
	"reboot",
	"uptime",
	"gpio"
};

typedef int(*arduShell_command) (String args[], const uint8_t argc);

static int cmd_reboot(String args[], const uint8_t argc);
static int cmd_uptime(String args[], const uint8_t argc);
static int cmd_gpio(String args[], const uint8_t argc);

static int cmd_reboot(String args[], const uint8_t argc)
{
	Serial.print("Rebooting device");

	for (uint8_t i = 0; i < 5; i++) {
		Serial.print(". ");
		delay(250);
	}

	Serial.println("");

	reboot();

	return 0;
}

static int cmd_uptime(String args[], const uint8_t argc)
{
	unsigned long int uptime = millis() / 1000;

	Serial.println(String(uptime) + " seconds");

	return 0;
}

static int cmd_gpio(String args[], const uint8_t argc)
{
	if (argc == 3 && args[1] == "mode" && args[2] == "output") {
		pinMode(args[3].toInt(), OUTPUT);
	}
	else if (argc == 3 && args[1] == "mode" && args[2] == "input") {
		pinMode(args[3].toInt(), INPUT);
	}
	else if (argc == 2 && args[1] == "get") {
		Serial.println(digitalRead(args[2].toInt()));
	}
	else if (argc == 3 && args[1] == "set") {
		digitalWrite(args[2].toInt(), args[3].toInt());
	}
	else {
		Serial.println("Usage:");
		Serial.println("\tgpio mode <output/input> <pin> -- set pin in mode");
		Serial.println("\t\t output - set <pin> as output");
		Serial.println("\t\t input - set <pin> as output");
		Serial.println("\tgpio set <pin> <1/0> -- set pin state");
		Serial.println("\tgpio get <pin> -- get pin state");
		return -1;
	}

	return 0;
}

static arduShell_command cmd_list[] = {
	cmd_reboot,
	cmd_uptime,
	cmd_gpio
};

String arduShell_command_name_get(const arduShell_command_t command)
{

	return arduShell_command_names[command];
}

int arduShell_command_handler(const arduShell_command_t command, String args[], const uint8_t argc)
{
	return cmd_list[command](args, argc);
}

void arduShell_commands_help(void)
{
	Serial.println("Help:");
	for (uint8_t command = 0; command < COMMAND_LAST; command++) {
		Serial.println("\t" + arduShell_command_names[(const arduShell_command_t)command]);
	}
}
