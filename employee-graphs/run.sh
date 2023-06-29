#!/bin/bash

make
./tema2

score=0

begin_test='output_'
begin_result='reference/result_'
termination='.out'

arr=( "hire" "fire" "promote" "move_employee" "move_team" "fire_team" "employees_by_manager" "employees_by_level" "best_manager" "reorganize" )
scores=( 5 10 10 10 10 5 5 10 5 20)

for i in {0..9}
do
    element=${arr[$i]}
    testFileName=$begin_test$element$termination
    resultFileName=$begin_result$element$termination
    result=$(diff $testFileName $resultFileName | wc -l)

    if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
        echo "Test ${arr[$i]}...........................passed"
        score=$((score+${scores[$i]}))
    else
        echo "Test ${arr[$i]}...........................failed"
    fi
done

echo "                                      Total: $score"
echo "Punctele pentru eliberarea memoriei vor fi acordate dupa verificarea cu valgrind. (make test)"

make clean
