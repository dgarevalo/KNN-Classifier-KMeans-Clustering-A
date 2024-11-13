#!/bin/bash

# Bucle externo i=0 a 7
for ((i=0; i<6; i++)); do
    if [ "$i" -ne 4 ] && [ "$i" -ne 3 ]; then
        # Crear carpeta Dataset{i+1}
        mkdir -p "Dataset$((i+1))"
        # Entrar en la carpeta
        
        # Bucle para ejecutar con k-means y con k-medoids
        for ((k=1; k<3; k++)); do
        # Bucle interno j=0 a 10
            for ((j=0; j<10; j++)); do
                cd "Dataset$((i+1))"
                mkdir -p "$((j+1))"
                cd ..
                # Ejecutar el comando ./../program > j.txt con las entradas 2 i+1 1
                echo "2 $((i+1)) $((k))" | ./program > "Dataset$((i+1))/$((j+1))/$((j))_$((k)).txt"
                
            done
        done
    fi
    
    # Salir de la carpeta
done