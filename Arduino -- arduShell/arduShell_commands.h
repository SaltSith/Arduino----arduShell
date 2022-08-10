#pragma once

#include <Arduino.h>

typedef enum {
	REBOOT = 0,
	UPTIME,
	GPIO,
	COMMAND_LAST
} arduShell_command_t;

String arduShell_command_name_get(const arduShell_command_t command);
int arduShell_command_handler(const arduShell_command_t command, String args[], const uint8_t argc);
void arduShell_commands_help(void);
