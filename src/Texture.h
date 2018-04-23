#ifndef _TEXTURE_INCLUDE
#define _TEXTURE_INCLUDE

#include "Engine.h"

using namespace std;

enum PixelFormat {TEXTURE_PIXEL_FORMAT_RGB, TEXTURE_PIXEL_FORMAT_RGBA};

// The texture class loads images an passes them to OpenGL
// storing the returned id so that it may be applied to any drawn primitives

class Texture
{
public:
	SDL_Texture* LoadTexture(const char* fileName);
	void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	SDL_Texture* get();
	Texture(); 
	Texture(const char* filename);
/*
public:
	Texture(); 
	Texture(const string &filename, PixelFormat format);

	bool loadFromFile(const string &filename, PixelFormat format);
	void loadFromGlyphBuffer(unsigned char *buffer, int width, int height);

	void createEmptyTexture(int width, int height);
	void loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height);
	void generateMipmap();
	
	void setWrapS(GLint value);
	void setWrapT(GLint value);
	void setMinFilter(GLint value);
	void setMagFilter(GLint value);
	
	void use() const;
	
	int width() const { return widthTex; }
	int height() const { return heightTex; }
*/
private:
	SDL_Texture* texture;
/*	int widthTex, heightTex;
	GLuint texId;
	GLint wrapS, wrapT, minFilter, magFilter;
*/
};

#endif // _TEXTURE_INCLUDE

