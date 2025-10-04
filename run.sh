#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <run_name> <input_file> <config_file>"
    exit 1
fi

run_name="$1"
input_file="$2"
config_file="$3"


mkdir -p "$run_name"
echo "---------------------"
echo "Running C++ simulation..."
time ./main "$run_name" "$input_file" "$config_file"

# 3. Plotting
echo "---------------------"
echo " Plotting energies..."
python3 analyse_data/analyse_energies.py "$run_name" energies.txt


echo " Plotting positions..."
python3 analyse_data/analyse_positions.py "$run_name" positions.txt

echo "==> Done. Outputs saved in '$run_name/'"
echo "---------------------"