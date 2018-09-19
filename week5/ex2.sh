#!/usr/bin/env bash

lock() {
    ln 'file' 'file.lock'
}

wait() {
    lock
    while [[ $? != 0 ]]; do
        current=$(date +%s)
        if [[ $((current - start)) > 5 ]]; then
            echo 'Failed'
            exit 1
        fi
        lock
    done
}

unlock() {
    rm 'file.lock'
}

if [ -e 'file.lock' ]; then
    rm 'file.lock' 2> /dev/null
fi

touch 'file'

wait
lines_count=$(wc -l < 'file')
if [[ $lines_count == 0 ]]; then
    echo '0' >> 'file'
fi
unlock

for i in {1..10}; do
    # critical region, as scripts may read the last number simultaneously and thus write the same number in the next line
    wait
    N=$(tail -n 1 'file')
    echo $((N + 1)) >> 'file'
    unlock
done
echo Done