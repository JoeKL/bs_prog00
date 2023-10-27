#include "guessing.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
"/proc/self/maps"
address           permsissions offset  dev   inode   pathname
555555554000-555555555000 r--p 00000000 08:03 656114                     /home/bsstudent/Desktop/prog00/bin/program
555555555000-555555556000 r-xp 00001000 08:03 656114                     /home/bsstudent/Desktop/prog00/bin/program
555555556000-555555557000 r--p 00002000 08:03 656114                     /home/bsstudent/Desktop/prog00/bin/program
555555557000-555555558000 r--p 00002000 08:03 656114                     /home/bsstudent/Desktop/prog00/bin/program
555555558000-555555559000 rw-p 00003000 08:03 656114                     /home/bsstudent/Desktop/prog00/bin/program
0x555555558044 target_address
555555559000-55555557a000 rw-p 00000000 00:00 0                          [heap]

Suche also nach dem ersten Eintrag mit rw-p und gebe diesen zurück, 
das wird wahrscheinlich der Data bereich sein, da er beschreibbar ist.

füge 0x44 an um den Offset zu bekommen

Der Offset wurde mit Binary Ninja gesucht. Ist nicht immer der gleiche. 
Aber ich hoffe das reicht.
- Niko :)
*/

unsigned long get_data_segment_start() {
	// Öffne die Datei "/proc/self/maps" für den Lesezugriff.
    FILE *maps_file = fopen("/proc/self/maps", "r");

    unsigned long start, end;
    char permissions[5]; //"rwxp" würde in permissions als Zeichenkette "rwxp" plus das Nullterminierungszeichen '\0' gespeichert.

	// Durchlaufe die Datei und lese die Adresse, Endadresse und Berechtigungen.
    while (fscanf(maps_file, "%lx-%lx %4s", &start, &end, permissions) == 3) {
		// Wenn die Berechtigungen "rw" (Lesen und Schreiben) sind, schließe die Datei und gib die Startadresse zurück.
        if (permissions[0] == 'r' && permissions[1] == 'w') {
            fclose(maps_file);
            return start;
        }
        // Überspringe die Zeile bis zum nächsten Zeilenumbruch, um zur nächsten Zeile zu gelangen.
        while (fgetc(maps_file) != '\n' && !feof(maps_file));
    }

	// Schließe die Datei und gib einen Fehler aus, falls der Datenbereich nicht gefunden wurde.
    fclose(maps_file);
    fprintf(stderr, "Data segment not found\n");
	return 0; // Rückgabe eines ungültigen Wertes, um anzuzeigen, dass der Datenbereich nicht gefunden wurde.
}

unsigned int guess_the_number(void) //lt. Aufgabenstellung darf dieser Header nicht verändert werden.
{
    // Memory-Access Lösung -----------------------

	unsigned long process__data_start = get_data_segment_start(); // hole den start des Data Segments
    unsigned long target_address = process__data_start + 0x44; // füge 0x44 an um den Offset zu bekommen
    //printf("target_address = %p\n",(void *)target_address);

    int value;
    memcpy(&value, (void *)target_address, sizeof(int)); //kopiere den wert aus dem Speicherbereich
    return value;

    // Memory-Access Lösung -----------------------


    //Binary Search Lösung ------------------------

    // int left = 0;
    // int right = 99999;
    // while (left <= right){
    //     int mid = (left + right)/2;
    //             int eval = evaluate(mid);
    //             if (eval == 0){
    //                 return mid;
    //             } else if (eval == 1) {	    // evaluate == 1 wenn mid < target
    //                 left = mid + 1;
    //             } else if (eval == -1) {	// evaluate == -1 wenn mid > target
    //                 right = mid - 1;
    //             }
    // }
    // return -1;

    //Binary Search Lösung ------------------------


}
