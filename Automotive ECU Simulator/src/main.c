#include "ecu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_SIZE 128

static EcuInputs inputs;
static EcuOutputs outputs;

/* Display ECU information */
static void PrintStatus(void)
{
    printf("\n========== ECU STATUS ==========\n");

    printf("ECU State       : %s\n",
           ECU_GetStateName(outputs.state));

    printf("Throttle        : %.1f %%\n",
           inputs.throttle_percent);

    printf("Temperature     : %.1f C\n",
           inputs.temperature_c);

    printf("Ignition        : %s\n",
           inputs.ignition_on ? "ON" : "OFF");

    printf("Brake           : %s\n",
           inputs.brake_pressed ? "PRESSED" : "RELEASED");

    printf("Engine RPM      : %u\n",
           (unsigned int)outputs.engine_rpm);

    printf("Overtemperature : %s\n",
           outputs.overtemperature_fault ? "YES" : "NO");

    printf("Diagnostic Code : %s\n",
           ECU_GetDtcName(outputs.dtc));

    printf("Description     : %s\n",
           ECU_GetDtcDescription(outputs.dtc));

    printf("Cycle Count     : %u\n",
           (unsigned int)outputs.cycle_count);

    printf("================================\n");
}

/* Display available commands */
static void PrintHelp(void)
{
    printf("\nAvailable commands:\n");

    printf("  help          - Show commands\n");
    printf("  status        - Display ECU status\n");
    printf("  throttle 50   - Set throttle to 50 percent\n");
    printf("  temp 85       - Set temperature to 85 C\n");
    printf("  ignition on   - Switch ignition ON\n");
    printf("  ignition off  - Switch ignition OFF\n");
    printf("  brake on      - Press brake\n");
    printf("  brake off     - Release brake\n");
    printf("  tick 10       - Execute 10 ECU cycles\n");
    printf("  quit          - Exit simulator\n\n");
}

/* Run one or more ECU update cycles */
static void RunCycles(unsigned int count)
{
    unsigned int i;

    for (i = 0U; i < count; i++)
    {
        ECU_Update(&inputs, &outputs);

        if (outputs.state == ECU_STATE_FAULT)
        {
            break;
        }
    }

    PrintStatus();
}

int main(void)
{
    char command[COMMAND_SIZE];

    inputs.throttle_percent = 0.0f;
    inputs.temperature_c = 25.0f;
    inputs.ignition_on = false;
    inputs.brake_pressed = false;

    ECU_Init(&outputs);

    printf("====================================\n");
    printf("     AUTOMOTIVE ECU SIMULATOR\n");
    printf("====================================\n");

    printf("Educational C11 software simulator\n");

    PrintHelp();
    PrintStatus();

    while (1)
    {
        char *argument;
        char *extra;

        printf("\nECU> ");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "quit") == 0)
        {
            printf("Exiting ECU simulator.\n");
            break;
        }

        if (strcmp(command, "help") == 0)
        {
            PrintHelp();
            continue;
        }

        if (strcmp(command, "status") == 0)
        {
            PrintStatus();
            continue;
        }

        if (strncmp(command, "throttle ", 9) == 0)
        {
            char *end_pointer;

            argument = command + 9;

            while (*argument == ' ')
            {
                argument++;
            }

            if (*argument == '\0')
            {
                printf("Error: enter a throttle value.\n");
                continue;
            }

            inputs.throttle_percent =
                strtof(argument, &end_pointer);

            if (end_pointer == argument)
            {
                printf("Error: invalid throttle value.\n");
                continue;
            }

            while (*end_pointer == ' ')
            {
                end_pointer++;
            }

            if (*end_pointer != '\0')
            {
                printf("Error: enter only one numeric value.\n");
                continue;
            }

            RunCycles(1U);
            continue;
        }

        if (strncmp(command, "temp ", 5) == 0)
        {
            char *end_pointer;

            argument = command + 5;

            while (*argument == ' ')
            {
                argument++;
            }

            if (*argument == '\0')
            {
                printf("Error: enter a temperature value.\n");
                continue;
            }

            inputs.temperature_c =
                strtof(argument, &end_pointer);

            if (end_pointer == argument)
            {
                printf("Error: invalid temperature value.\n");
                continue;
            }

            while (*end_pointer == ' ')
            {
                end_pointer++;
            }

            if (*end_pointer != '\0')
            {
                printf("Error: enter only one numeric value.\n");
                continue;
            }

            RunCycles(1U);
            continue;
        }

        if (strncmp(command, "ignition ", 9) == 0)
        {
            argument = command + 9;

            if (strcmp(argument, "on") == 0)
            {
                inputs.ignition_on = true;
            }
            else if (strcmp(argument, "off") == 0)
            {
                inputs.ignition_on = false;
            }
            else
            {
                printf("Use: ignition on OR ignition off\n");
                continue;
            }

            RunCycles(1U);
            continue;
        }

        if (strncmp(command, "brake ", 6) == 0)
        {
            argument = command + 6;

            if (strcmp(argument, "on") == 0)
            {
                inputs.brake_pressed = true;
            }
            else if (strcmp(argument, "off") == 0)
            {
                inputs.brake_pressed = false;
            }
            else
            {
                printf("Use: brake on OR brake off\n");
                continue;
            }

            RunCycles(1U);
            continue;
        }

        if (strncmp(command, "tick ", 5) == 0)
        {
            char *end_pointer;
            unsigned long count;

            argument = command + 5;

            while (*argument == ' ')
            {
                argument++;
            }

            count = strtoul(argument, &end_pointer, 10);

            while (*end_pointer == ' ')
            {
                end_pointer++;
            }

            if (end_pointer == argument ||
                *end_pointer != '\0' ||
                count == 0UL ||
                count > 100000UL)
            {
                printf("Use: tick <number from 1 to 100000>\n");
                continue;
            }

            RunCycles((unsigned int)count);
            continue;
        }

        /*
         * Prevent accidental interpretation of unused
         * command arguments.
         */
        extra = NULL;
        (void)extra;

        printf("Unknown command. Type 'help'.\n");
    }

    return 0;
}
