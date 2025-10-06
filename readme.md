# N Body Simulation
<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <p>This is a N Body simulation prjoect developed for the Scientific Programming and software designe course held by prof. Schramm at university of Geneve. 
        <p>The code is written majorly in C++ using the OOP principles.</p>
        <p> Some scritps in pyhton are later implemented to analyse the datas produced during the simulation <p>
    <div>

 <div>       


# Table of contents
- [N Body Simulation](#n-body-simulation)
- [Table of contents](#table-of-contents)
- [Getting started](#getting-started)
    - [Compile with make](#compile-with-make)
- [Usage](#usage)
- [Animations](#animations)
- [License](#license)


# Getting started
To use the code, clone the repository from your terminal with the following command:
```shell
git clone git@github.com:GiovanniPellegrini/N-body-simulation.git
```

This will create a folder named `N-body-simulation` in your current directory.

### Compile with make

You can run the code using the `makefile`

    make

This will compile the main with alla the dependecies and the programm will be ready to use.

# Usage

After running `./main`, the terminal will display the following message 

 ```shell
Usage: ./main <run_name> <input.txt> <config.txt>
```  
where 
- `run_name` is name of the directory that is created where all useful simulation results will be stored.
- `input.txt` is the file where all bodies in the simulation are declared (see [Tutorial](https://github.com/GiovanniPellegrini/N-Body-Simulation/blob/main/Tutorial.md)
- `config.txt` is where all the parameters of the simulations are specified (see [Tutorial](https://github.com/GiovanniPellegrini/N-Body-Simulation/blob/main/Tutorial.md))

Each simulation will create two file `positions.txt` and `energies.txt`, which can be  analyse and display through the two phyton scripts `analyse_positions.py` and `analyse_energies.py` 

Each python script can still be used separately using the command line:
```shell
python <python_FileName> <run_name> <file>
```
- `python_FileName` is `analyse_positions.py/analyse_energies.py` 
- `run_name` is the direcotry where the results of the simulations are stored.
- `file` is `positions.txt/energies.txt`

A shell script is implemented to concatenare tutti questi comandi compilando semplicemente 

 ```shell
./run.sh <run_name> <input_file> <config_file>
```

so for example:
 ```shell
./run.sh solar_system solar_system.txt config_solar_sysyem.txt
```

# Animations


If you want to create an animation you can use the script `analyse_positions_animations.py` which use the libraries FuncAnimation, PillowWriter from matplotlib.animation

# License

N Body Simulation is licensed under the MIT License. See the [license.txt](https://github.com/GiovanniPellegrini/not_intellij_idea/blob/master/license.txt) file for details.

- **Open a pull request**: If you have written code that improves the project, you can submit it as a pull request.
- **Report bugs**: If you find a bug, you can report it by creating an issue. Please provide a detailed description of the bug and include the steps necessary to reproduce it.

You can contact me on my github profile
-[Giovanni Pellegrini](https://github.com/GiovanniPellegrini)
