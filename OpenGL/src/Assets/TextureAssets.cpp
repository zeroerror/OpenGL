#include "TextureAssets.h"

TextureAssets::TextureAssets() {
    allTextures = std::hash_map<unsigned int, Texture*>();
}

TextureAssets::~TextureAssets() {}

unsigned int TextureAssets::LoadTexture(const char* path) {
	Texture* texture = new Texture(path);
	allTextures.insert(std::pair<unsigned int, Texture*>(texture->GetID(), texture));
}

void TextureAssets::UseTexture(unsigned int textureID) {
	allTextures[textureID]->Bind();
}

void TextureAssets::DeleteTexture(unsigned int textureID) {
	allTextures[textureID]->~Texture();
}

void TextureAssets::DeleteAllTexture() {
	for (int i = 0; i < allTextures.size(); i++) {
		allTextures[i]->~Texture();
	}
}