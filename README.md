### SFML configuration in visual studio
* open the .sln file in visual studio
* choose debug mode 
* left click on the project in the solution explorer and open properties
* c++ -> general add $(SolutionDir)\SFML-2.5.1\include in the additional include directories
* go to linker -> general add $(SolutionDir)\SFML-2.5.1\include in the additional library directory
* then go to input tab and add those in the additional dependencies 
    opengl32.lib
    sfml-system-d.lib
    sfml-window-d.lib
    sfml-graphics-d.lib
    sfml-main-d.lib
* the dll files are already in directory of the exe file , just run build and run
