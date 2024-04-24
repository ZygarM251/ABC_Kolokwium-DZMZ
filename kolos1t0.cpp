#include <iostream>
#include <fstream>

struct Struktura {
    int i;
    double d;
};

Struktura* stworzTablice(int rozmiar, const Struktura& prototyp) {
    Struktura* tablica = new Struktura[rozmiar];
    for (int i = 0; i < rozmiar; ++i) {
        tablica[i] = prototyp;
    }
    return tablica;
}

void zapiszTabliceDoPliku(const char* nazwaPliku, int rozmiar, const Struktura& prototyp) {
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu" << std::endl;
        return;
    }

    plik << rozmiar << "\n";
    for (int i = 0; i < rozmiar; ++i) {
        plik << prototyp.i << " " << prototyp.d << "\n";
    }

    plik.close();
}

Struktura* odczytajZPliku(const char* nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku do odczytu" << std::endl;
        return nullptr;
    }

    int rozmiar;
    plik >> rozmiar;
    Struktura* tablica = new Struktura[rozmiar];
    for (int i = 0; i < rozmiar; ++i) {
        plik >> tablica[i].i >> tablica[i].d;
    }

    plik.close();
    return tablica;
}

int main() {
    const char* nazwaPliku = "tablica.txt";
    Struktura prototyp = { 1, 3.14 };
    //duze Z w ASCII to 90
    Struktura* tworzonaTablica = stworzTablice(90, prototyp);

    zapiszTabliceDoPliku(nazwaPliku, 90, prototyp);

    Struktura* odczytanaTablica = odczytajZPliku(nazwaPliku);

    bool czySaIdentyczne = true;
    for (int i = 0; i < 90; ++i) {
        if (tworzonaTablica[i].i != odczytanaTablica[i].i || tworzonaTablica[i].d != odczytanaTablica[i].d) {
            czySaIdentyczne = false;
            break;
        }
    }


    std::cout << "Czy sa identyczne?:\t";
    if (czySaIdentyczne) {
        std::cout << "Tak\n";
    }
    else {
        std::cout << "Nie\n";
    }

    delete[] tworzonaTablica;
    delete[] odczytanaTablica;

    return 0;
}
