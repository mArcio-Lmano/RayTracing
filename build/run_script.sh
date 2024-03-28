#!/bin/bash

# Define the run function
run() {
    make
    ./ray_tracing > image.ppm
}

# Call the run function
run