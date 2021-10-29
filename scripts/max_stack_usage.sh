#!/bin/sh

echo 'Maximum Stack Usage: \c'
grep 'Maximum Stack Usage' $1 |awk '{printf("%d\n",$6)}'| sort -n |tail -1