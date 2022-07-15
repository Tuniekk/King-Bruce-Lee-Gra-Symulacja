/**
* \file menu.h
* \brief Plik naglowkowy modulu Menu.
*/

#ifndef MENU_H
#define MENU_H

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define MAX_LICZBA_RZECZY 3 //Liczba opcji w menu glownym
#define LICZBA_POSTACI 3 //Liczba wojownikow dostepnych w programie

class CMenu {
private:
	///Numer wybranego napisu w menu glownym
	int indexWybranejRzeczy;
	///Numer wybranego napisu w menu wyboru postaci do gry
	int indexWybranejPostaciDoGry;
	///Numer wybranego napisu w menu wyboru postaci do symulacji
	int indexWybranejPostaciDoSymulacji;

	sf::VideoMode videoMode; 
	///Zmienna przechowywujaca plik z wybrana czcionka
	sf::Font czcionka;
	///Tablica napisow wyswietlanych w menu glownym
	sf::Text text[MAX_LICZBA_RZECZY]; 

	///Napis "wybierz wojownika", wyswietlany kiedy zostala wybrana gra w menu glownym
	sf::Text polecenieWyborPostaci;
	///Tablica napisow wyswietlanych w menu wyboru postaci do gry.
	sf::Text textWyborPostaciDoGry[LICZBA_POSTACI];
	///Napis "wybierz wojownikow", wyswietlany kiedy zostala wybrana symulacja w menu glownym
	sf::Text polecenieWyborPostaciSymulacja;
public:
	///Tablica napisow wyswietlanych w menu wyboru postaci do symulacji.
	sf::Text textWyborPostaciDoSymulacji[LICZBA_POSTACI];
	///Tablica przechowywujaca informacje o tym, ktore postacie zostaly wybrane do symulacji (== 1 oznacza, ze postac jest wybrana).
	bool wybranePostacieDoSymulacji[LICZBA_POSTACI];

	CMenu(float szerokosc = 1280, float wysokosc = 720);
	~CMenu();

	/** \brief Funkcja aktualizujaca menu co klatke.
	*/
	void update();
	/** \brief Funkcja odpowiadajaca za wyswietlanie menu glownego w oknie.
	* \param *okno Miejsce, w ktorym zostaje wyswietlane menu glowne.
	*/
	void render(sf::RenderTarget* okno);
	/** \brief Funkcja odpowiadajaca za wyswietlanie menu wyboru postaci do gry.
	* \param *okno Miejsce, w ktorym zostaje wyswietlane menu wyboru postaci do gry.
	*/
	void renderWyborPostaciDoGry(sf::RenderTarget* okno);
	/** \brief Funkcja odpowiadajaca za wyswietlanie menu wyboru postaci do symulacji.
	* \param *okno Miejsce, w ktorym zostaje wyswietlane menu wyboru postaci do symulacji.
	*/
	void renderWyborPostaciDoSymulacji(sf::RenderTarget* okno);
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu glownym. Jej wywolanie spowoduje ruch w gore w menu glownym.
	*/
	void ruchWGore();
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu glownym. Jej wywolanie spowoduje ruch w dol w menu glownym.
	*/
	void ruchWDol();
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu wyboru postaci do gry. Jej wywolanie spowoduje ruch w lewo w menu wyboru postaci do gry.
	*/
	void ruchWLewoPostacDoGry();
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu wyboru postaci do gry. Jej wywolanie spowoduje ruch w prawo w menu wyboru postaci do gry.
	*/
	void ruchWPrawoPostacDoGry();
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu wyboru postaci do symulacji. Jej wywolanie spowoduje ruch w lewo w menu wyboru postaci do symulacji.
	*/
	void ruchWLewoPostacDoSymulacji();
	/** \brief Funkcja odpowiadajaca za poruszanie sie po menu wyboru postaci do symulacji. Jej wywolanie spowoduje ruch w prawo w menu wyboru postaci do symulacji.
	*/
	void ruchWPrawoPostacDoSymulacji();
	/** \brief Funkcja odpowiadajaca zwracanie indeksu wybranej rzeczy w menu glownym.
	*/
	int zwrocWybranaRzecz() {return indexWybranejRzeczy;}
	/** \brief Funkcja odpowiadajaca zwracanie indeksu wybranej rzeczy w menu wyboru postaci do gry.
	*/
	int zwrocWybranaPostacDoGry() {return indexWybranejPostaciDoGry;}
	/** \brief Funkcja odpowiadajaca zwracanie indeksu wybranej rzeczy w menu wyboru postaci do symulacji.
	*/
	int zwrocWybranaPostacDoSymulacji() { return indexWybranejPostaciDoSymulacji; }
};

#endif //MENU_H