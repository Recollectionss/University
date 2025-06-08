REGEXP=$(cat ./scripts/source/regexp2.txt)

echo
echo "Input: "
echo "" | grep -E -x --color "$REGEXP"

echo
echo "Input: b"
echo "b" | grep -E -x --color "$REGEXP"

echo
echo "Input: baba"
echo "baba" | grep -E -x --color "$REGEXP"

echo
echo "Input: ab"
echo "ab" | grep -E -x --color "$REGEXP"

echo
echo "Input: bab"
echo "bab" | grep -E -x --color "$REGEXP"
