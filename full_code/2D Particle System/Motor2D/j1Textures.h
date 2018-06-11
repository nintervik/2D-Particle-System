#ifndef __j1TEXTURES_H__
#define __j1TEXTURES_H__

#include "j1Module.h"
#include <list>

struct SDL_Texture;
struct SDL_Surface;

class j1Textures : public j1Module
{
public:

	j1Textures();
	virtual ~j1Textures();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();

	SDL_Texture* const	Load(const char* path);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	std::list<SDL_Texture*> textures;
};


#endif