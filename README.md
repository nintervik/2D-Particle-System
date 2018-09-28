# 2D-Particle-System1

I am [Víctor Masó](https://www.linkedin.com/in/v%C3%ADctor-mas%C3%B3-garcia/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

***

A hand coded 2D Particle System. The system will be programmed in C++ using [Visual Studio 2017]( https://www.visualstudio.com/es/downloads/?rr=https%3A%2F%2Fwww.google.es%2F) as IDE, [SDL 2.0](https://www.libsdl.org/download-2.0.php) to render the graphics and [pugixml](https://pugixml.org/) for data parsing. The end goal of the tutorial is to success on creating a fire and smoke effect.

There are three main things that I will be focused on for this tutorial:
- **Generic and understandable.** Anyone, regardless of the lanaguage they're using or purpose should be able to understand the concepts and implement his own particle system from the information here presented. The system should be generic enough to be implemented in any project without almost any modification.
- **Good performance.** Particles can really affect framerate and performance so optimization is key. That's something we will take care of.
- **Well structured, robust and flexible system.** If you have a good structure, building new particle effects on top of it is not very difficult; it's just about adding and tweaking a few parameters. But the base underneath must be solid and work properly. This system should be flexible enough to develop new and more complex features on top of it.

* [Github repository](https://github.com/nintervik/2D-Particle-System)  
* [Website](https://nintervik.github.io/2D-Particle-System/)
* [Releases](https://github.com/nintervik/2D-Particle-System/releases)

## Installation instructions

Download the zip file and unzip it. Open the folder, execute the .exe and enjoy!

_IMPORTANT: do not modify, change or add any folder or file (unless specified) as you might not be able to execute the application._

## Notes on performance

Be aware that creating a lot of emitters with high emission rates might result in a bad performance. Due to physics movement calculations, performance gets worser when there are vortices on the scene. Also don't spawn a lot of smoke emitters as they genereate a lot of particles.

## Controls

### Keyboard and mouse:

Emitters creation:
- RIGHT CLICK: to create a fire emitter that follows the torch
- NUM 1: Explosion 1
- NUM 2: Flame
- NUM 3: Purple fire
- NUM 4: Bubbles
- NUM 5: Explosion 2
- NUM 6: Smoke
- NUM 7: Spark
- NUM 8: Pixel smoke

General:
- RETURN: remove all emitters
- S: Stop fire emitter for 5 seconds
- D: Start fire emitter for 5 seconds
- O: Turn on vortex sensitive on purple flame emitter
- F: Turn off vortex sensitive on purple flame emitterg
- ESC: exit application

You can change the attributes of the emitters by changing its attributes inside the xml file called psystem_config. You can also add new ones if needed. Remeber to increase MAX_NUM_EMITTERS_TYPE to store the number of emitters you need.

## Changelog

v0.1
- 2D Particle System implemented
- Just fire and color changing fire implemented

v0.2
- Improved particle system structure
- Added a lot of new emitter types
- Added methods to start and stop emitters
- Minor bugs solved
- Optimized memory management

v0.3 
- Changed string compare methods
- Removed unnecessary comments
- Optimized particle removing process 
- More error control when blitting textures on screen
- Improved define names
- Added xml extension to psystem_config file
- Solved memory leaks in texture module
- Vortex control through xml
- Vortex method to switch it on or off for each emitter
- Minor bugs fixed

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