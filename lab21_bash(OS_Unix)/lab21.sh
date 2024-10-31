#!/bin/bash

#Лабораторная работа №21. Вариант 4
#Выполнил студент группы М8О-104Б-22
#Тесля Данила Сергеевич

if [ $# -ne 3 ]; then
    echo "Введите $0 директория суффикс префикс"
    exit 1
fi


dir="$1"
suff="$2"                          
pref="$3"

cd "$dir" || exit 1

for file in *"$suff"; do

    if [ -e "$file" ]; then
        filename=$(basename "$file")
        filerename="$pref$filename"
        mv "$file" "$filerename"
        echo "Файл: $filename был переименован в : $filerename"
    fi

done
