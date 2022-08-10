#include "arduShell.h"

#include <Arduino.h>

void arduShell_init(const uint32_t baudrate)
{
	Serial.begin(baudrate);

	Serial.println("arduShell initialized. . . ");
}

void arduShell_main_loop(void)
{

}
