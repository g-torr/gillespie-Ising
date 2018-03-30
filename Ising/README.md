### Ising model folder.
It contains 3 different implementations:
* **cudaC** (Monte Carlo)
* **Python3** (using Monte Carlo) for generic matrix of couplings
* **BGA** Matlab , using binary genetic algorithm
The BGA is not completed but it just try of minimising the energy, (it would give the right approach in the T=0 case)
**cuda** contains the cudac code and the python script to analyse data.
**python** folder contains my solution for generic couplings in the tile Monte_Carlo.ipynb and the solution provided during lecture.
**bga** seems to be interested, because although it does not converge soon, it seems that big domains do not form.
