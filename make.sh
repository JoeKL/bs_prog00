#!/bin/bash

# Prüfen, ob mindestens ein Argument übergeben wurde
if [ $# -eq 0 ]; then
    echo "Fehler: Kein Argument übergeben. Nutze 'compile' oder 'clean'."
    exit 1
fi

# Die Aktion basierend auf dem Argument ausführen
case "$1" in
    "compile")
        # Überprüfen, ob der bin-Ordner existiert, wenn nicht, erstelle ihn
        [ ! -d "bin" ] && mkdir bin

        # Übersetzen, wenn die Quelldateien neuer sind als die Programmdatei
        if [ ! -f "bin/program" ] || [ "guess.c" -nt "bin/program" ] || [ "guessing.h" -nt "bin/program" ] || [ "main.c" -nt "bin/program" ]; then
            gcc -std=c11 -Wall -Wextra -Werror guess.c main.c -o bin/program
        else
            echo "Programm ist bereits auf dem neuesten Stand."
        fi
        ;;
    "clean")
        # Lösche den bin-Ordner und sein Inhalt
        [ -d "bin" ] && rm -r bin
        ;;
    *)
        # Fehlermeldung, wenn das Argument nicht erkannt wird
        echo "Fehler: Unbekanntes Argument. Nutze 'compile' oder 'clean'."
        exit 1
        ;;
esac
