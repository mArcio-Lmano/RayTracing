#!/bin/bash

# Define the run function
run() {
  if [ -f image.ppm ]; then
    rm image.ppm
  fi
  make
  ./ray_tracing >image.ppm
  feh image.ppm
}

# Call the run function
run
