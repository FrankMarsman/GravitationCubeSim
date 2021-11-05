# GravitationCubeSim
Simulation of a particle orbiting a cube shaped body.

<img width="350" alt="GUI" src="https://user-images.githubusercontent.com/7474358/140446798-7fdfb50c-043f-4a80-a705-7b5e3fd4597c.png">

## Introduction
This program can be used to simulate a point mass orbiting a central, cube shaped body. The program uses simple [**Newtonian gravity**](https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation) to compute the forces on the simulated particles. The user can control the masses, positions, and velocities of various particles in the simulation. 


## The GUI
The GUI of this program is shown below. The GUI allows the user to vary the simulation speed, as well as some other simulation parameters.

<img width="474" alt="GUI" src="https://user-images.githubusercontent.com/7474358/140445786-19775afe-3d89-4fba-b2b4-ef6b6c9cf27b.gif">


## Example simulations
Three example simulations are shown below. It is possible to create a wide range of simulations, by adjusting the parameters of the simulation.

<p float="left">
<img src="https://user-images.githubusercontent.com/7474358/140445370-c1881dc7-30ef-4811-bba8-8be69d1db1f9.gif" width="200" height="200">
<img src="https://user-images.githubusercontent.com/7474358/140445584-c91fe81b-4e90-4c72-8181-e83371b2ad0b.gif" width="200" height="200">
<img src="https://user-images.githubusercontent.com/7474358/140445606-497d47d7-acdd-4900-a38a-a635663876a0.gif" width="200" height="200">
</p>

## Usage
To add a central cube, use the `AddStaticCube(double len, uint N, double M)` method defined in [`gravsim.cpp`](https://github.com/FrankMarsman/GravitationCubeSim/blob/f4a708280b7b7458027ac976e97b3497a8743402/code/gravsim.cpp#L25-L39). This will add a cube with side lengths `len` [m] and mass `M` [kg]. The generated cube consists of `N` x `N` point masses, arranged in a square grid.

## How to run

### Qt Creator
Start by installing the Qt5 SDK from [qt.io](https://www.qt.io/download). 
To build this projects, open the [`GravitySim.pro`](code/GravitySim.pro) file with Qt Creator. Inside Qt Creator, you can first build the project, after which you can run the program.


