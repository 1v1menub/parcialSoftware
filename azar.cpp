#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

class Jugador {
public:
    EstrategiaJuego* estrategia;
    void ElegirEstrategia(EstrategiaJuego* e) {
        estrategia = e;
    }

    bool RecibirNumero(int n) {
        estrategia->AgregarNumero(n);
        bool g = estrategia->CalcularVictoria();
        return g;
    }
};

class Juego {
private:
    vector<Jugador*> jugadores;
    vector<int> numeros;
    bool terminado;
    Juego();
public:
    Juego(const Juego&) = delete;

    static Juego& ConseguirInstancia() {
        static Juego instancia;
        return instancia;
    }

    void GenerarNumero(int seedmod) {
        srand(time(0) + seedmod);
        int num = rand() % 100 + 1;
        NotificarJugadores(num);
    }

    void NotificarJugadores(int n) {
        for(auto &jug : jugadores) {
            if(jug->RecibirNumero(n)) {
                terminado = true;
                AnunciarGanador(jug);
            }
        }
    }

    bool AnunciarGanador(Jugador* jug) {
        cout << "El jugador con la estrategia" << jug->estrategia->nombre << endl << " ha ganado" << endl;
    }
};

class EstrategiaJuego {
public:
    vector<int> numeros;
    string nombre;
    virtual bool CalcularVictoria() = 0;

    void AgregarNumero(int n) {
        numeros.push_back(n);
    }
};



class CincoPares : public EstrategiaJuego {
public:
    CincoPares(vector<int> n) {
        numeros = n;
    }

    bool CalcularVictoria() {
        int s = numeros.size();
        int contador = 0;
        for(int i = 0; i < s; i++) {
            if(numeros[i] % 2 == 0) {
                contador++;
            }
        }
        if(contador >= 5) {
            return true;
        }
        else {
            return false;
        }
    }
};

class CincoImpares : public EstrategiaJuego {
public:
    CincoImpares (vector<int> n) {
        numeros = n;
    }

    bool CalcularVictoria() {
        int s = numeros.size();
        int contador = 0;
        for(int i = 0; i < s; i++) {
            if(numeros[i] % 2 == 1) {
                contador++;
            }
        }
        if(contador >= 5) {
            return true;
        }
        else {
            return false;
        }
    }
};

class NumeroPrimo : public EstrategiaJuego {
public:
    NumeroPrimo (vector<int> n) {
        numeros = n;
    }

    bool CalcularVictoria() {
        vector<int> primos = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        int s = numeros.size();
        int contador = 0;
        for(int i = 0; i < s; i++) {
            for(int j = 0; j < 25; j++) {
                if(numeros[i] == primos[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};

class TresMultiplos10 : public EstrategiaJuego {
public:
    TresMultiplos10 (vector<int> n) {
        numeros = n;
    }

    bool CalcularVictoria() {
        int s = numeros.size();
        int contador = 0;
        for(int i = 0; i < s; i++) {
            if(numeros[i] % 10 == 0) {
                contador++;
            }
        }
        if(contador >= 3) {
            return true;
        }
        else {
            return false;
        }
    }
};

class DosMultiplos25 : public EstrategiaJuego {
public:
    DosMultiplos25 (vector<int> n) {
        numeros = n;
    }

    bool CalcularVictoria() {
        int s = numeros.size();
        int contador = 0;
        for(int i = 0; i < s; i++) {
            if(numeros[i] % 25 == 0) {
                contador++;
            }
        }
        if(contador >= 2) {
            return true;
        }
        else {
            return false;
        }
    }
};



int main() {

    Juego& j = Juego::ConseguirInstancia();
    for(int i = 0 ; i < 5; i++ ) {
        
    }


}