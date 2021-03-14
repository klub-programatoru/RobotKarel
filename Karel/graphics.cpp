
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <cstdio>
#include <math.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"

using namespace std;

Obrazovka::Obrazovka()
{
	x = 0;
	y = 0;
}

Obrazovka *Obrazovka::instance()
{
	static Obrazovka inst;
	return &inst;
}

void Obrazovka::inicializuj(const char *name, const unsigned int sirka, const unsigned int vyska, const unsigned int vlajky)
{
	w = sirka;
	h = vyska;
	// name = name;
	// vlajky = vlajky;

	// Inicializuji grafickou knihovnu
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		printf("SDL_Init() selhalo: %s\n", SDL_GetError());
		exit(1);
	}

	// Otevru okno na obrazovce
	if (!(gWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, vlajky)))
	{
		printf("SDL_SetVideoMode() selhalo: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	else
	{
		gScreenSurface = SDL_GetWindowSurface(gWindow);
	}
}

void Obrazovka::getWindow(SDL_Window *&cWindow)
{
	cWindow = gWindow;
}

void Obrazovka::umisti(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Obrazovka::pohni(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Obrazovka::aktualizuj()
{
	SDL_UpdateWindowSurface(gWindow);
}

void Obrazovka::smaz()
{
	SDL_FillRect(gScreenSurface, NULL, 0);
}
void Obrazovka::zavri()
{
	//Destroy window
	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
	exit(1);
}

void Obrazovka::zamkni()
{
	if ((SDL_MUSTLOCK(gScreenSurface)) && (SDL_LockSurface(gScreenSurface) < 0))
	{
		printf("Can't lock screen: %s\n", SDL_GetError());
		return;
	}
}

void Obrazovka::odemkni()
{
	if (SDL_MUSTLOCK(gScreenSurface))
		SDL_UnlockSurface(gScreenSurface);
}

Uint32 Obrazovka::getpixel(int x, int y)
{
	if (x < 0 || x >= w || y < 0 || y >= h)
		return 0;

	int bpp = gScreenSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)gScreenSurface->pixels + y * gScreenSurface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *)p;

	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}

void Obrazovka::putpixel(int x, int y, Uint32 pixel)
{
	if (x < 0 || x >= w || y < 0 || y >= h)
		return;

	Uint8 *p = (Uint8 *)gScreenSurface->pixels + y * gScreenSurface->pitch + x * gScreenSurface->format->BytesPerPixel;

	switch (gScreenSurface->format->BytesPerPixel)
	{
	case 1:
		*p = pixel;
		break;
	case 2:
		*(Uint16 *)p = pixel;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

Obrazek::Obrazek()
{
	this->gSurface = NULL;
	x = y = vx = vy = ax = ay = ox = oy = 0;
	w = h = 0;
	obrazovka = Obrazovka::instance();
}

// Destruktor
Obrazek::~Obrazek()
{
	SDL_FreeSurface(gSurface);
}

// Nacteni obrazku z disku do pameti
void Obrazek::nacti(const char *filename)
{
	gSurface = SDL_GetWindowSurface(obrazovka->gWindow);
	gHelloWorld = IMG_Load(filename);
	if (!gHelloWorld)
	{
		printf("Chyba nacitni obrazku! %s \n", IMG_GetError());
		SDL_Quit();
		exit(1);
	}
}

// Nacteni obrazku z disku do pameti v std strigu
/*void Obrazek::nacti(std::string filename)
{
	nacti(filename.c_str());
}*/

// Nedovol objektu opustit obrazovku
void Obrazek::meze()
{
	if (this->x < 0)
		this->x = 0;
	if (this->y < 0)
		this->y = 0;
	if (this->x > obrazovka->w - this->w)
		this->x = obrazovka->w - this->w;
	if (this->y > obrazovka->h - this->h)
		this->y = obrazovka->h - this->h;
}

// Presun pocatek objektu
void Obrazek::pocatek(float px, float py)
{
	ox = px;
	oy = py;
}

// Presun objektu na zadane souradnice
void Obrazek::umisti(float px, float py)
{
	x = px;
	y = py;
}

// Pohyb objektu o zadanou vzdalenost
void Obrazek::pohni(float px, float py)
{
	x += px;
	y += py;
}

// Nastav rychlost automatickeho pohybu
void Obrazek::rychlost(float x, float y)
{
	vx = x;
	vy = y;
}

void Obrazek::zrychleni(float x, float y)
{
	ax = x;
	ay = y;
}

// Aktualizuj automaticke pohyby
void Obrazek::aktualizuj()
{
	vx += ax;
	vy += ay;
	x += vx;
	y += vy;
	//printf("%f,%f %f,%f %f,%f\n", x, y, vx, vy, ax, ay);
}

// Vykresleni objektu na obrazovku
void Obrazek::kresli()
{
	SDL_Rect drect;

	drect.x = (int)round(x - ox - obrazovka->x);
	drect.y = (int)round(y - oy - obrazovka->y);
	SDL_BlitSurface(this->gHelloWorld, NULL, gSurface, &drect);
}

// Zjistime kolizi
int Obrazek::kolize(Obrazek *o)
{
	if (
		(o->x - o->ox + o->w) >= this->x - this->ox && o->x - o->ox <= (this->x - this->ox + this->w) && (o->y - o->oy + o->h) >= this->y - this->oy && o->y - o->oy <= (this->y - this->oy + this->h))
		return 1;
	else
		return 0;
}

Uint32 Obrazek::getpixel(int x, int y)
{
	int bpp = this->gSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)this->gSurface->pixels + y * this->gSurface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *)p;

	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}

// Jednoduche globalni kreslici funkce

Uint32 pixel = 0;
int lx = 0, ly = 0;

#define BILA 255, 255, 255
#define CERVENA 255, 0, 0
#define ZELENA 0, 255, 0
#define MODRA 0, 0, 255
#define AZUROVA 0, 255, 255
#define PURPUROVA 255, 0, 255
#define ZLUTA 255, 255, 0

void barva(unsigned char r, unsigned char g, unsigned char b)
{
	Obrazovka *obrazovka = Obrazovka::instance();
	pixel = SDL_MapRGB(obrazovka->gScreenSurface->format, r, g, b);
}

void bod(int x, int y)
{
	Obrazovka *obrazovka = Obrazovka::instance();

	obrazovka->zamkni();
	obrazovka->putpixel(x - obrazovka->x, y - obrazovka->y, pixel);
	obrazovka->odemkni();

	lx = x;
	ly = y;
}

void cara(int x1, int y1, int x2, int y2)
{
	Obrazovka *obrazovka = Obrazovka::instance();

	int i, a;
	float k, p;

	x1 -= obrazovka->x;
	x2 -= obrazovka->x;
	y1 -= obrazovka->y;
	y2 -= obrazovka->y;

	lx = x2;
	ly = y2;

	obrazovka->zamkni();

	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		if (x2 < x1)
		{
			a = y1;
			y1 = y2;
			y2 = a;
			a = x1;
			x1 = x2;
			x2 = a;
		}

		k = (float)(y2 - y1) / (x2 - x1);
		for (i = x1, p = y1; i <= x2; i++, p += k)
		{
			obrazovka->putpixel(i, (int)p, pixel);
		}
	}
	else
	{
		if (y2 < y1)
		{
			a = y1;
			y1 = y2;
			y2 = a;
			a = x1;
			x1 = x2;
			x2 = a;
		}

		k = (float)(x2 - x1) / (y2 - y1);
		for (i = y1, p = x1; i <= y2; i++, p += k)
		{
			obrazovka->putpixel((int)p, i, pixel);
		}
	}
	obrazovka->odemkni();
}

void cara(int x, int y)
{
	cara(lx, ly, x, y);
}

void rcara(int x, int y)
{
	cara(lx, ly, lx + x, ly + y);
}

void obdelnik(int x1, int y1, int x2, int y2)
{
	Obrazovka *obrazovka = Obrazovka::instance();

	SDL_Rect rect;
	rect.x = x1 - obrazovka->x;
	rect.y = y1 - obrazovka->y;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 + 1;
	SDL_FillRect(obrazovka->gScreenSurface, &rect, pixel);
}
