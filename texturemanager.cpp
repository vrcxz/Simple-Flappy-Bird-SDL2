static SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
	SDL_Surface *img = IMG_Load(path);
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);

	return texture;
}