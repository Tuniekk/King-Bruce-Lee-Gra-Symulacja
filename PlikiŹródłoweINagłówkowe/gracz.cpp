/**
* \file gracz.cpp
* \brief Plik cpp modulu Gracz.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie obiektu klasy typu CGracz.
*/

#include "gracz.h"

CGracz::CGracz(sf::Keyboard::Key pKrL, sf::Keyboard::Key pKrP, sf::Keyboard::Key pKrD, sf::Keyboard::Key pKrG, sf::Keyboard::Key pAP, sf::Keyboard::Key pK, sf::Keyboard::Key pAS, string imie)
{
	this->pKrokuWLewo = pKrL;
	this->pKrokuWPrawo = pKrP;
	this->pKrokuWDol = pKrD;
	this->pKrokuWGore = pKrG;
	this->pAtakuPiescia = pAP;
	this->pKopniecia = pK;
	this->pAtakuSpecjalnego = pAS;
	this->nazwaGracza = imie;
}

CGracz::~CGracz()
{

}