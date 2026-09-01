#!/bin/bash

echo "A. Lines that start with S:"
grep '^S' Employees.txt

echo
echo "B. Lines containing HR case-sensitive:"
grep 'HR' Employees.txt

echo
echo "C. Lines containing HR, ignoring case sensitivity:"
grep -i 'HR,' Employees.txt

