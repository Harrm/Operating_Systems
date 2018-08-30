#!/bin/bash

gcc "ex$1.c" "-o" "ex$1.out" 

"./ex$1.out"
