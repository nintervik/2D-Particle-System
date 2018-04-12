# 2D-Particle-System

A hand coded 2D Particle System. The system will be programmed in C++ using [Visual Studio 2017]( https://www.visualstudio.com/es/downloads/?rr=https%3A%2F%2Fwww.google.es%2F) as IDE, [SDL 2.0](https://www.libsdl.org/download-2.0.php) to render the graphics and [pugixml](https://pugixml.org/) for data parsing. The end goal of the tutorial is to success on creating a fire and smoke effect.

There are three main things that I will be focused on for this tutorial:
- **Generic and understandable.** Anyone, regardless of the lanaguage they're using or purpose should be able to understand the concepts and implement his own particle system from the information here presented. The system should be generic enough to be implemented in any project without almost any modification.
- **Good performance.** Particles can really affect framerate and performance so optimization is key. That's something we will take care of.
- **Well structured, robust and flexible system.** If you have a good structure, building new particle effects on top of it is not very difficult; it's just about adding and tweaking a few parameters. But the base underneath must be solid and work properly. This system should be flexible enough to develop new and more complex features on top of it.

* [Github repository](https://github.com/nintervik/2D-Particle-System)  
* [Website](https://nintervik.github.io/2D-Particle-System/)
* [Release](https://github.com/nintervik/2D-Particle-System/releases)

## Installation instructions

Download the zip file and unzip it. Open the folder, execute the .exe and enjoy!

_IMPORTANT: do not modify, change or add any folder or file (unless specified) as you might not be able to execute the application._

## Notes on performance

Be aware that creating a lot of emitters with high emission rates might result in a bad performance.

## Controls

### Keyboard and mouse:

- Right click to create a fire emitter
- Number 2 to create a fire emitter without smoke
- Number 3 to create a green fire with purple smoke
- Return key to remove all emitters
- ESC to close application

You can change the attributes of the three emitters by changing the its attributes inside the xml file called psystem_config.


## Tools used
* IDE: Microsoft Visual Studio 2017
* Language: C++
* Graphics and audio: SDL 2.0
* Data: pugixml 1.8
* Profiler: Brofiler
* Code repository: GitHub
* Others: Adobe Photoshop CS6

## Sprites

- <https://opengameart.org/content/lens-flares-and-particles>
