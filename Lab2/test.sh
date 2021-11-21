#!/bin/sh

echo Building LongArithmetic...
if ! gcc Lab2.c; then 
    echo -e "\e[31;1mBuild Failed. \e[33mExiting...\e[0m" 
    exit 1
fi
i=1

function test_arithmectic() {
    got=$(./a.out $1 $2 $3)
    if [[ $got -eq $4 ]]; then
	    echo -e "Test \e[33;1m$i \e[32mPASSED\e[0m"
        return 0
    else
	    echo -e "Test \e[33;1m$i \e[31mFAILED\e[0m [Got: $got, Expected: $4]"
        return 1
    fi
}

test_arithmectic 3 + 5 8
i=$(($i + 1))
test_arithmectic 20 - 10 10
i=$(($i + 1))
test_arithmectic 5 - 5 0
i=$(($i + 1))
test_arithmectic 3 / 5 0
i=$(($i + 1))
test_arithmectic 10 . 4234542 42345420
i=$(($i + 1))
test_arithmectic 256 / 64 4
i=$(($i + 1))
test_arithmectic 7 . 8 56
i=$(($i + 1))