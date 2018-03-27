
# **2D Particle System** 

I am [Víctor Masó](https://www.linkedin.com/in/v%C3%ADctor-mas%C3%B3-garcia/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

***

## **Index**

* Introduction
* What is a Particle System and why do we care?
* References

***

## **Introduction**

In this website I will explain what it is, how it works and how to program a 2D Particle System in computer graphics. The system will be programmed in C++ using Visual Studio 2017 as IDE and SDL 2.0 to render the graphics. The end goal of the tutorial is to success on creating a fire and smoke effect.

There are three main things that I wll be focused on for this tutorial:
- **Generic and understandable.** Anyone, regardless of the lanaguage they're using or purpose should be able to understand the concepts and implement his own particle system from the information here presented. The system should be generic enough to be implemented in any project without almost any modification.
- **Good performance.** Particles can really affect framerate and performance so it's important to manage in an optimized way. That's something we will take care of.
- **Well structured, robust and flexible system.** If you have a good structure, building new particle effects on top of it is not very difficult; it's just about adding and tweaking a few parameters. But the base underneath must be solid and work properly. This system should be flexible enough to develop new and more complex features on top of it.

Be aware that this web page is focused on the structure and behaviour of a 2D particle system but it assumes you have a base program loop and can render textures on screen at least. However, we will talk about the render part only for particle effects purposes, not the actual rendering of the texture.

Another important thing that I want to remark is that the way I'm going to explain how to implement the system is not unique and probably not the best. There are a lot of ways to do it and professional people that knows a lot more that I do. If you want to learn more about this topic I encourage you to check the references that helped me doing this.

Well, without further delay let's get into playing with these particles!

***

## **What is a Particle System and why do we care?**

Back in the old days...
