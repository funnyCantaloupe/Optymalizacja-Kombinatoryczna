#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// ponizej wpisujemy parametry

int dna_length = 12;
int window = 3;
float positive_errors_percentage = 10;
float negative_errors_percentage = 10;


char alphabet[4] = {'A', 'T', 'C', 'G'};
char *lancuchDNA = new char[dna_length];
string *okienka = new string[dna_length];


void dna_chain() {
    int RandIndex;
    for (int i = 0; i < dna_length; i++) {
        RandIndex = rand() % 4;
        lancuchDNA[i] = alphabet[RandIndex];
    }
}

void windows() {
    for (int i = 0; i < dna_length - window + 1; i++) {
        for (int j = 0; j < window; j++) {
            okienka[i] = okienka[i] + lancuchDNA[i + j];
        }
    }
}

void add_positive_errors() { // nie skonczone, mozna zmienic koncepcje tego
    int number_of_positive_errors = (positive_errors_percentage/100) * dna_length;
    int rand_p_err;
    vector<int> randomized_errors;
    for (int i = 0; i < number_of_positive_errors; i++) {
        rand_p_err = rand() % (dna_length - window + 1);
        for (auto& n : randomized_errors) {
            if (rand_p_err == n)
                break;
        }
    }
}

void add_negative_errors() {

}

int main() {
    srand(time(NULL));
    dna_chain();
    windows();


    for (int i = 0; i < dna_length; i++) {
        cout << lancuchDNA[i];
    }

    cout << endl << endl;

    for (int i = 0; i < dna_length; i++) {
        cout << okienka[i] << endl;
    }
     

    delete[] lancuchDNA;
    delete[] okienka;
    return 0;
}
