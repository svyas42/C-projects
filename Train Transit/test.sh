#!/bin/bash
# This is a shell script to check your program(s) on test cases.
# It usese the same language you normally use to type commands in
# a terminal window.  You can write whole programs in shell.

# Assume we've succeeded until we see otherwise.
FAIL=0

# Print an error message and set the fail flag.
fail() {
    echo "**** $1"
    FAIL=1
}

# Check the exit status.  The actual exit status (ASTATUS) should match
# the expected status (ESTATUS)
checkStatus() {
    ESTATUS="$1"
    ASTATUS="$2"

    # Make sure the program exited with the right exit status.
    if [ "$ASTATUS" -ne "$ESTATUS" ]; then
	fail "FAILED - incorrect program exit status. (expected $ESTATUS,  Got: $ASTATUS)"
	return 1
    fi

    return 0
}

# Check the contents of an a file.  If the expected file (EFILE)
# exists, then the actual file (AFILE) should exist and it should match.
checkFile() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"

    # Make sure we're really expecting this file.
    if [ ! -f "$EFILE" ]; then
	return 0
    fi

    # Make sure the output matches the expected output.
    echo "   diff $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
	fail "FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
	return 1
    fi

    return 0
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should be empty.
checkFileOrEmpty() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"

    # if the expected output file doesn't exist, the actual file should be
    # empty.
    if [ ! -f "$EFILE" ]; then
	if [ -s "$AFILE" ]; then
	    fail "FAILED - $NAME ($AFILE) should be empty."
	    return 1
	fi
	return 0
    fi

    # Make sure the output matches the expected output.
    echo "   diff $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
	fail "FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
	return 1
    fi

    return 0
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should not exist.
checkFileOrDNE() {
    NAME="$1"
    EFILE="$2"
    AFILE="$3"
    
    # if the expected output file doesn't exist, the actual file should not exist
    if [ ! -f "$EFILE" ]; then
	if [ -f "$AFILE" ]; then
	    fail "FAILED - $NAME ($AFILE) should not exist."
	    return 1
	fi
	return 0
    fi

    # Make sure the output matches the expected output.
    echo "   diff $EFILE $AFILE"
    diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
	fail "FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
	return 1
    fi

    return 0
}

# The given file should exist but should be empty.
checkEmpty() {
    NAME="$1"
    AFILE="$2"
    
    if [ -s "$AFILE" ]; then
	fail "FAILED - $NAME ($AFILE) should be empty."
	return 1
    fi

    return 0
}

# Test the ident program.
runTest() {
    TESTNO=$1
    ESTATUS=$2

    echo "Test $TESTNO"
    rm -f stdout.txt stderr.txt report.txt report2.txt

    echo "   ./transit ${args[@]} > stdout.txt 2> stderr.txt"
    ./transit ${args[@]} > stdout.txt 2> stderr.txt
    ASTATUS=$?

    if ! checkStatus "$ESTATUS" "$ASTATUS" ||
       ! checkFile "Terminal output" "expected-stdout-$TESTNO.txt" "stdout.txt" ||
       ! checkFile "Report output" "expected-report-$TESTNO.txt" "report.txt" ||
       ! checkFileOrEmpty "Stderr output" "expected-stderr-$TESTNO.txt" "stderr.txt"
    then
	return 1
    fi

    echo "Test $TESTNO PASS"
    return 0
}

# make a fresh copy of the target programs
make clean
make

if [ $? -ne 0 ]; then
    fail "Make exited unsuccessfully"
fi

# Run test cases
if [ -x  ]; then
    args=(map-01.txt route-01.txt)
    runTest 01 0
    
    args=(map-02.txt route-02.txt)
    runTest 02 0
    
    args=(map-03.txt route-03.txt)
    runTest 03 0
    
    args=(map-04.txt route-04.txt)
    runTest 04 0
    
    args=(map-05.txt route-05.txt)
    runTest 05 0
    
    args=(-v map-06.txt route-06.txt)
    runTest 06 0
    
    args=(-v map-07.txt route-07.txt)
    runTest 07 0
    
    args=(-v map-08.txt route-08.txt)
    runTest 08 0
    
    args=(-r report.txt map-09.txt route-09.txt)
    runTest 09 0
    
    args=(-r report.txt -v map-10.txt route-10.txt)
    runTest 10 0
    
    args=(-v -r report.txt map-11.txt route-11.txt)
    runTest 11 0
    
    args=(map-12.txt route-12.txt)
    runTest 12 0
    
    args=(-v map-13.txt route-13.txt)
    runTest 13 0
    
    args=(-v map-14.txt route-14.txt)
    runTest 14 0
    
    args=(-v map-15.txt route-15.txt)
    runTest 15 0
    
    args=(map-16.txt route-16.txt)
    runTest 16 1
    
    args=(map-17.txt route-17.txt)
    runTest 17 1
    
    args=(map-18.txt route-18.txt)
    runTest 18 1
    
    args=(map-19.txt route-19.txt)
    runTest 19 1
    
    args=(map-20.txt route-20.txt)
    runTest 20 1
    
    args=(map-21.txt route-21.txt)
    runTest 21 1
    
    args=(map-22.txt route-22.txt)
    runTest 22 1
    
    args=(map-23.txt route-23.txt)
    runTest 23 1
    
    args=(map-24.txt route-24.txt)
    runTest 24 1
    
    args=(map-25.txt missing-25.txt)
    runTest 25 1
    
    args=(-r /bad-report-file.txt map-26.txt route-26.txt)
    runTest 26 1
    
    args=(map-27.txt route-27.txt)
    runTest 27 1
    
    args=(-r report.txt -r report2.txt map-28.txt route-28.txt)
    runTest 28 1
    
    args=(-r map-29.txt route-29.txt)
    runTest 29 1
    
    args=(map-30.txt)
    runTest 30 1
    
else
    fail "Since your program didn't compile, no tests were run."
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "TESTS SUCCESSFUL"
  exit 0
fi
