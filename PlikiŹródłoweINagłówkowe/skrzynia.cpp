/**
* \file skrzynia.cpp
* \brief Plik cpp modulu Skrzynia.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie oraz wyswietlanie obiektu klasy CSkrzynia.
*/
#include "skrzynia.h"

void CSkrzynia::inicjujZmienne(int sz, int wys, int wx, int wy, int z, string i)
{
	this->szerokosc = sz;
	this->wysokosc = wys;
	this->x = wx;
	this->y = wy;
	this->zdrowie = z;
	this->wytrzymalosc = 1;
	this->imie = i;
}

void CSkrzynia::inicjujModel()
{
	this->model.setPosition(x, y);
	this->model.setSize(sf::Vector2f(this->szerokosc, this->wysokosc));
	this->model.setFillColor(sf::Color(70, 40, 11));
}

CSkrzynia::CSkrzynia(int sz, int wys, int x, int y, int z, string i)
{
	this->inicjujZmienne(sz, wys, x, y, z, i);
	this->inicjujModel();
}

CSkrzynia::~CSkrzynia()
{

}

void CSkrzynia::przyjmijObrazenia(int liczbaObrazen)
{
	if (liczbaObrazen - this->wytrzymalosc <= 0)
		this->zdrowie = (this->zdrowie - 1);
	else
		this->zdrowie = (this->zdrowie - liczbaObrazen + this->wytrzymalosc);
}

void CSkrzynia::render(sf::RenderTarget* target)
{
	target->draw(this->model);
}