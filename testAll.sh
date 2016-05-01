#! /bin/sh

for file in $(ls kakuro_grid); do
    ./kakuro -b kakuro_grid/$file
    echo -e "\n"
    ./kakuro -f kakuro_grid/$file
    echo -e "\n"
done
