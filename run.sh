#!/bin/bash
sudo clear
 
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
original_binary_name="zapclient"
temp_binary_name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1)

mkdir -p temp
if ! cp "$script_dir/$original_binary_name" "temp/$temp_binary_name"; then
  exit 1
fi

(sudo env XDG_RUNTIME_DIR="/run/user/0" "./temp/$temp_binary_name") & pid=$! # Get the PID of the executed binary
 
# Hide the PID of the executed binary and its child processes
if echo "$pid" | sudo tee /proc/sys/kernel/ns_last_pid > /dev/null; then
  child_pids=$(pgrep -P $pid)
  for child_pid in $child_pids; do
    echo "$child_pid" | sudo tee /proc/sys/kernel/ns_last_pid > /dev/null
  done
fi

trap 'rm -r "temp/"; exit 1' 2

# Wait for the binary to finish execution
if ! wait $pid; then
    rm -r "temp/"
    exit 1
fi
