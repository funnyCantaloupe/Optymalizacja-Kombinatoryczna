#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> wynik_DNA;
vector<int> wymieszane_wierzcholki;
vector<pair<int,int>> ulozone_wierzcholki;
vector<int> nie_pasuje_bo_uzyty;
vector<int> zuzyte_wierzcholki_id;

int main() {
    //PARAMETRY
    char zasady_azotowe[4] = {'A', 'T', 'C', 'G'};
    int dlugosc_DNA = 100;
    int dlugosc_okienka = 6;
    float procent_pozytywnych = 0;
    float procent_negatywnych = 0;

    //GENEROWANIE LANCUCHA DNA
    vector<char> lancuch_DNA;
    int rand_index;
    srand(time(NULL));
    cout << "Wygenerowany lancuch: " << endl;
    for (int i = 0; i < dlugosc_DNA; i++) {
        rand_index = rand() % +4;
        lancuch_DNA.push_back(zasady_azotowe[rand_index]);
        cout << lancuch_DNA[i] << " ";
    }

    //GENEROWANIE OKIENEK
    vector<vector<char>> okienka;
    vector<char> okienka_temp;
    vector<vector<char>> okienka_kopia;
    int liczba_okienek = dlugosc_DNA - (dlugosc_okienka - 1);
    int index = 0;
    for (int i = 0; i < liczba_okienek; i++) //tyle jest okienek
    {
        index = i;
        for (int j = 0; j < dlugosc_okienka; j++) //taka maja dlugosc okienka
        {
            okienka_temp.push_back(lancuch_DNA[index]);
            index++;
        }
        okienka.push_back(okienka_temp);
        okienka_temp.clear();
    }

    //Wyswietlanie okienek
    cout << endl;
    for (int i = 0; i < liczba_okienek; i++) {
        cout << "Okienko nr: " << i << " | ";
        for (auto it = okienka[i].begin(); it != okienka[i].end(); it++) {
            cout << *it;
        }

        cout << endl;
    }

    //GENEROWANIE BLEDOW NEGATYWNYCH - USUWANIE NUKLEOTYDOW
    float liczba_bledow_negatywnych = round(liczba_okienek * (procent_negatywnych / 100));
    for (int i = 0; i < liczba_bledow_negatywnych; i++) {
        rand_index = rand() % +(liczba_okienek - 1);
        okienka.erase(okienka.begin() + rand_index);
        liczba_okienek--;
    }
    dlugosc_DNA = dlugosc_DNA - liczba_bledow_negatywnych;


    //GENEROWANIE BLEDOW POZYTYWNYCH - DODAWANIE NUKLEOTYDOW
    int rand2_index;
    float liczba_bledow_pozytywnych = round(liczba_okienek * (procent_pozytywnych / 100));
    for (int i = 0; i < liczba_bledow_pozytywnych; i++) {
        for (int j = 0; j < dlugosc_okienka; j++) //generowanie losowego okienka
        {
            rand_index = rand() % +4;
            rand2_index = rand() % + (liczba_okienek - 1);
            okienka_temp.push_back(zasady_azotowe[rand_index]);
        }
        okienka.insert(okienka.begin() + rand2_index, okienka_temp);
        liczba_okienek++;
        okienka_temp.clear();
    }
    dlugosc_DNA = dlugosc_DNA + liczba_bledow_pozytywnych;


    // dodanie kopii wektora okienka
    okienka_kopia = okienka;

    //Startowy wierzcholek (dla rozwiazanie z wagami korzystamy z tego samego kawalka kodu)
    for (auto it = okienka[0].begin(); it != okienka[0].end(); it++) {
        wynik_DNA.push_back(*it);
    }
    okienka = okienka_kopia;
    zuzyte_wierzcholki_id.push_back(0);


    //Kolejne wierzcholki
    int pomoc = 0; // mozna pomyslec nad lepsza nazwa
    int pomoc2 = liczba_okienek; // mozna pomyslec nad lepsza nazwa


    // rozwiazanie z wagami
    // oznaczenie wag kolejnych wierzcholkow dla rozwazanego w danym momencie wierzcholka

    int id_obecnego_wierzcholka = 0; // zeby moc porownac do tego wierzcholka w ponizeszej petli (j)

    vector<int> waga_wierzcholkow;
    vector<int> uzyte_losowe;

    pomoc2 = liczba_okienek;

    int licznik_ite;
    int id_wierzcholka = 0;
    int licznik_zasad = 0;

    random_shuffle(okienka.begin(), okienka.end());

    while (wynik_DNA.size() != dlugosc_DNA) {

        cout << endl;
        okienka_temp = okienka[id_obecnego_wierzcholka];
        cout << "AKTUALNY WIERZCHOLEK (WAGI LICZYMY DLA NIEGO): ";
        for (auto& n : okienka_temp) {
            cout << n;
        }
        cout << endl;

        for (int i = 0; i < liczba_okienek; i++) {
                for (int j = 0; j < dlugosc_okienka; j++) {
                    if (equal(okienka[id_obecnego_wierzcholka].begin() + j,
                              okienka[id_obecnego_wierzcholka].end(), okienka[i].begin(), okienka[i].end() - j) && count(zuzyte_wierzcholki_id.begin(), zuzyte_wierzcholki_id.end(), i) == 0) {
                        waga_wierzcholkow.push_back(j);
                        break;
                    }
                    else if (j == dlugosc_okienka - 1 || count(zuzyte_wierzcholki_id.begin(), zuzyte_wierzcholki_id.end(), i) != 0) {
                        waga_wierzcholkow.push_back(0);
                        break;
                    }
                }


            // wypisywanie wierzchokow, wag oraz ich id

            licznik_ite = 0;
            okienka_temp = okienka[i];

                for (auto ite = okienka_temp.begin(); ite != okienka_temp.end(); ite++) {
                    if (count(zuzyte_wierzcholki_id.begin(), zuzyte_wierzcholki_id.end(), i) == 0) {
                        if (licznik_ite != dlugosc_okienka - 1) {
                            ite--;
                            licznik_ite++;
                        } else {
                            cout << "wierzcholek: ";
                            for (int j = 0; j < dlugosc_okienka; j++) {
                                cout << *(ite + j);
                            }
                            cout << " waga wierzcholka: " << waga_wierzcholkow[i] << endl;
                            licznik_ite = 0;
                            break;
                        }
                    }
                }

            okienka_temp = okienka[i];
        }

        id_wierzcholka = 0;

        // wybieranie kolejnego wierzcholka

        int min_waga = dlugosc_okienka; // niedopasowanie!
        int index2;

        for (auto &n: waga_wierzcholkow) {
            if (n != 0 && n < min_waga) {
                min_waga = n;
            }
        }

            for (auto &el: waga_wierzcholkow) {
                if (el == min_waga) {
                    wymieszane_wierzcholki = waga_wierzcholkow;
                    int id = 0;
                    for (auto& n : wymieszane_wierzcholki) {
                        ulozone_wierzcholki.emplace_back(make_pair(n, id));
                        id++;
                    }
                    for (auto& n : ulozone_wierzcholki) {
                        if (n.first == el) {
                            index2 = n.second;
                            ulozone_wierzcholki.clear();
                            id = 0;
                            for (auto& m : wymieszane_wierzcholki) {
                                ulozone_wierzcholki.emplace_back(make_pair(m, id));
                                id++;
                            }
                            break;
                        }
                    }
                    if (find(zuzyte_wierzcholki_id.begin(), zuzyte_wierzcholki_id.end(), index2) != zuzyte_wierzcholki_id.end()) {
                        nie_pasuje_bo_uzyty.push_back(index2);
                        continue;
                    }
                    else {
                        zuzyte_wierzcholki_id.push_back(index2);
                        for (auto& t : ulozone_wierzcholki) {
                            if (t.second == index2) {
                                int waga_minus = 0;
                                for (auto& y : okienka[index2]) {
                                    if (t.first > waga_minus) {
                                        waga_minus++;
                                    }
                                    else {
                                        for (auto it = okienka[index2].begin() - waga_minus + dlugosc_okienka; it != okienka[index2].end(); it++) {
                                            wynik_DNA.push_back(*it);
                                            cout << "Dodano do rozwiazania: " << *it << endl;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        id_obecnego_wierzcholka = index2;
                        cout << "id obecnego wierzcholka: " << id_obecnego_wierzcholka << endl;
                        okienka_temp = okienka[index2];
                        waga_wierzcholkow.clear();
                        break;
                    }
                }
                zuzyte_wierzcholki_id.push_back(index2);
            }
        }



    //wypisanie wyniku
    cout << endl << endl << "Rozwiazanie: " << endl;
    for (int i = 0; i < dlugosc_DNA; i++)
    {
        cout << wynik_DNA[i] << " ";
    }

    //porownanie oryginalnej sekwencji oraz jej odtworzenia na podstawie okienek
    cout << endl << endl;
    int liczba_poprawnych_zasad = 0;
    for (int i = 0; i < dlugosc_DNA; i++) {
        if (lancuch_DNA[i] == wynik_DNA[i]) {
            liczba_poprawnych_zasad++;
        }
    }

    float poprawne_zasady_float = float (liczba_poprawnych_zasad);
    float dlugosc_DNA_float = float (dlugosc_DNA);
    float poprawnosc_rozwiazania = (poprawne_zasady_float/dlugosc_DNA_float) * 100;
    cout << "Poprawnosc rozwiazania: " << poprawnosc_rozwiazania << endl;

    return 0;
}
    //END (main)