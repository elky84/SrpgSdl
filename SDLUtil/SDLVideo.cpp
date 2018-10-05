#include "SDLVideo.h"

SDL_Surface* SDLVideo::CreateSurface(DWORD flag, int width, int height, BYTE bpp, BYTE rMask, BYTE gMask, BYTE bMask, BYTE aMask)
{
	return SDL_CreateRGBSurface(flag, width, height, bpp, rMask, gMask, bMask, aMask);
}

SDL_Surface*  SDLVideo::LoadImg(char* filename)
{
	// The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL; 
	SDL_Surface* loadedImage = IMG_Load(filename); 
	if( loadedImage != NULL ) 
	{ 
		// Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 

		// Free the old image 
		SDL_FreeSurface( loadedImage ); 
	}
	else
	{
		loadedImage->flags = 5;
		FILE* fp = NULL;
		fopen_s(&fp, "error.txt", "wt+");
		if(fp)
		{
			fprintf(fp, "%s", SDL_GetError());
			fclose(fp);
		}
	}
	// Return the optimized image 
	return optimizedImage; 
}


SDL_Surface* SDLVideo::LoadImgColorKey(char* filename, DWORD colorkey)
{
	SDL_Surface* image = LoadImg(filename);
	if(image) SetColorKey(image, colorkey);
	return image;
}

SDL_Surface* SDLVideo::LoadImgAlpha(char* filename, BYTE alpha)
{
	SDL_Surface* image = LoadImg(filename);
	if(image) SetAlpha(image, alpha);
	return image;
}

void SDLVideo::SetAlpha(SDL_Surface* surface, BYTE alpha)
{
	SDL_SetAlpha(surface, SDL_SRCALPHA, alpha);
}

void SDLVideo::SetColorKey(SDL_Surface* image, DWORD colorkey)
{
	//Map the color key
	Uint32 nRealColorkey = SDL_MapRGB(image->format, GetRValue(colorkey), GetGValue(colorkey), GetBValue(colorkey) );

	//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
	SDL_SetColorKey(image, SDL_RLEACCEL | SDL_SRCCOLORKEY, nRealColorkey ); 
}



bool SDLVideo::Lock(SDL_Surface* image)
{
	if(SDL_MUSTLOCK(image)){
		if(SDL_LockSurface(image) < 0){
			return false;
		}
	}
	return true;
}

void SDLVideo::Fill(SDL_Surface* surface, DWORD color)
{
	SDL_FillRect(surface, NULL, color);
}

void SDLVideo::Unlock(SDL_Surface* image)
{
	if(SDL_MUSTLOCK(image)) {
		SDL_UnlockSurface(image);
	}
}

SDL_Surface* SDLVideo::InvertImage(SDL_Surface* image, SDL_Rect* srcrect)  //같은 비트로 이뤄진 표면이어야 한다.
{
	SDL_Surface* temp = CreateSurface(SDL_HWSURFACE, srcrect->w, srcrect->h, image->format->BitsPerPixel);
	if(!Lock(image) || !Lock(temp))
	{
		SDL_FreeSurface(temp);
		return NULL;
	}

	for(int y = 0; y < srcrect->h; y++)
	{
		for(int x = 0; x < srcrect->w; x++)
		{
			switch (temp->format->BytesPerPixel) 
			{
			case 1:  /* 8-bpp 라고 가정*/
				{
					Uint8* bufp = (Uint8* )temp->pixels + y*temp->pitch + x + srcrect->x;
					*bufp =* ((Uint8* )image->pixels + y*image->pitch + srcrect->x + srcrect->w -1 - x);
					break;
				}
			case 2: /* 아마 15-bpp 아니면 16-bpp*/
				{ 
					Uint16* bufp = (Uint16* )temp->pixels + y*temp->pitch / 2 + x + srcrect->x;
					*bufp =* ((Uint16* )image->pixels + y*image->pitch / 2 + srcrect->x + srcrect->w -1 -x);
					break;
				}
			case 3: /* 느린 24-bpp mode, 보통 사용되지 않는다*/
				{ 
					Uint8* bufp = (Uint8* )temp->pixels + y*  temp->pitch + (x + srcrect->x)*  3;
					bufp[0] =* ((Uint8* )image->pixels + y*  image->pitch + (srcrect->x + srcrect->w -1 - x)*  3);
					bufp[1] =* ((Uint8* )image->pixels + y*  image->pitch + (srcrect->x + srcrect->w -1 - x)*  3 + 1);
					bufp[2] =* ((Uint8* )image->pixels + y*  image->pitch + (srcrect->x + srcrect->w -1 - x)*  3 + 2);
					break;
				}
			case 4: /* 아마 32-bpp*/
				{ 
					Uint32* bufp = (Uint32* )temp->pixels + y*temp->pitch/4 + x + srcrect->x;
					*bufp =* ((Uint32*)image->pixels + y*image->pitch/4 + srcrect->x + srcrect->w -1 - x);
					break;
				}
			}	
		}
	}

	Unlock(image);
	Unlock(temp);
	return temp;
}

SDLVideo::SDLVideo(int width, int height, BYTE bpp, DWORD flag)
{
	m_Screen = SDL_SetVideoMode(width, height, bpp, flag);
	if ( m_Screen == NULL ) {
		fprintf(stderr, "Unable to set %dx%d [%d, %d] video: %s\n", width, height, bpp, flag, SDL_GetError());
		exit(1);
	}

	m_nWidth = width;
	m_nHeight = height;
	m_nBpp = bpp;

	m_EffectSurface = CreateSurface(SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA, width, height, bpp, 0, 0, 0, 0);
	Fill(m_EffectSurface);
	m_Effect = NULL;
}

SDLVideo::~SDLVideo()
{
	SDL_FreeSurface(m_EffectSurface);
	SDL_FreeSurface(m_Screen);
}

void SDLVideo::Blit(SDL_Surface* image, int x, int y)
{
	static SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = image->w + x;
	rect.h = image->h + y;
	SDL_BlitSurface(image, NULL, m_Screen, &rect);
}

void SDLVideo::Blit(SDL_Surface* image)
{
	SDL_BlitSurface(image, NULL, m_Screen, NULL);
}

void SDLVideo::Blit(SDL_Surface* image, SDL_Rect* srcrect, int x, int y)
{
	if(image == NULL || srcrect == NULL) return;

	static SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = image->w + x;
	rect.h = image->h + y;

	SDL_BlitSurface(image, srcrect, m_Screen, &rect);
}

void SDLVideo::Blit(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dest, SDL_Rect* destrect)
{
	if(src == NULL || dest == NULL) return;
	SDL_BlitSurface(src, srcrect, dest, destrect);
}

void SDLVideo::DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color = SDL_MapRGB(m_Screen->format, r, g, b);
	if(Lock(m_Screen)){
		return;
	}

	switch (m_Screen->format->BytesPerPixel) 
	{
	case 1:  /* 8-bpp 라고 가정*/
		{
			Uint8* bufp = (Uint8* )m_Screen->pixels + y*m_Screen->pitch + x;
			*bufp = color;
			break;
		}
	case 2: /* 아마 15-bpp 아니면 16-bpp*/
		{ 
			Uint16* bufp = (Uint16* )m_Screen->pixels + y*m_Screen->pitch/2 + x;
			*bufp = color;
			break;
		}
	case 3: /* 느린 24-bpp mode, 보통 사용되지 않는다*/
		{ 
			Uint8* bufp = (Uint8* )m_Screen->pixels + y*m_Screen->pitch + x*  3;
			if(SDL_BYTEORDER == SDL_LIL_ENDIAN) 
			{
				bufp[0] = color;
				bufp[1] = color >> 8;
				bufp[2] = color >> 16;
			} 
			else 
			{
				bufp[2] = color;
				bufp[1] = color >> 8;
				bufp[0] = color >> 16;
			}
			break;
		}
	case 4: /* 32-bpp*/
		{ 
			Uint32* bufp = (Uint32* )m_Screen->pixels + y*m_Screen->pitch/4 + x;
			*bufp = color;
			break;
		}
	}

	Unlock(m_Screen);
}

void SDLVideo::Flip()
{
	if(m_Effect)
	{
		(this->*m_Effect)();
	}
	SDL_Flip(m_Screen);
}

void SDLVideo::SetFadeOut()
{
	m_Effect = &SDLVideo::FadeOut;
}

void SDLVideo::FadeOut()
{
	static BYTE i = 0;
	i += 5;
	if(255 <= i)
	{
		i = 0;
		EffectEnd();
	}

	if(m_Effect)
	{
		SetAlpha(m_EffectSurface, i);
		Blit(m_EffectSurface, 0, 0);
	}
}

void SDLVideo::SetEffect(void (SDLVideo::*EffectFunc)())
{
	m_Effect = EffectFunc;
}

void SDLVideo::SetFadeIn()
{
	m_Effect = &SDLVideo::FadeIn;
}

void SDLVideo::FadeIn()
{
	static BYTE i = 255;
	i -= 5;
	if(i <= 0)
	{
		i = 255;
		EffectEnd();
		return;
	}

	SetAlpha(m_EffectSurface, i);
	Blit(m_EffectSurface, 0, 0);
}

void SDLVideo::EffectEnd()
{
	m_Effect = NULL;
}