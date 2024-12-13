#!/bin/bash
FAIL=0

# Function to run a single test of the program
runTest() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./template < input-$TESTNO.txt > output.txt"
  ./template < input-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Try to build the project with gcc.
echo "Building with gcc"
gcc -Wall -std=c99 -g template.c input.c replace.c -o template

# Run all the tests for our program
if [ -x template ] ; then
    runTest 01 0
    runTest 02 0
    runTest 03 0
    runTest 04 0
    runTest 05 0
    runTest 06 0
    runTest 07 0
    runTest 08 0
    runTest 09 0
    runTest 10 100
    runTest 11 100
    runTest 12 102
    runTest 13 101
    runTest 14 101
    runTest 15 103
    runTest 16 103
else
    echo "**** Your program didn't compile successfully, so it couldn't be tested."
    FAIL=1

fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
