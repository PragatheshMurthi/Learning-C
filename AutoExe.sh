#!/bin/bash

# Path to the file that triggers tcpdump
TRIGGER_FILE="/home/sidharth/Pragathesh/trigger_file.txt"

# Interface to listen on
INTERFACE="eth0"

# Output file for tcpdump
OUTPUT_FILE="/home/sidharth/Pragathesh/tcpdump_output.pcap"

# Infinite loop
while true; do
    if [ -f "$TRIGGER_FILE" ]; then
        echo "[$(date)] File found: $TRIGGER_FILE. Starting tcpdump..."

        # Start tcpdump in background
        tcpdump -i "$INTERFACE" -w "$OUTPUT_FILE" > /dev/null 2>&1 &
        TCPDUMP_PID=$!

        echo "[$(date)] tcpdump started with PID $TCPDUMP_PID. Sleeping for 80ms..."

        # Sleep for 80 milliseconds
        sleep 0.08

        # Kill the tcpdump process
        kill $TCPDUMP_PID 2>/dev/null

        echo "[$(date)] tcpdump with PID $TCPDUMP_PID killed after 80ms."

        # Remove the trigger file
        rm -f "$TRIGGER_FILE"
    else
        echo "[$(date)] Trigger file not found. Waiting..."
    fi

    # Sleep before checking again
    sleep 5
done
