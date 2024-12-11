#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// OHJELMAN VAKIOT

const int ALENNUKSET[3] = { 0, 10, 20 }; // Alennukset
const int YHH = 100; // Yhden hengen huoneen hinta
const int KHH = 150; // Kahden hengen huoneen hinta

//ALIOHJELMAT

// Arvotaan parillinen huonemäärä väliltä 40-300
int arvonta() {
    int maara = (rand() % 131 + 40) / 2 * 2;
    return maara;
}

// Alennuksen arvonta (0%, 10% tai 20%)
int alennuksenarvonta() {
    return ALENNUKSET[rand() % 3];
}

// Saatavuuden tarkistus
bool saatavuus(const vector<bool>& huoneet, int huoneNumero) {
    return !huoneet[huoneNumero - 1];
}

// Varataan huone ja lisätään varauslistaan 
void huoneenvaraus(vector<bool>& huoneet, vector<string>& varaukset, int huoneNumero,
    const string& nimi, int oidenMaara, int hintaPerYksiO) {
    huoneet[huoneNumero - 1] = true; // Merkintä
    int varausnumero = rand() % 90000 + 10000; // Varaus numeron arvonta
    int alennus = alennuksenarvonta(); // Alennuksen arvonta 
    double loppusumma = oidenMaara * hintaPerYksiO * ((100 - alennus) / 100.0);

    // Varauksen lisääminen varauslistaan 
    string varaus = to_string(varausnumero) + ": " + nimi +
        ", Huone: " + to_string(huoneNumero) +
        ", Yhteensä: " + to_string(oidenMaara) + " yötä, Loppusumma: " +
        to_string(loppusumma) + " euroa";
    varaukset.push_back(varaus);

    // Varauksen tietojen tulostus
    cout << "Varaus onnistui! Varausnumero: " << varausnumero << endl;
    cout << "Alennus: " << alennus << "%" << endl;
    cout << "Loppusumma: " << fixed << setprecision(2) << loppusumma << " euroa" << endl;
}

// Varauksen haku nimellä
void haku_nimella(const vector<string>& varaukset, const string& hakunimi) {
    cout << "\nVaraukset antamallesi nimellä \"" << hakunimi << "\":\n";
    bool loytyi = false;
    for (const string& varaus : varaukset) {
        if (varaus.find(hakunimi) != string::npos) {
            cout << varaus << endl;
            loytyi = true;
        }
    }
    if (!loytyi) {
        cout << "Listoistamme ei valitettavasti löytynyt varausta antamallasi nimellä\n";
    }
}

// Tulostaa päävalikon käyttäjälle
void menu() {
    cout << "Mitä haluaisit tehdä\n";
    cout << "Varausten tekeminen\n";
    cout << "1. Yhden hengen huone\n";
    cout << "2. Kahden hengen huone\n";
    cout << "Varausten tarkastelu\n";
    cout << "3. Näytä kaikki varaukset\n";
    cout << "4. Hae varauksia nimellä\n";
    cout << "5. Poistu ohjelmasta\n";
}

// Virhesyötön tarkistus
int tarkistus(int alaraja, int ylaraja) {
    int arvo;
    while (true) {
        cin >> arvo;
        if (cin.fail() || arvo < alaraja || arvo > ylaraja) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Virhe! Syötä luku " << alaraja << "-" << ylaraja << ": ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return arvo;
        }
    }
}

//PÄÄOHJELMA

int main() {
    srand(time(0)); // Satunnaislukugeneraattorin luonti

    // Huonemäärän arvonta satunnaisesti
    int huoneidenMaara = arvonta();
    vector<bool> yhdenHengenHuoneet(huoneidenMaara / 2, false);
    vector<bool> kahdenHengenHuoneet(huoneidenMaara / 2, false);
    vector<string> varaukset;

    cout << "Tervetuloa Hotelli Tamkin varausjärjestelmän etusivulle." << endl;
    cout << "Hotellissa on vapaana  " << huoneidenMaara / 2 << " yhden hengen huonetta ja "
        << huoneidenMaara / 2 << " kahden hengen huonetta.\n";

    bool kaynnissa = true;
    while (kaynnissa) {
        menu(); // Päävalikko 
        cout << "Valintasi: ";
        int valinta = tarkistus(1, 5);

        switch (valinta) {
        case 1: { // Yhden hengen huoneen varaus
            string nimi;
            int oidenMaara, huoneNumero;

            cout << "Varaajan nimi? ";
            getline(cin, nimi);
            cout << "Montako yötä ajattelit viipyä? ";
            oidenMaara = tarkistus(1, numeric_limits<int>::max());

            cout << "Anna huoneen numero (1-" << huoneidenMaara / 2 << "): ";
            huoneNumero = tarkistus(1, huoneidenMaara / 2);

            if (saatavuus(yhdenHengenHuoneet, huoneNumero)) {
                huoneenvaraus(yhdenHengenHuoneet, varaukset, huoneNumero, nimi, oidenMaara, YHH);
            }
            else {
                cout << "Valittu huone on jo varattu.\n";
            }
            break;
        }
        case 2: { // Kahden hengen huoneen varaus
            string nimi;
            int oidenMaara, huoneNumero;

            cout << "Varaajan nimi? ";
            getline(cin, nimi);
            cout << "Montako yötä ajattelit viipyä? ";
            oidenMaara = tarkistus(1, numeric_limits<int>::max());

            cout << "Anna huoneen numero (" << huoneidenMaara / 2 + 1 << "-" << huoneidenMaara << "): ";
            huoneNumero = tarkistus(huoneidenMaara / 2 + 1, huoneidenMaara);

            if (saatavuus(kahdenHengenHuoneet, huoneNumero - huoneidenMaara / 2)) {
                huoneenvaraus(kahdenHengenHuoneet, varaukset, huoneNumero - huoneidenMaara / 2, nimi, oidenMaara, KHH);
            }
            else {
                cout << "Valittu huone on jo varattu.\n";
            }
            break;
        }
        case 3: { // Kaikkien varausten näyttäminen
            if (varaukset.empty()) {
                cout << "Ei varauksia.\n";
            }
            else {
                cout << "\nVaraukset:\n";
                for (const string& varaus : varaukset) {
                    cout << varaus << endl;
                }
            }
            break;
        }
        case 4: { // Varausten hakeminen nimellä
            string hakunimi;
            cout << "Anna nimi: ";
            getline(cin, hakunimi);
            haku_nimella(varaukset, hakunimi);
            break;
        }
        case 5: // Ohjelman lopetus
            cout << "Kiitos käynnistä! Toivottavasti tapaamme jälleen.\n";
            kaynnissa = false;
            break;
        }
    }
    return 0;
}
