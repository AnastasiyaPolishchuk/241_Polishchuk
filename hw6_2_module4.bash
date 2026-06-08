#!/bin/bash

sum() {
    local total=0
    local error=0

    for num in "$@"; do
        addition=$(expr "$total" + "$num" 2>/dev/null)
        if [ $? -ne 0 ]; then
            error=1
            break
        fi
        total="$addition"
    done

    if [ $error -eq 1 ]; then
        echo 0
    else
        echo "$total"
    fi
}

read -r line1
read -r line2

sum1=$(sum $line1)
sum2=$(sum $line2)

if [ "$sum1" -eq "$sum2" ]; then
    echo "Equal"
else
    echo "Not equal"
fi