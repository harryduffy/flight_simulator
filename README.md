# Plane Loading Simulator

## Abstract

The other day I was waiting to board a plane to the Gold Coast, when the attendant called the back half of passengers to board the plane (rows <img src="https://latex.codecogs.com/svg.image?\frac{n}{2}&space;\rightarrow&space;n"/>). I then started thinking about what was a quicker **loading scheme**:
1. loading the plane by row, like the attendant had done, or
2. loading the plane by column

That is, loading the row by outside columns to inside columns. This made more sense to me, as the *queue's* to enter a certain row experience no blocking. My hypothesis is that loading the plane by column is quicker.

I also want to improve my programming skills in C, so will be producing the simulator in **C** as opposed to **Python** where it may be more favourable, due to easier access to graphical interfaces like Matplotlib or Pygame and having an Object Oriented Paradigm.

## Current State

The simulation is almost complete for simulating row-loading but is incomplete for column-loading. The row-loading simulation requires randomly generated passenger delay, row blocking and other characteristics of a loading scenario to be a more accurate representation of loading a plane.

### By Harry Duffy
