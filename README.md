# Arduino----arduShell
Commandline shell for arduino

## Shell interpreter which use serial port

Read input string and split into substrings ie. `command_name arg0 arg1 arg2` , and look for command (first string) with corresponding name, the following strings are command arguments.

When command name is unknown then help (command list is printed).

When command arguments are unknown then individual help is printed.

## You can add your own commands by:
1. Extending enum `arduShell_command_t` (`COMMAND_LAST` - must be the last one)
2. Extending command names list `arduShell_command_names` according to the order of enum.
3. Creating command as function type int with arguments `cmd_gpio(String args[], const uint8_t argc)` 
4. Add command to command list `cmd_list` in order.
