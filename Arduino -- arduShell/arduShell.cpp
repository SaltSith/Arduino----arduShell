#include "arduShell.h"

#include <Arduino.h>

#define ARDU_SHELL_MAX_ARGS					5/// Total args for commands

static void arduShell_debug(String args[], uint8_t argc);

static void arduShell_debug(String args[], uint8_t argc)
{
	Serial.println("argc = " + String(argc));

	for (uint8_t arg = 0; arg <= argc; arg++) {
		Serial.println("[" + String(arg) + "] " + args[arg]);
	}
}

void arduShell_init(const uint32_t baudrate)
{
	Serial.begin(baudrate);

	Serial.println("arduShell initialized. . . ");
}

void arduShell_main_loop(void)
{
	String data = "";

	String args[ARDU_SHELL_MAX_ARGS];
	uint8_t argc = 0;

	if (Serial.available()) {
		data = Serial.readString();
	}

	if (data == "") {
		return;
	}

	data.replace("\n", "");
	data.replace("\r", "");

	for (uint16_t i = 0; i < data.length(); i++) {
		if (data[i] == ' ') {
			argc++;
			continue;
		}
		if (argc >= ARDU_SHELL_MAX_ARGS) {
			Serial.println("To many arguments!");
			return;
		}
		args[argc] += data[i];
	}

	arduShell_debug(args, argc);
}

