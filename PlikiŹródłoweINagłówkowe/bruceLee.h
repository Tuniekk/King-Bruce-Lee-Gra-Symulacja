/**
* \file bruceLee.h
* \brief Plik naglowkowy modulu BruceLee.
*/

#ifndef BRUCELEE_H
#define BRUCELEE_H

#pragma once

#include "obiekt.h"
#include "stol.h"

#include <iostream>
#include <string.h>

/*
Wojownik Bruce Lee:
-Atak piescia oraz kopniecie standardowe.
-Atak specjalny - rzut szurikenem. Po wcisnieciu przycisku ataku specjalnego podczas ruchu wojownik wyrzuca szuriken (w ksztalcie kola) w kierunku ruchu. 
Szuriken ten przy trafieniu w obiekt znika oraz zadaje obrazenia. Po wyrzuceniu szurikenu nalezy odczekac pewien czas, zanim mozna wyrzucic kolejny szuriken.
Obecnie nie ma limitu szurikenow, ktore moga byc naraz na ekranie.

-Wojownik ten jest w stanie przechodzic przez stoly. Inne przeszkody oraz wojownicy blokuja postac.
*/
class CBruceLee :public CWojownik
{
private:
	///Dlugosc jednego cyklu poruszania sie
	int czasTrwaniaCyklu; 
	///Ilosc czasu jaka minela od skoñczenia ostatniego cyklu (lub ilosc czasu, jaka trwa obecny cykl poruszania sie) 
	int czasObecnyCyklu; 

	/// Wektor atakow specjalnych wojownika (rzucanych pociskow
	std::vector<sf::CircleShape> szurikeny;

	/// Wektor kierunkow w osi X, w jaka sa odwrocone szurikeny
	vector<float> xKierunkiAtakowSpecjalnych;
	/// Wektor kierunkow w osi Y, w jaka sa odwrocone szurikeny
	vector<float> yKierunkiAtakowSpecjalnych;

	void inicjujZmienne(int x, int y, string i, int z, int sz, int szer, int wys, int w, int s);
	void inicjujModel();

public:
	///Zmienna przechowywujaca informacje o tym, czy postac jest sterowana przez gracza
	bool trybSterowania;
	//Konstruktor i destruktor
	CBruceLee(int wx = 200, int wy = 200, string i = "Bruce Lee", int z = 60, int sz = 6, int szer = 100, int wys = 100, int w = 4, int s = 10);
	~CBruceLee();

	void atakPiescia(bool wykonajAtak);
	void ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void kopniecie(bool wykonajAtak);
	void ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void atakSpecjalny(bool wykonajAtak);
	void ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void chodzenie(char stronaRuchu);

	float obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt);
	void liczCzas();
	void wykryjKolizjeZOknem(const sf::RenderTarget* okno); //Funkcja rejestrujaca zderzenia postaci z krawedziami okna
	void wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty);
	void update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty);
	void przyjmijObrazenia(int liczbaObrazen);

	void renderAtakPiescia(sf::RenderTarget* okno);
	void renderKopniecie(sf::RenderTarget* okno);
	/** \brief Wyswietlanie pociskow wystrzelonych przez wojownika.
	* \param *okno miejsce, gdzie sa wyswietlane pociski.
	*/
	void renderSzurikeny(sf::RenderTarget* okno);
	void render(sf::RenderTarget* target);
};

#endif //BRUCELEE_H