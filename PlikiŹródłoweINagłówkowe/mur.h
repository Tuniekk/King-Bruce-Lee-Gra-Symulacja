/**
* \file mur.h
* \brief Plik naglowkowy modulu Mur.
*/

#ifndef MUR_H
#define MUR_H

#pragma once

#include "obiekt.h"

class CMur :public CPrzeszkoda {
private:
	void inicjujZmienne(int sz, int wys, int wx, int wy, int z, string i);
	void inicjujModel();
public:
	CMur(int sz = 30, int wys = 300, int x = 600, int y = 150, int z = 3, string i = "Mur");
	~CMur();

	void przyjmijObrazenia(int liczbaObrazen);
	void render(sf::RenderTarget* target);
};

#endif //MUR_H