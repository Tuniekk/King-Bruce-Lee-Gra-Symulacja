/**
* \file kingBruceLee.cpp
* \brief Plik cpp modulu kingBruceLee.
*
* Tutaj znajduje sie kod zrodlowy funkcji main.
*/
#include "menu.h" //Zawiera definicje klasy CMenu
#include "gra.h" //Zawiera definicje klasy CGra

int main()
{
    sf::RenderWindow oknoMenu(sf::VideoMode(1280, 720), "Menu glowne", sf::Style::Default);
    CMenu menuGlowne(oknoMenu.getSize().x, oknoMenu.getSize().y);

    while (oknoMenu.isOpen())
    {
        sf::Event event;
        while (oknoMenu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                oknoMenu.close();
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    menuGlowne.ruchWGore();
                    break;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    menuGlowne.ruchWDol();
                    break;
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    int index = menuGlowne.zwrocWybranaRzecz();
                    if (index == 0)
                    {
                        bool wybranoGre = 1;
                        while (wybranoGre == 1)
                        {
                            sf::Event wyborPostaci;
                            while (oknoMenu.pollEvent(wyborPostaci))
                            {
                                if (wyborPostaci.type == sf::Event::Closed)
                                {
                                    oknoMenu.close();
                                    wybranoGre = 0;
                                }
                                if (wyborPostaci.type == sf::Event::KeyReleased)
                                {
                                    if (wyborPostaci.key.code == sf::Keyboard::Left)
                                    {
                                        menuGlowne.ruchWLewoPostacDoGry();
                                        break;
                                    }
                                    if (wyborPostaci.key.code == sf::Keyboard::Right)
                                    {
                                        menuGlowne.ruchWPrawoPostacDoGry();
                                        break;
                                    }
                                    if (wyborPostaci.key.code == sf::Keyboard::Enter)
                                    {
                                        CGra gra;
                                        gra.dodajObiekty();

                                        int indexWybranejPostaci = menuGlowne.zwrocWybranaPostacDoGry();
                                        if (indexWybranejPostaci == 0)
                                        {
                                            gra.gracz1.postacGracza = &gra.bruceLee;
                                            gra.bruceLee.trybSterowania = 1;
                                        }

                                        if (indexWybranejPostaci == 1)
                                        {
                                            gra.gracz1.postacGracza = &gra.karateKid;
                                            gra.karateKid.trybSterowania = 1;
                                        }

                                        if (indexWybranejPostaci == 2)
                                        {
                                            gra.gracz1.postacGracza = &gra.jackieChan;
                                            gra.jackieChan.trybSterowania = 1;
                                        }

                                        gra.dodajWojownika(&gra.bruceLee);
                                        gra.dodajWojownika(&gra.karateKid);
                                        gra.dodajWojownika(&gra.jackieChan);

                                        //Petla gry
                                        while (gra.oknoOtwarte())
                                        {
                                            gra.sterowanie(gra.gracz1);
                                            gra.update();
                                            gra.render();
                                        }
                                    }
                                    if (wyborPostaci.key.code == sf::Keyboard::Escape)
                                    {
                                        wybranoGre = 0;
                                        break;
                                    }
                                }
                            }
                            oknoMenu.clear();
                            menuGlowne.renderWyborPostaciDoGry(&oknoMenu);
                            oknoMenu.display();
                        }
                    }
                    if (index == 1)
                    {
                        bool wybranoSymulacje = 1;
                        int liczbaWybranychPostaci = 0;

                        while (wybranoSymulacje == 1)
                        {
                            sf::Event wyborPostaciSymulacja;
                            while (oknoMenu.pollEvent(wyborPostaciSymulacja))
                            {
                                if (wyborPostaciSymulacja.type == sf::Event::Closed)
                                {
                                    oknoMenu.close();
                                    wybranoSymulacje = 0;
                                }
                                if (wyborPostaciSymulacja.type == sf::Event::KeyReleased)
                                {
                                    if (wyborPostaciSymulacja.key.code == sf::Keyboard::Left)
                                    {
                                        menuGlowne.ruchWLewoPostacDoSymulacji();
                                        break;
                                    }
                                    if (wyborPostaciSymulacja.key.code == sf::Keyboard::Right)
                                    {
                                        menuGlowne.ruchWPrawoPostacDoSymulacji();
                                        break;
                                    }
                                    if (wyborPostaciSymulacja.key.code == sf::Keyboard::Enter)
                                    {
                                        int indexWybranejPostaci = menuGlowne.zwrocWybranaPostacDoSymulacji();
                                        if (indexWybranejPostaci == 0)
                                        {
                                            if (menuGlowne.wybranePostacieDoSymulacji[0] == 0)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[0] = 1;
                                                liczbaWybranychPostaci++;
                                                menuGlowne.textWyborPostaciDoSymulacji[0].setFillColor(sf::Color::Green);
                                            }
                                            else if (menuGlowne.wybranePostacieDoSymulacji[0] == 1)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[0] = 0;
                                                liczbaWybranychPostaci--;
                                                menuGlowne.textWyborPostaciDoSymulacji[0].setFillColor(sf::Color::White);
                                            }

                                        }
                                        if (indexWybranejPostaci == 1)
                                        {
                                            if (menuGlowne.wybranePostacieDoSymulacji[1] == 0)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[1] = 1;
                                                liczbaWybranychPostaci++;
                                                menuGlowne.textWyborPostaciDoSymulacji[1].setFillColor(sf::Color::Green);
                                            }
                                            else if (menuGlowne.wybranePostacieDoSymulacji[1] == 1)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[1] = 0;
                                                liczbaWybranychPostaci--;
                                                menuGlowne.textWyborPostaciDoSymulacji[1].setFillColor(sf::Color::White);
                                            }
                                        }
                                        if (indexWybranejPostaci == 2)
                                        {
                                            if (menuGlowne.wybranePostacieDoSymulacji[2] == 0)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[2] = 1;
                                                liczbaWybranychPostaci++;
                                                menuGlowne.textWyborPostaciDoSymulacji[2].setFillColor(sf::Color::Green);
                                            }
                                            else if (menuGlowne.wybranePostacieDoSymulacji[2] == 1)
                                            {
                                                menuGlowne.wybranePostacieDoSymulacji[2] = 0;
                                                liczbaWybranychPostaci--;
                                                menuGlowne.textWyborPostaciDoSymulacji[2].setFillColor(sf::Color::White);
                                            }
                                        }
                                    }
                                    if (wyborPostaciSymulacja.key.code == sf::Keyboard::Space && liczbaWybranychPostaci >= 2)
                                    {
                                        CGra gra;
                                        gra.dodajObiekty();

                                        if (menuGlowne.wybranePostacieDoSymulacji[0] == 1)
                                            gra.dodajWojownika(&gra.bruceLee);
                                        if (menuGlowne.wybranePostacieDoSymulacji[1] == 1)
                                            gra.dodajWojownika(&gra.karateKid);
                                        if (menuGlowne.wybranePostacieDoSymulacji[2] == 1)
                                            gra.dodajWojownika(&gra.jackieChan);

                                        while (gra.oknoOtwarte())
                                        {
                                            gra.update();
                                            gra.render();
                                        }
                                    }
                                    if (wyborPostaciSymulacja.key.code == sf::Keyboard::Escape)
                                    {
                                        wybranoSymulacje = 0;
                                        for (int i = 0; i < LICZBA_POSTACI; i++)
                                        {
                                            menuGlowne.wybranePostacieDoSymulacji[i] = 0;
                                        }
                                        break;
                                    }
                                }
                            }
                            oknoMenu.clear();
                            menuGlowne.renderWyborPostaciDoSymulacji(&oknoMenu);
                            oknoMenu.display();
                        }
                    }
                    if (index == 2)
                    {
                        oknoMenu.close();
                    }
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    menuGlowne.ruchWLewoPostacDoGry();
                    break;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    menuGlowne.ruchWPrawoPostacDoGry();
                    break;
                }
            }

        }
        oknoMenu.clear();
        menuGlowne.render(&oknoMenu);
        oknoMenu.display();
    }
    return 0;
}