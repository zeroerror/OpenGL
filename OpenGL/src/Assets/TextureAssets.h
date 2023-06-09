#pragma once
#include <hash_map>
#include <Texture.h>

class TextureAssets {

public:
	TextureAssets() {}
	~TextureAssets() {}

	unsigned int LoadTexture(const char* path);
	void UseTexture(unsigned int shader);
	void DeleteTexture(unsigned int shader);
	void DeleteAllTexture();

private:
	std::hash_map<unsigned int, Texture*> allTextures;

};

