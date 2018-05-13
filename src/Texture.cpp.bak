#include "Texture.h"

using namespace std;

SDL_Texture* Texture::LoadTexture(const char* file)
{
	SDL_Surface* tempSurface = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::instance().renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}

SDL_Texture* Texture::get(){
	return texture;
}

void Texture::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Engine::instance().renderer, tex, &src, &dest, NULL, NULL, flip);
}

Texture::Texture(const char* file){
	texture = LoadTexture(file);
}

