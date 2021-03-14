#ifndef OBRAZEK_H
#define OBRAZEK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>

#define BILA 255, 255, 255
#define CERVENA 255, 0, 0
#define ZELENA 0, 255, 0
#define MODRA 0, 0, 255
#define AZUROVA 0, 255, 255
#define PURPUROVA 255, 0, 255
#define CERNA 0, 0, 0
#define ZLUTA 255, 255, 0


class Obrazovka
{
	public:
		SDL_Window* gWindow = NULL;
		SDL_Surface* gScreenSurface = NULL;
		//SDL_Window* gWindow = NULL;
		// Obrazek* obrazek;
		unsigned int w, h;
		float x, y;
		
		static Obrazovka* instance();
		void inicializuj( const char *name, const unsigned int sirka, const unsigned int vyska, const unsigned int vlajky);
		void umisti(float x, float y);
		void pohni(float x, float y);
		void aktualizuj();
		void smaz();
        void zavri();
		void zamkni();
		void getWindow(SDL_Window*& cWindow);
		void odemkni();
		Uint32 getpixel(int x, int y);
		void putpixel(int x, int y, Uint32 pixel);
	protected:
		Obrazovka();
};

class Obrazek
{
public:
	// Vnitrni promenne objektu
	SDL_Surface *gSurface;
	//SDL_Window* win;
	Obrazovka* obrazovka;
	
	SDL_Surface* gHelloWorld = NULL;
	float x, y, vx, vy, ax, ay, ox, oy;
	int w, h;
	
	// Konstruktor
	Obrazek();

	// Destruktor
	~Obrazek();

	// Nacteni obrazku z disku do pameti
	void nacti(const char *filename);
	void nacti_animaci(char *filename, int w, int h);

	// Nacteni obrazku z disku do pameti std stringu
	//void nacti(std::string filename);

	// Nedovol objektu opustit obrazovku
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );
	
	void meze();
	
	void pocatek(float px, float py);

	// Presun objektu na zadane souradnice
	void umisti(float px, float py);

	// Pohyb objektu o zadanou vzdalenost
	void pohni(float px, float py);

	// Nastav rychlost automatickeho pohybu
	void rychlost(float x, float y);

	void zrychleni(float x, float y);

	// Aktualizuj automaticke pohyby
	void aktualizuj();

	// Vykresleni objektu na obrazovku
	void kresli();

	// Zjistime kolizi
	int kolize(Obrazek *o);
	Uint32 getpixel(int x,int y);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
};
extern Uint32 pixel;



void barva(unsigned char r, unsigned char g, unsigned char b);
void bod(int x, int y);
void cara(int x1, int y1, int x2, int y2);
void cara(int x, int y);
void rcara(int x, int y);
void obdelnik(int x1, int y1, int x2, int y2);


#endif // MAIN_H