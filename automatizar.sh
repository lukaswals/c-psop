#!/usr/bin/env bash
#
# Bash script para automatizar la ejecucion de varios algoritmos PSOP al mismo
# tiempo, aprovechando las capacidades multinucleos de los CPU actuales
#
# Copyright (c) 2013 
# Autores: Wals Ochoa, Lucas & Labayen, Franco

#Funcion que cuenta la cantidad de algoritmos pso en ejecucion
function contar_pso(){
    let cant=0
    while read -r line
    do
        let "cant++"
    done < <(jobs)
    echo "$cant"
}

echo "Ingrese la cantidad de ejecuciones que desea automatizar:"
read max

#Definimos una variable numerica que controlara la cantidad de ejecuciones
#de psop que se han realizado hasta el momento
let ejec=0
#Conseguimos la cantidad de nucleos de nuestra pc
let procesadores=$(nproc)
#Calculamos la cantidad maxima de ejecuciones simultaneas
let max_ejec=(procesadores-2)


if [ $max_ejec -lt 1 ]
then
    #Con esto nos aseguramos de al menos utilizar un procesador
    let "max_ejec=1"
fi

while [ $ejec -lt $max ]
#while [ $ejec -lt $6 ]
do
    #Si se estan ejecutando menos pso del maximo permitido
    #se ejecuta uno
    if [ $(contar_pso) -lt $max_ejec ]
    then
        #Ejecutamos el algoritmo en background para que no joda este script
        echo "Ejecutando psop nº $ejec..."
        ./psop $* &
        #./psop $1 $2 $3 $4 $5 &
        let "ejec++"
        #Sleep por seguridad de los archivos
        sleep 1
    fi
done

echo "Automatizacion terminada, puede que algunos algoritmos se esten ejecutando
aun. Por favor sea paciente. Lo normal es que falten $max_ejec o menos ejecuciones."

exit
