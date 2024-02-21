# Fakeout

This is a simple game inspired by the 1976 game Breakout. The objective of the game is to break all of the
brightly-colored blocks at the top of the screen. To make this project, I relied only on the SDL library
for creating real-time graphical applications and plain-old C code. On Unix-based systems, the game can be
built and run using the provided shell script and CMakeLists.txt file. As I have time, I will try to update
this project in the future. I would like to eventually add power-ups to the game as well as maybe more varied
level design to make the experience a bit deeper.

## Installation

This project was created on a Unix-based machine. Specifically, I have only tested the development setup on a Mac.
To install the project: 

1. Download the required libraries. If using a Mac, each of these libraries can be installed with Homebrew.
    1. [SDL2](https://www.libsdl.org/)
    2. [SDL2_image](https://wiki.libsdl.org/SDL2_image/FrontPage)
    3. [SDL2_ttf](https://wiki.libsdl.org/SDL2_ttf/FrontPage)
2. Fork and clone this repository on your local machine.
3. After everything is installed, ensure that you are in the main project directory.
4. Run the bash script `run.sh`. You may have to give permission to run the script by typing `chmod +x run.sh`.

After this, the game should open in a new window.

## References

This project was loosely based off of the [SDL shooter game tutorial by Parallel 
Realities](https://www.parallelrealities.co.uk/tutorials/#shooter). I also used their [TTF
Tutorial](https://www.parallelrealities.co.uk/tutorials/#ttf) for help setting up and using the TTF library to
display text on screen. Lastly, the font used in the game is the [Press Start 2P Font by
codeman38](https://www.fontspace.com/press-start-2p-font-f11591). Thank you to all of these creators.
