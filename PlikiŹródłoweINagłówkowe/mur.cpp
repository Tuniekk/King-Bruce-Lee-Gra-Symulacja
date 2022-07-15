/**
* \file mur.cpp
* \brief Plik cpp modulu Mur.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie oraz wyswietlanie obiektu klasy CMur.
*/
#include "mur.h"

void CMur::inicjujZmienne(int sz, int wys, int wx, int wy, int z, string i)
{
	this->szerokosc = sz;
	this->wysokosc = wys;
	this->x = wx;
	this->y = wy;
	this->zdrowie = z;
	this->wytrzymalosc = 1;
	this->imie = i;
}

void CMur::inicjujModel()
{
	this->model.setPosition(x, y);
	this->model.setSize(sf::Vector2f(this->szerokosc, this->wysokosc));
	this->model.setFillColor(sf::Color::White);
}

CMur::CMur(int sz, int wys, int x, int y, int z, string i)
{
	this->inicjujZmienne(sz, wys, x, y, z, i);
	this->inicjujModel();
}

CMur::~CMur()
{

}

void CMur::przyjmijObrazenia(int liczbaObrazen)
{
	if (liczbaObrazen - this->wytrzymalosc <= 0)
		this->zdrowie = (this->zdrowie - 1);
	else
		this->zdrowie = (this->zdrowie - liczbaObrazen + this->wytrzymalosc);
}

void CMur::render(sf::RenderTarget* target)
{
	target->draw(this->model);
}