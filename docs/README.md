# **2D Particle System** 

I am [Víctor Masó](https://www.linkedin.com/in/v%C3%ADctor-mas%C3%B3-garcia/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

> Download the latest release [here](https://github.com/nintervik/2D-Particle-System/releases)

***

## **Index**

* [1. Introduction](https://nintervik.github.io/2D-Particle-System/#1-introduction)
* [2. What is a Particle System and why do we care?](https://nintervik.github.io/2D-Particle-System/#2-what-is-a-particle-system-and-why-do-we-care)
  * [2.1 A bit of history](https://nintervik.github.io/2D-Particle-System/#21-a-bit-of-history)
  * [2.2 Particle systems nowadays](https://nintervik.github.io/2D-Particle-System/#22-particle-systems-nowadays)
  * [2.3 The components](https://nintervik.github.io/2D-Particle-System/#23-the-components)
    * [2.3.1 The emitters](https://nintervik.github.io/2D-Particle-System/#231-the-emitters)
    * [2.3.2 The particles](https://nintervik.github.io/2D-Particle-System/#232-the-particles)
* [3. Our approach](https://nintervik.github.io/2D-Particle-System/#3-our-approach)
* [4. TODOs](https://nintervik.github.io/2D-Particle-System/#4-todos)
* [5. Performance](https://nintervik.github.io/2D-Particle-System/#5-performance)
* [6. Improvements and further work](https://nintervik.github.io/2D-Particle-System/#6-improvements-and-further-work)
* [7. References](https://nintervik.github.io/2D-Particle-System/#7-references)
* [8. License](https://nintervik.github.io/2D-Particle-System/#8-license)

***

## **1. Introduction**

In this website I will explain what it is, how it works and how to program a 2D particle system in computer graphics. The system will be programmed in C++ using [Visual Studio 2017]( https://www.visualstudio.com/es/downloads/?rr=https%3A%2F%2Fwww.google.es%2F) as IDE, [SDL 2.0](https://www.libsdl.org/download-2.0.php) to render the graphics and [pugixml](https://pugixml.org/) for data parsing. The end goal of the tutorial is to success on creating a fire and smoke effect.

There are three main things that I will be focused on for this tutorial:
- **Generic and understandable.** Anyone, regardless of the lanaguage they're using or purpose should be able to understand the concepts and implement his own particle system from the information here presented. The system should be generic enough to be implemented in any project without almost any modification.
- **Good performance.** Particles can really affect framerate and performance so optimization is key. That's something we will take care of.
- **Well structured, robust and flexible system.** If you have a good structure, building new particle effects on top of it is not very difficult; it's just about adding and tweaking a few parameters. But the base underneath must be solid and work properly. This system should be flexible enough to develop new and more complex features on top of it.

Be aware that this web page is focused on the structure and behaviour of a 2D particle system but it assumes you have a base program loop and can render textures on screen at least. However, we will talk about the render part only for particle effects purposes, not the actual rendering of the texture.

Another important thing that I want to remark is that the way I'm going to explain how to implement the system is not unique and probably not the best. There are a lot of ways to do it and professional people that knows a lot more that I do. If you want to learn more about this topic I encourage you to check the [references](https://nintervik.github.io/2D-Particle-System/#references) that helped me doing this.

Well, without further delay let's get into playing with these particles!

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **2. What is a Particle System and why do we care?**

What is a particle system and why do we need one? Well, first let’s dig a bit into computer graphics stuff.

If you have programmed games or computer graphics related stuff is quite common to work with sprites and sprites sheets. For those unfamiliar with this term, a sprite is simply a two-dimensional bitmap used to be displayed on the screen. It is used especially in 2D videogames to render both static and animated elements of the game. It’s also very frequent to find them as a pixel art form. To save memory they are normally grouped into a same bitmap called sprite sheet. Down below there’s an example of a sprite sheet of Fire Man from the NES Mega Man game:

![77885](https://user-images.githubusercontent.com/25589509/37985238-841e7f38-31f8-11e8-96fe-99673a9012c1.png)

This example is very simple but sprites can become complex...

![super_sonic_1_sprite_sheet_by_winstontheechidna-dbhwb26](https://user-images.githubusercontent.com/25589509/37985355-cfefc1a6-31f8-11e8-8be3-9c2be803dc9e.png)

...a lot actually...

![sm](https://user-images.githubusercontent.com/25589509/37985996-9ec846b4-31fa-11e8-91b0-44b38edd1c7c.jpg)

So, what happens when we need something more organic, more chaotic; like a fire, a smoke, a fog, fireworks, snow… Yes, you’ve guessed it. It has to be drawn by hand by the artist. If the game has a low-res pixel art style it may not be a problem, but as the game becomes more detailed natural elements are more difficult to reproduce and if you have to timeline for your project this is a problem. 

This is a spritesheet of a fire caused by a a bomb in Gunbird (Psiskyo, 1994):

![tetsu_explosion_death](https://user-images.githubusercontent.com/25589509/37986157-0dd24af0-31fb-11e8-9aa3-6d9906ec676c.png)

You start to see the problem now right? What if the game is too complex to do it by a hand or is actually a 3D game? What if we want something like this:

![explosion_01_dribbble](https://user-images.githubusercontent.com/25589509/38469869-b738adf0-3b5b-11e8-9274-9273ebb50281.gif)

Well, that's when particle systems come into play.

A particle system is a structure that allows you to simulate particles of different types in an organic way with the advantage of just tweaking some particle properties to get the exact results you want very quickly and without effort. And the best part: you don’t have to draw any of these particles. You just need a base texture and that’s all. The system will be in charge of rendering the particles, the effects (such as glowing), physics calculations, emission rate and so on. You don't need to worry about anything, just playing around with it to get what you want.

This is just a generic description. Let's dive into more techical details of what this all means.

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

### **2.1 A bit of history**

Particle systems are very common in computer graphics and have been used since the early 1980s. One of the first implementations was seen in _Star Trek II: The Wrath of Khan_ in 1982. The film featured a sequence called Genesis Demo where a planet is terraformed by a torpedo to make it habitable. For achieving this effect William T. Reeves, a researcher at Lucasfilm Ltd, did a research on particle systems on a paper called [_Particle Systems - A Technique for Modeling a Class of Fuzzy Objects_](https://www.lri.fr/~mbl/ENS/IG2/devoir2/files/docs/fuzzyParticles.pdf).

This is the sequence mentioned above, as you can see the results are quite impressive considering the time this was done:

<iframe width="640" height="360" src="https://www.youtube.com/embed/QXbWCrzWJo4" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Reeves describes a particle system in this paper as follows:

> "_A particle system is a collection of many minute particles that together represent
a fuzzy object. Over a period of time, particles are generated into a system, move
and change from within the system, and die from the system._"

So basically a particle system contains a bunch of tiny objects called particles that have some kind of movement and a lifetime. These particles are generated and destroyed over time to simulate a flow. Hence, a particle system is the structure in charge of managing the living particles and generate new ones when needed.

Organic effects are difficult to simulate but what particle systems do is simplify the problem. Like in physics, we divide the effect in tiny and controllable particles that as a whole seems like something bigger that behaves as natural phenomenas. By managing a large group of these particles we can represent natural effects like water, fire or smoke so much easier than if we tried to treat it as a whole thing.

### **2.2 Particle systems nowadays**

Since the Genesis effects things have evolved quickly but the foundation is the same as before. Here's a short video on how Pixar Animation Studios uses particle systems nowadays. William T. Reeves is currently working there too!

<iframe width="854" height="480" src="https://www.youtube.com/embed/ovlVh-QgVao" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Nowadays particle systems can be found in any almost any game engine or 3D software. Maya and 3D Max have one as well as Unity or Unreal Engine. Particle are really important in a lot of videogames as it makes huge improvement. Particles makes the enviroment or the the player stands out and it really adds up a lot to the game. Let's see a few examples.

Take for example the next teamfight in League of Legends, as you can see particles makes a huge diiference when producing things like magic spells:

![LOLGIF](https://github.com/nintervik/Testing-Team-Workflow/blob/master/LOLGIF.gif?raw=true)

Now try to picture it without all this particle effects, it wouldn't' make sense right? 

But particle systems are also used to generate more realistic things like these explosions in Battlefield:

![battlefield](https://user-images.githubusercontent.com/25589509/38503370-2ecfc162-3c12-11e8-94b3-99a8159b6d0e.gif)

Or more subtle like the main menu in Hollow Knight:

![animated gif-downsized_large](https://user-images.githubusercontent.com/25589509/38541558-b983b330-3c9f-11e8-8ce9-21c143d985a4.gif)

Moreover, particle systems can be a double-edged sword too. Aside from being used for creating VFX as well as hiding visual bugs. For instance in this example, the X game does this by...

Put img here...

Okay now that you get the idea let's see what composes a particle system.

### **2.3 The components**

#### 2.3.1 The emitters

Particle systems usually contain what it's known as an emitter. An emittter is the object in charge of spawning all the particles and defining the particles behaviour and their properties. An emitter is in charge of the following things:

- Controlling the emission rate of particles. Basically how many particles are generated per frame.
- The postion where the particles are generated.
- Particles' velocity and movement.
- Particles life.
- Other particle properties like colors, transparency or size.

The emitter itself contains all the particles that will be updated and die over time. All this data is transfered from the emitter to all this particles so they behave like they are suposed to. Changing this data will change how the particles in that emitter will behave. 

A particle system can be composed of multiple different kind of emitters that at the same time can also have emitters inside of them. This inception thing can go as far as we want depending of what we want to simulate. For example, for the Genesis Effect Reeves explains in his paper that they used a tree structure in order to create this subemitters. By using this hierearchy there's a particle system which acts as a parent and contains subsystems that contains other subsystems.

#### 2.3.2 The particles

Now that we have the base, let's talk about particles. As said before particles inherit its properties from the emitter they came from. But what is exctly the particle itself? The particle itself it's just a simple moving texture that is renderered on screen. In 3D enviroments they use something called billboards which is basically an image that always faces the camera. But we don't need to worry about that as we will focus only in 2D.

This texture can be anything we want that fits our purpose. It's usually a balck and white fuzzy texture that will be tinted when rendered. A good example is this set of particle textures down below:

![particle_set](https://user-images.githubusercontent.com/25589509/38513650-29411102-3c2f-11e8-85b7-f3d5725da3f3.jpg)

Particle properties along with the emitter can be anything you like. The possibilities are endless. The Unity engine for example has big spectrum when it comes to emitters and particle properties, you can change anything you want and this flexibility allows you to generate almost any type of particle you can think of. You can choose the size, the color, the speed, the emitter shape, the texture and a lot more. Down below there's a screenshoot of this options in Unity.

![psystem_unity](https://user-images.githubusercontent.com/25589509/38539516-cc407fb4-3c98-11e8-9ae4-5d5439e189ba.PNG)

But how this particles are managed thorugh the system? do we need to generate a completly new particle each time? Will this affect the perdormance? We will discuss this in the next section.

When working in 3D enviroments particle textures are often mapped in a 3D geometry to create more interesting effects. This is called blending geometry and it's quite impressive! Here's a quick video on how particles are done in League of Legends using this technique.

<iframe width="854" height="480" src="https://www.youtube.com/embed/FUu2WNcJbtE" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Okay, I think that's enough theory for now, we must build the system in order to use it. So let's get to work!

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **3. Our approach**

Okay but what are we going to do? We will keep it simple but solid and flexible. Our particle system will have the following features:
- It will be 2D (although almost everything explained here can be transfered into 3D if needed).
- Particles movement will be linear but with the option of interpolate between start and end speed.
- An atlas full of particle textures will be used to render different types of particles.
- All data wil be outside the code, written in an xml file. 

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **4. TODOs**

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **5. Performance**

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **6. Improvements and further work**

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **7. References**

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)


***

## **8. License**

~~~~~~~~~~~~~~~

MIT License

Copyright (c) 2018 nintervik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

~~~~~~~~~~~~~~~

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)
