#include "TextureManager.hpp"

TextureManager::TextureManager()
{
	if (!TextureAsset::IsRegistered(U"laraCroft")) {
		TextureAsset::Register(U"laraCroft", U"image/LaraCroft_804x2279.png");
	}
}
