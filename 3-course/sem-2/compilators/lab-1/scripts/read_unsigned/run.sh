#!/bin/bash
set -e

echo
echo "Input: 123"
echo "Result: "

echo "123" | ./dragon-tiger/read_unsigned
echo


echo "Input: 123f"
echo "Result: "

echo "123f" | ./dragon-tiger/read_unsigned
echo


echo "Input: -123"
echo "Result: "

echo "123f" | ./dragon-tiger/read_unsigned
echo
