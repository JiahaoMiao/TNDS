#!/bin/bash

# script che esegue in cascata N volte lo stesso programma

if test $# -eq 0; then
    echo "Usage: submit <number of elements to read in each files>"
    exit
fi

for i in 'seq 1 1'; #main loop
do
    # questo e' il comando di esecuzione del programma(nota i due parametri di input))
    ./prova $1 data$i.dat

    # qui rispesco il valore di ritorno del programma (return /exit)
    error_code=$?
    echo execution ended with code $error_code

    # se l'esecuzione non e' andato a buon fine
    if[ $error_code -ne 0] ; then
        echo rashing with code $error_code running on data$i.dat
        break
    fi
done

#Per eseguirlo, uso il comando "source" 