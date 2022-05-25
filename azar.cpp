#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

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
        nombre = "Cinco Pares";
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
        nombre = "Cinco Impares";
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
        nombre = "Numero Primo";
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
        nombre = "Tres Multiplos de 10";
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
        nombre = "Dos Multiplos de 25";
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
    Juego() {
        terminado = false;
    }
public:
    Juego(const Juego&) = delete;

    static Juego& ConseguirInstancia() {
        static Juego instancia;
        return instancia;
    }

    void GenerarNumero(int seedmod) {
        srand(time(0) + seedmod);
        int num = rand() % 100 + 1;
        for(int i = 0; i < numeros.size(); i++) {
            if(num == numeros[i]) {
                GenerarNumero(seedmod + 100);
                return;
            }
        }
        numeros.push_back(num);
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

    void AnunciarGanador(Jugador* jug) {
        cout << "El jugador con la estrategia " << jug->estrategia->nombre << " ha ganado" << endl;
    }

    bool ConseguirEstado() {
        return terminado;
    }

    vector<int> ConseguirVector() {
        return numeros;
    }

    bool InscribirJugador(Jugador* ju) {
        bool usado = false;
        for(auto &jug : jugadores) {
            if(ju->estrategia->nombre == jug->estrategia->nombre) {
                usado = true;
            }
        }
        if(!usado) {
            jugadores.push_back(ju);
            return true;
        }
        else {
            return false;
        }
    }

};

int main() {
    Juego& j = Juego::ConseguirInstancia();
    cout << "El juego se abre" << endl;
    Jugador jug1;
    jug1.ElegirEstrategia(new CincoPares(j.ConseguirVector()));
    j.InscribirJugador(&jug1);
    Jugador jug2;
    jug2.ElegirEstrategia(new CincoImpares(j.ConseguirVector()));
    j.InscribirJugador(&jug2);
    Jugador jug3;
    jug3.ElegirEstrategia(new NumeroPrimo(j.ConseguirVector()));
    j.InscribirJugador(&jug3);
    Jugador jug4;
    jug4.ElegirEstrategia(new TresMultiplos10(j.ConseguirVector()));
    j.InscribirJugador(&jug4);
    Jugador jug5;
    jug5.ElegirEstrategia(new DosMultiplos25(j.ConseguirVector()));
    j.InscribirJugador(&jug5);
    while(!j.ConseguirEstado()){
        int ctr = 0;
        cout << "El juego continua" << endl;
        j.GenerarNumero(ctr);
        ctr++;
    }
}; 
