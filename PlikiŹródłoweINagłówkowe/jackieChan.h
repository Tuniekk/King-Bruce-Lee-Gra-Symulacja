/**
* \file jackiechan.h
* \brief Plik naglowkowy modulu JackieChan.
*/

#ifndef JACKIECHAN_H
#define JACKIECHAN_H

#pragma once

#include "obiekt.h"
#include "skrzynia.h"

#include <iostream>
#include <string.h>

/*
* \brief Wojownik Jackie Chan:
*Atak piescia oraz kopniecie standardowe.
*Atak specjalny - Jackie Chan atakuje piescia o duzo wiekszym rozmiarze.
*
*Wojownik ten jest w stanie przechodzic przez skrzynie. Inne przeszkody oraz wojownicy blokuja postac.
*/
class CJackieChan :public CWojownik {
private:
	///Dlugosc jednego cyklu poruszania sie
	int czasTrwaniaCyklu;
	///Ilosc czasu jaka minela od skoñczenia ostatniego cyklu (lub ilosc czasu, jaka trwa obecny cykl poruszania sie) 
	int czasObecnyCyklu;

	/// Wektor przechowywujacy ataki specjalne wyrzucone przez wojownika
	std::vector<sf::RectangleShape> atakiSpecjalne; // Wektor przechowywujacy ataki specjalne wyrzucone przez wojownika

	/// Wektor kierunkow w osi X, w jaka sa odwrocone ataki specjalne
	vector<float> xKierunkiAtakowSpecjalnych;
	/// Wektor kierunkow w osi Y, w jaka sa odwrocone ataki specjalne
	vector<float> yKierunkiAtakowSpecjalnych;

	void inicjujZmienne(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s);
	void inicjujModel();

public:
	///Zmienna przechowywujaca informacje o tym, czy postac jest sterowana przez gracza
	bool trybSterowania;
	//Konstruktor i destruktor
	CJackieChan(int wx = 600, int wy = 650, string i = "Jackie Chan", int z = 70, int sz = 7, int szer = 85, int wys = 85, int w = 3, int s = 10);
	~CJackieChan();

	void atakPiescia(bool wykonajAtak);
	void ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void kopniecie(bool wykonajAtak);
	void ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void atakSpecjalny(bool wykonajAtak);
	void ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void chodzenie(char stronaRuchu);

	float obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt);
	void liczCzas();
	void wykryjKolizjeZOknem(const sf::RenderTarget* okno);
	void wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty);
	void update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty);
	void przyjmijObrazenia(int liczbaObrazen);

	void renderAtakPiescia(sf::RenderTarget* okno);
	void renderKopniecie(sf::RenderTarget* okno);
	/** \brief Wyswietlanie ataku specjalnego wojownika.
	* \param *okno miejsce, gdzie sa wyswietlane pociski.
	*/
	void renderAtakSpecjalny(sf::RenderTarget* okno);
	void render(sf::RenderTarget* target);
};

#endif //JACKIECHAN_H