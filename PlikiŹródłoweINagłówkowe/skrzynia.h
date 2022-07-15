/**
* \file skrzynia.h
* \brief Plik naglowkowy modulu Skrzynia.
*/

#ifndef SKRZYNIA_H
#define SKRZYNIA_H

#pragma once

#include "obiekt.h"

class CSkrzynia :public CPrzeszkoda {
private:
	void inicjujZmienne(int sz, int wys, int wx, int wy, int z, string i);
	void inicjujModel();
public:
	CSkrzynia(int sz = 60, int wys = 60, int x = 600, int y = 150, int z = 3, string i = "Skrzynia");
	~CSkrzynia();

	void przyjmijObrazenia(int liczbaObrazen);
	void render(sf::RenderTarget* target);
};

#endif //SKRZYNIA_H