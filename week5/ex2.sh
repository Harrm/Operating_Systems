#!/usr/bin/env bash

lock() {
    ln 'file' 'file.lock'
    return $?
}

wait() {
    lock
    while [[ $? != 0 ]]; do
        lock
    done
}

unlock() {
    rm 'file.lock'
}

if [ -e 'file.lock' ]; then
    rm 'file.lock' 2> /dev/null
fi

#critical region, as both scripts may try to create the file
touch 'file'

for i in {1..10}; do
    # critical region, as scripts may read the last number simultaneously and thus write the same number in the next line
    wait
    N=$(tail -n 1 'file')
    echo $((N + 1)) >> 'file'
    unlock
done
echo Done