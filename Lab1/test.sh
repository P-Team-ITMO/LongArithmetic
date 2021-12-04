#!/bin/sh
echo Building WordCount...
if ! gcc main.c; then 
	echo -e "Build \e[31;1mFailed\e[0m. \e[33mExiting...\e[0m"
	exit 1
fi

# set to false if checking for bytes is not needed
CHECK_BYTES=true
BYTES_EXPECTED=(83 57 0 45)
# same for lines
CHECK_LINES=true
LINES_EXPECTED=(3 1 0 8)
# ...and for words
CHECK_WORDS=true
WORDS_EXPECTED=(13 13 0 5)

echo -n "Check for: "
[[ $CHECK_WORDS = true ]] && echo -n "words "
[[ $CHECK_BYTES = true ]] && echo -n "bytes "
[[ $CHECK_LINES = true ]] && echo -n "lines"
echo ""
exit_code=0
i=0
for testfile in tests/test?.txt; do
	passed=true
	if [[ $CHECK_WORDS = true ]]; then
		words=$(./a.out -w $testfile)
		[ $words -eq ${WORDS_EXPECTED[$i]} ] || passed=false
	fi
	if [[ $CHECK_BYTES = true ]]; then
		bytes=$(./a.out -c $testfile)
		[ $bytes -eq ${BYTES_EXPECTED[$i]} ] || passed=false
	fi
	if [[ $CHECK_LINES = true ]]; then
		lines=$(./a.out -l $testfile)
		[ $lines -eq ${LINES_EXPECTED[$i]} ] || passed=false
	fi
	if [[ $passed = true ]]; then
			echo -e "Test \e[33;1m$(($i + 1 )) \e[32mPASSED\e[0m "
	else 
		echo -ne "Test \e[33;1m$(($i + 1)) \e[31mFAILED\E[0m ["
			if [[ $words -ne ${WORDS_EXPECTED[$i]} && $CHECK_WORDS = true ]]; then
				echo -ne "Words got: $words, Expected: ${WORDS_EXPECTED[$i]}; "
			fi
			if [[ $bytes -ne ${BYTES_EXPECTED[$i]} && $CHECK_BYTES = true ]]; then
				echo -ne "Bytes got: $bytes, Expected: ${BYTES_EXPECTED[$i]}; "
			fi
			if [[ $lines -ne ${LINES_EXPECTED[$i]} && $CHECK_LINES = true ]]; then
				echo -ne "Lines got: $lines, Expected: ${LINES_EXPECTED[$i]}; "
			fi
		echo -e "\b\b  \b\b]"
        exit_code=1
	fi
	i=$(($i + 1))
done
exit $exit_code
