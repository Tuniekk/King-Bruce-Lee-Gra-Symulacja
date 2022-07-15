/**
* \file menu.cpp
* \brief Plik cpp modulu Menu.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie obiektu klasy typu CMenu, jego aktualizowanie, poruszanie sie po menu oraz wyswietlanie menu.
*/

#include "menu.h"

CMenu::CMenu(float szerokosc, float wysokosc)
{
	for (int i = 0; i < LICZBA_POSTACI; i++)
	{
		this->wybranePostacieDoSymulacji[i] = 0;
	}

	if (!czcionka.loadFromFile("fonts/arial.ttf"))
	{
		// W przypadku gdyby plik sie nie zaladowal
	}

	this->text[0].setFont(czcionka);
	this->text[0].setFillColor(sf::Color::Red);
	this->text[0].setString("Zagraj");
	this->text[0].setPosition(sf::Vector2f(szerokosc / 4, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->text[1].setFont(czcionka);
	this->text[1].setFillColor(sf::Color::White);
	this->text[1].setString("Symulacja");
	this->text[1].setPosition(sf::Vector2f(szerokosc / 4, wysokosc / (MAX_LICZBA_RZECZY + 1) * 2));

	this->text[2].setFont(czcionka);
	this->text[2].setFillColor(sf::Color::White);
	this->text[2].setString("Wyjdz");
	this->text[2].setPosition(sf::Vector2f(szerokosc / 4, wysokosc / (MAX_LICZBA_RZECZY + 1) * 3));

	this->indexWybranejRzeczy = 0;

	this->polecenieWyborPostaci.setFont(czcionka);
	this->polecenieWyborPostaci.setFillColor(sf::Color::White);
	this->polecenieWyborPostaci.setString("Wybierz wojownika:");
	this->polecenieWyborPostaci.setPosition(sf::Vector2f(szerokosc / 4, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoGry[0].setFont(czcionka);
	this->textWyborPostaciDoGry[0].setFillColor(sf::Color::Red);
	this->textWyborPostaciDoGry[0].setString("Bruce Lee");
	this->textWyborPostaciDoGry[0].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoGry[1].setFont(czcionka);
	this->textWyborPostaciDoGry[1].setFillColor(sf::Color::White);
	this->textWyborPostaciDoGry[1].setString("Karate Kid");
	this->textWyborPostaciDoGry[1].setPosition(sf::Vector2f(szerokosc / 1.5, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoGry[2].setFont(czcionka);
	this->textWyborPostaciDoGry[2].setFillColor(sf::Color::White);
	this->textWyborPostaciDoGry[2].setString("Jackie Chan");
	this->textWyborPostaciDoGry[2].setPosition(sf::Vector2f(szerokosc / 1.25, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->indexWybranejPostaciDoGry = 0;

	this->polecenieWyborPostaciSymulacja.setFont(czcionka);
	this->polecenieWyborPostaciSymulacja.setFillColor(sf::Color::White);
	this->polecenieWyborPostaciSymulacja.setString("Wybierz wojownikow:");
	this->polecenieWyborPostaciSymulacja.setPosition(sf::Vector2f(szerokosc / 4, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoSymulacji[0].setFont(czcionka);
	this->textWyborPostaciDoSymulacji[0].setFillColor(sf::Color::Red);
	this->textWyborPostaciDoSymulacji[0].setString("Bruce Lee");
	this->textWyborPostaciDoSymulacji[0].setPosition(sf::Vector2f(szerokosc / 2, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoSymulacji[1].setFont(czcionka);
	this->textWyborPostaciDoSymulacji[1].setFillColor(sf::Color::White);
	this->textWyborPostaciDoSymulacji[1].setString("Karate Kid");
	this->textWyborPostaciDoSymulacji[1].setPosition(sf::Vector2f(szerokosc / 1.5, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->textWyborPostaciDoSymulacji[2].setFont(czcionka);
	this->textWyborPostaciDoSymulacji[2].setFillColor(sf::Color::White);
	this->textWyborPostaciDoSymulacji[2].setString("Jackie Chan");
	this->textWyborPostaciDoSymulacji[2].setPosition(sf::Vector2f(szerokosc / 1.25, wysokosc / (MAX_LICZBA_RZECZY + 1) * 1));

	this->indexWybranejPostaciDoSymulacji = 0;
}

CMenu::~CMenu()
{

}


void CMenu::update()
{

}

void CMenu::render(sf::RenderTarget* okno)
{
	for (int i = 0; i < MAX_LICZBA_RZECZY; i++)
	{
		okno->draw(this->text[i]);
	}
}

void CMenu::renderWyborPostaciDoGry(sf::RenderTarget* okno)
{
	okno->draw(polecenieWyborPostaci);
	for (int i = 0; i < LICZBA_POSTACI; i++)
	{
		okno->draw(this->textWyborPostaciDoGry[i]);
	}
}

void CMenu::renderWyborPostaciDoSymulacji(sf::RenderTarget* okno)
{
	okno->draw(polecenieWyborPostaciSymulacja);
	for (int i = 0; i < LICZBA_POSTACI; i++)
	{
		if (this->wybranePostacieDoSymulacji[i] == 1 && indexWybranejPostaciDoSymulacji != i)
		{
			this->textWyborPostaciDoSymulacji[i].setFillColor(sf::Color::Green);
		}
		else if (this->wybranePostacieDoSymulacji[i] == 0 && indexWybranejPostaciDoSymulacji != i)
		{
			this->textWyborPostaciDoSymulacji[i].setFillColor(sf::Color::White);
		}
		okno->draw(this->textWyborPostaciDoSymulacji[i]);
	}
}

void CMenu::ruchWGore()
{
	if (indexWybranejRzeczy - 1 >= 0)
	{
		this->text[indexWybranejRzeczy].setFillColor(sf::Color::White);
		this->indexWybranejRzeczy += -1;
		this->text[indexWybranejRzeczy].setFillColor(sf::Color::Red);
	}
}

void CMenu::ruchWDol()
{
	if (indexWybranejRzeczy + 1 < MAX_LICZBA_RZECZY)
	{
		this->text[indexWybranejRzeczy].setFillColor(sf::Color::White);
		this->indexWybranejRzeczy += 1;
		this->text[indexWybranejRzeczy].setFillColor(sf::Color::Red);
	}
}

void CMenu::ruchWLewoPostacDoGry()
{
	if (indexWybranejPostaciDoGry - 1 >= 0)
	{
		this->textWyborPostaciDoGry[this->indexWybranejPostaciDoGry].setFillColor(sf::Color::White);
		this->indexWybranejPostaciDoGry += -1;
		this->textWyborPostaciDoGry[this->indexWybranejPostaciDoGry].setFillColor(sf::Color::Red);
	}
}

void CMenu::ruchWPrawoPostacDoGry()
{
	if (this->indexWybranejPostaciDoGry + 1 < LICZBA_POSTACI)
	{
		this->textWyborPostaciDoGry[this->indexWybranejPostaciDoGry].setFillColor(sf::Color::White);
		this->indexWybranejPostaciDoGry += 1;
		this->textWyborPostaciDoGry[this->indexWybranejPostaciDoGry].setFillColor(sf::Color::Red);
	}
}

void CMenu::ruchWLewoPostacDoSymulacji()
{
	if (indexWybranejPostaciDoSymulacji - 1 >= 0)
	{
		this->textWyborPostaciDoSymulacji[this->indexWybranejPostaciDoSymulacji].setFillColor(sf::Color::White);
		this->indexWybranejPostaciDoSymulacji += -1;
		this->textWyborPostaciDoSymulacji[this->indexWybranejPostaciDoSymulacji].setFillColor(sf::Color::Red);
	}
}

void CMenu::ruchWPrawoPostacDoSymulacji()
{
	if (this->indexWybranejPostaciDoSymulacji + 1 < LICZBA_POSTACI)
	{
		this->textWyborPostaciDoSymulacji[this->indexWybranejPostaciDoSymulacji].setFillColor(sf::Color::White);
		this->indexWybranejPostaciDoSymulacji += 1;
		this->textWyborPostaciDoSymulacji[this->indexWybranejPostaciDoSymulacji].setFillColor(sf::Color::Red);
	}
}
