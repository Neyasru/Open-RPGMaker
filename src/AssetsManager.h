#ifndef _ASSETSMANAGER_H_
#define _ASSETSMANAGER_H_

#include <map>
#include <string>
#include "Texture.h"
//#include "Font.h"
//#include "Audio.h"

class AssetsManager {
public:
	AssetsManager();

	void loadImages();
	void loadMusics();
	void loadSounds();
	void loadFonts();

	Texture* getTexture(string code);
	//Font*  getFont(font_code code);
	//Audio* getMusic(music_code code);
	//Audio* getSound(sound_code code);

	~AssetsManager();

private:
	map<string, Texture*> textures;
	map<string, bool> textureLoaded;
	//map<string, Font*> fonts;
	//map<string, Audio*> musics;
	//map<string, Audio*> sounds;
};

#endif
