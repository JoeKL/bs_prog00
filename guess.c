#include "guessing.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long get_data_segment_start() {
    FILE *maps_file = fopen("/proc/self/maps", "r");

    unsigned long start, end;
    char perms[5];
    while (fscanf(maps_file, "%lx-%lx %4s", &start, &end, perms) == 3) {
        if (perms[0] == 'r' && perms[1] == 'w') {
            fclose(maps_file);
            return start;
        }
        // Skip to the next line
        while (fgetc(maps_file) != '\n' && !feof(maps_file));
    }

    fclose(maps_file);
    fprintf(stderr, "Data segment not found\n");
	return -1;
}

unsigned int guess_the_number(void) //lt. Aufgabenstellung darf dieser Header nicht verändert werden.
{

	unsigned long process__data_start = get_data_segment_start();
	unsigned long target_address = process__data_start + 0x44;

	int value;
	memcpy(&value, (void *)target_address, sizeof(int));
	return value;

}
