# **2D Particle System** 

I am [Víctor Masó](https://www.linkedin.com/in/v%C3%ADctor-mas%C3%B3-garcia/), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

> Download the latest release [here](https://github.com/nintervik/2D-Particle-System/releases)

***

## **Index**

* [1. Introduction](https://nintervik.github.io/2D-Particle-System/#1-introduction)
* [2. What is a Particle System and why do we care?](https://nintervik.github.io/2D-Particle-System/#2-what-is-a-particle-system-and-why-do-we-care)
  * [2.1 A bit of history](https://nintervik.github.io/2D-Particle-System/#21-a-bit-of-history)
  * [2.2 Particle systems nowadays](https://nintervik.github.io/2D-Particle-System/#22-particle-systems-nowadays)
* [Our approach](https://nintervik.github.io/2D-Particle-System/#our-approach)
* [References](https://nintervik.github.io/2D-Particle-System/#references)
* [License](https://nintervik.github.io/2D-Particle-System/#license)

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

So basically a particle system contains a bunch of tiny objects called particles that have somo kind of movement and a lifetime. These particles are generated and destroyed over time to simulate a flow. Hence, a particle system is the structure in charge of managing the living particles and generate new ones when needed.

Organic effects are difficult to simulate but what particle systems do is simplify the problem. Like in physics, we divide the effect in tiny and controllable particles that as a whole seems like something bigger that behaves as natural phenomenas. By managing a large group of these particles we can represent natural effects like water, fire or smoke so much easier than if we tried to treat it as a whole thing.

### **2.2 Particle systems nowadays**

Since the Genesis effects things have evolved quickly but the foundation is the same as before. Here's a short video on how Pixar Animation Studios uses particle systems nowadays. William T. Reeves is currently working there too!

<iframe width="854" height="480" src="https://www.youtube.com/embed/ovlVh-QgVao" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Nowadays particle systems can be found in any almost any game engine or 3D software. Maya and 3D Max have one as well as Unity or Unreal Engine. Particle are really important in a lot of videogames as it makes huge improvement. Particles makes the enviroment or the the player stands ou and it really adds up a lot to the game. Let's see a few examples.

Take for example the next teamfight in League of Legends, as you can see particles makes a huge diiference when produing things like magic spells:

![LOLGIF](https://github.com/nintervik/Testing-Team-Workflow/blob/master/LOLGIF.gif?raw=true)

Now try to picture it without all this particle effects, it wouldn't' make sense right? 

But particle systems are also used to generate more realistic things like these explosions in Battlefield:

![battlefield](https://user-images.githubusercontent.com/25589509/38503370-2ecfc162-3c12-11e8-94b3-99a8159b6d0e.gif)

Or more subtle like the main menu in Hollow Knight:
Put here here...

Moreover, particle systems can be a double-edged sword too. Aside from being used for creating VFX as well as hiding visual bugs. For instance in this example, the X game does this by...

Put img here...

Okay now that you get the idea let's see what composes a particle system.

### **2.3 The components**

#### The emitters

Particle systems usually contain what it's known as an emitter. An emittter is the object in charge of spawning all the particles and defining the particles behaviour and their properties. An emitter is in charge of the following things:

- Controlling the emission rate of particles. Basically how many particles are generated per frame.
- The postion where the particles are generated.
- Particles' velocity and movement.
- Particles life.
- Other particle properties like colors, transparency or size.

The emitter itself contains all the particles that will be updated and die over time. All this data is transfered from the emitter to all this particles os they behave like they are suposed to. Changing this data will change how the particles in that emitter will behave. 

A particle system can be composed of multiple different kind of emitters that at the same time can also have emitters inside of them. This inception thing can go as far as we want depending of what we want to simulate. For example, for the Genesis Effect Reeves explains in his paper that they used a tree structure in order to create this subemitters. By using this hierearchy there's a particl system whic acts as a parent and contain subsystems that contains other subsystems.

#### The particles

Now that we have the base, let's talk about particles.



<iframe width="854" height="480" src="https://www.youtube.com/embed/FUu2WNcJbtE" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

This is very nice, but first we must build the system in order to use it. So let's get to work!

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **Our approach**

-	Talk about what we are going to do (2D, not 3D!)

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)

***

## **References**

[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)


***

## **License**


[**Back to index**](https://nintervik.github.io/2D-Particle-System/#index)
