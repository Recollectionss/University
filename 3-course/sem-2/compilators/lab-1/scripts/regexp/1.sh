REGEXP=$(cat ./scripts/source/regexp1.txt)

echo
echo "Input: abb"
echo "abb" | grep -E -x --color "$REGEXP"

echo
echo "Input: baba"
echo "baba" | grep -E -x --color "$REGEXP"

echo
echo "Input: aab"
echo "aab" | grep -E -x --color "$REGEXP"

echo
echo "Input: bba"
echo "bba" | grep -E -x --color "$REGEXP"

echo
echo "Input: b"
echo "b" | grep -E -x --color "$REGEXP"

echo
echo "Input: bb"
echo "bb" | grep -E -x --color "$REGEXP"

