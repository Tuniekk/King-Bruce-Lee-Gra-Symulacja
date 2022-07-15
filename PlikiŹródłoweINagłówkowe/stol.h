/**
* \file stol.h
* \brief Plik naglowkowy modulu Stol.
*/

#ifndef STOL_H
#define STOL_H

#pragma once

#include "obiekt.h"

#include <iostream>
#include <string.h>


class CStol :public CPrzeszkoda {
private:
	void inicjujZmienne(int sz, int wys, int wx, int wy, int z, string i);
	void inicjujModel();
public:
	CStol(int sz = 50, int wys = 50, int x = 50, int y = 50, int z = 3, string i = "Stol");
	~CStol();

	void przyjmijObrazenia(int liczbaObrazen);
	void render(sf::RenderTarget* target);
};

#endif //STOL_H