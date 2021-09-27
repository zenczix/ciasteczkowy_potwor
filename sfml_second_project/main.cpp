#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#define ROZMIAR_OKNA_X  1000.f
#define ROZMIAR_OKNA_Y  1000.f


class AvengerSprite : public sf::Sprite
{
public:
    enum TYP {Potwor, Ciastko, Kamien, Sesam};

    sf::Vector2f szybkosc;
    TYP typ;

    AvengerSprite(sf::Texture* tekstura) :sf::Sprite()
    {
        setTexture(*tekstura);
        scale(0.2f, 0.2f);
        setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
    }

    virtual ~AvengerSprite()
    {
    }

    bool Kolizja(AvengerSprite* postac)
    {
        return getGlobalBounds().intersects(postac->getGlobalBounds());
    }

    void Pokaz(sf::RenderWindow& okno)
    {

        okno.draw(*this);

    }

    void Animuj(const sf::Time& elapsed)
    {

        move(szybkosc * elapsed.asSeconds());

        sf::FloatRect pr = getGlobalBounds();
        sf::Vector2f p = getPosition();


        if (p.y + pr.height * 0.5f < 0.0f)
        {
            setPosition(p.x, 5000.0f + pr.height * 0.5f);
        }

        else if (p.y - pr.height * 0.5f > 5000.0f)
        {
            setPosition(p.x, -pr.height * 0.5f);
        }

    }
};

class Potwor : public AvengerSprite
{
private:


public:
    Potwor(sf::Texture* tekstura) : AvengerSprite(tekstura)
    {

        typ = AvengerSprite::TYP::Potwor;
    }

    virtual ~Potwor()
    {
    }


};

class Ciastko : public AvengerSprite
{
public:
    Ciastko(sf::Texture* tekstura) : AvengerSprite(tekstura)
    {
        szybkosc = sf::Vector2f(0.0f, 50.f);
        typ = AvengerSprite::TYP::Ciastko;
    }

    virtual ~Ciastko()
    {
    }

};

class Kamien : public AvengerSprite
{
public:
    Kamien(sf::Texture* tekstura) : AvengerSprite(tekstura)
    {
        typ = AvengerSprite::TYP::Kamien;

            szybkosc = sf::Vector2f(0.0f, 50.0f);

    }

    virtual ~Kamien()
    {
    }
};
class Sesam : public AvengerSprite
{
public:
    Sesam(sf::Texture* tekstura) : AvengerSprite(tekstura)
    {
        szybkosc = sf::Vector2f(0.0f, 0.1f);
        typ = AvengerSprite::TYP::Sesam;
    }

    virtual ~Sesam()
    {
    }

};
void umiesc_w_losowym_miejscu(AvengerSprite* postac, sf::Vector2f minmax)
{
    float losowe_x = rand() % (int)(minmax.x);
    float losowe_y = rand() % (int)(minmax.y);
    postac->setPosition(losowe_x, losowe_y);
}


int main()
{
    sf::RenderWindow okno(sf::VideoMode(ROZMIAR_OKNA_X, ROZMIAR_OKNA_Y), "ulica sezamkowa");
std::map<std::string, sf::Texture*> tekstury;

sf::SoundBuffer buffer;
if(!buffer.loadFromFile("muzyka.wav"))
{
    std::cout<<"ERROR" << std::endl;
}

sf::Sound sound;

sound.setBuffer(buffer);


sf::SoundBuffer buffer2;
if(!buffer2.loadFromFile("No.wav"))
{
    std::cout<<"ERROR" << std::endl;
}

sf::Sound sound2;

sound2.setBuffer(buffer2);

sf::Font font;


if(!font.loadFromFile("arial.ttf"))
{
   std::cout << "can't load font" << std::endl;
}


int score = 0;

sf::Font arial;

arial.loadFromFile("arial.ttf");

std::ostringstream ssScore;

ssScore << "Score: " << score;

sf::Text lblScore;

lblScore.setCharacterSize(40);

lblScore.setPosition({ 800, 10 });

lblScore.setFont(arial);

lblScore.setString(ssScore.str());

lblScore.setFillColor(sf::Color::Red);

int zycia = 5;

std::ostringstream sszycia;

sszycia << "zycia: " << zycia;

sf::Text lblzycia;

lblzycia.setCharacterSize(40);

lblzycia.setPosition({ 800, 40 });

lblzycia.setFont(arial);

lblzycia.setString(sszycia.str());

lblzycia.setFillColor(sf::Color::Red);

    tekstury.insert(std::make_pair("ciastko", new sf::Texture()));

       tekstury.insert(std::make_pair("potwor", new sf::Texture()));

       tekstury.insert(std::make_pair("kamien", new sf::Texture()));

        tekstury.insert(std::make_pair("sesam", new sf::Texture()));

       tekstury["ciastko"]->loadFromFile("tekstury/ciastko.png");

       tekstury["potwor"]->loadFromFile("tekstury/potwor.png");

       tekstury["kamien"]->loadFromFile("tekstury/kamien.png");

       tekstury["sesam"]->loadFromFile("tekstury/sesam.png");

    std::vector<AvengerSprite*> postacie;

    Potwor* potwor = new Potwor(tekstury["potwor"]);
    postacie.emplace_back(potwor);

    Sesam* sesam = new Sesam(tekstury["sesam"]);
    postacie.emplace_back(sesam);


    for (int i = 0; i < 60; i++)
    {
        Kamien* kamien = new Kamien(tekstury["kamien"]);
        umiesc_w_losowym_miejscu(kamien, sf::Vector2f(1000.0f, 5000.0f));
        postacie.emplace_back(kamien);
    }


    for (int i = 0; i < 40; i++)
    {
        Ciastko* ciastko = new Ciastko(tekstury["ciastko"]);
        umiesc_w_losowym_miejscu(ciastko, sf::Vector2f(1000.0f, 5000.0f));
        postacie.emplace_back(ciastko);
    }

     sf::Vector2f srodek_okna = sf::Vector2f(1000.0f, 1700.0f) * 0.5f;
    postacie[0]->setPosition(srodek_okna);


     sf::Clock zegar;
    sf::Time czas_teraz;


    while (okno.isOpen())
    {

        sf::Event event;
        while (okno.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                okno.close();
        }

        czas_teraz = zegar.restart();



okno.clear(sf::Color::Cyan);

okno.draw(lblScore);

okno.draw(lblzycia);
        for (auto& postac : postacie)
        {

            postac->Animuj(czas_teraz);
            postac->Pokaz(okno);
        }

        okno.display();

       Potwor* potwor = static_cast<Potwor*>(postacie[0]);

        auto postac = postacie.begin() + 1;

        while (postac != postacie.end())
        {
            if (potwor->Kolizja(*postac))
            {
                if ((*postac)->typ == AvengerSprite::TYP::Ciastko)
                {
                    sound.play();

                    score+=5;
                    ssScore.str("");
                    ssScore << "Score " << score;
                    lblScore.setString(ssScore.str());
                }
                else if ((*postac)->typ == AvengerSprite::TYP::Kamien)
                {
                    sound2.play();
                   zycia--;
                    sszycia.str("");
                    sszycia << "Zycia " << zycia;
                    lblzycia.setString(sszycia.str());
                }

                delete (*postac);
                postac = postacie.erase(postac);


            }

            else
            {
                ++postac;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            postacie[0]->szybkosc = sf::Vector2f(-200.0f, 0.0f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            postacie[0]->szybkosc = sf::Vector2f(200.0f, 0.0f);
        }
        if (zycia == 0)
        {
            std::cout << "PRZEGRANA PO STRACIE 5 ZYC"<<std::endl;
            okno.close();
        }

        if (score == 50)
        {
            std::cout << "WYGRANA PO ZDOBYCIU 50 PKT"<<std::endl;
            okno.close();
        }
    }



    return 0;
}
