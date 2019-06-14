#!/bin/bash

if test $# -ne 1
then
    echo "Usage: $0 TESTNAME" >&2
    exit 2
fi

TEST="$1"
DIFF="diff/$TEST.diff"
EFFX="reference/$TEST.ffx"
OFFX="current/$TEST.ffx"

if test ! -f "$DIFF"
then
    echo "Error: expecting file $DIFF to exists"
    exit 1
fi

if test -s "$DIFF"
then
    echo
    echo "#### BEGIN REGRESSION found for test $TEST ####"
    echo "## Expected FFX ($EFFX)"
    cat "$EFFX"
    echo "## Obtained FFX ($OFFX)"
    cat "$OFFX"
    echo "## Difference of summaries"
    cat "$DIFF"
    echo "####"
    echo "## If this is not a regression, enter:"
    echo "mv current/$TEST.ffx reference/$TEST.ffx"
    echo "## Otherwise, fix this!"
    echo "## You can rerun this test using:"
    echo "make $TEST.status"
    echo "#### END REGRESSION found for test $TEST ####"
    echo
fi
