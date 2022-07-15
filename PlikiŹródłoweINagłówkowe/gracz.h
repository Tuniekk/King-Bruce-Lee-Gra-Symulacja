/**
* \file gracz.h
* \brief Plik naglowkowy modulu Gracz.
*/

#ifndef GRACZ_H
#define GRACZ_H

#pragma once

#include <iostream>
#include <string.h>

#include "obiekt.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class CGracz 
{
public:
	///Imie gracza
	string nazwaGracza;
	///Wskaznik sluzacy do wskazywania wojownika wybranego przez gracza
	CWojownik* postacGracza;

	///Przycisk sluzacy do chodzenia w lewo
	sf::Keyboard::Key pKrokuWLewo;
	///Przycisk sluzacy do chodzenia w prawo
	sf::Keyboard::Key pKrokuWPrawo;
	///Przycisk sluzacy do chodzenia w dol
	sf::Keyboard::Key pKrokuWDol; 
	///Przycisk sluzacy do chodzenia w gore
	sf::Keyboard::Key pKrokuWGore; 
	///Przycisk sluzacy do wywolania ataku piescia wojownika
	sf::Keyboard::Key pAtakuPiescia;
	///Przycisk sluzacy do wywolania kopniecia wojownika
	sf::Keyboard::Key pKopniecia;
	///Przycisk sluzacy do wywolania ataku specjalnego wojownika
	sf::Keyboard::Key pAtakuSpecjalnego;

	CGracz(sf::Keyboard::Key pKrL = sf::Keyboard::A, sf::Keyboard::Key pKrP = sf::Keyboard::D, sf::Keyboard::Key pKrD = sf::Keyboard::S, sf::Keyboard::Key pKrG = sf::Keyboard::W,
		sf::Keyboard::Key pAP = sf::Keyboard::R, sf::Keyboard::Key pK = sf::Keyboard::T, sf::Keyboard::Key pAS = sf::Keyboard::Y, string imie = "Gracz1");
	~CGracz();
};

#endif //GRACZ_H