#include "Display.h"

Display::Display(): state("menu"), numPicked(-1), apCode1(""), apCode2("") {}


void Display::displayMenu() {
    cout << '\n' << "l---------------------------------------------------------------------l" ;
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                     Bem-Vindo a AirTrans App!                       |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|---------------------------------------------------------------------|";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  Escolha uma das opcoes seguintes:                                  |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  1. Planear um voo eficientemente                                   |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  2. Informacoes                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  3. Acerca da App                                                   |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  4. Quit                                                            |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n';

}

void Display::displayLocais() {
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                            AirTrans App                             |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|---------------------------------------------------------------------|";
    cout << '\n' << "|  Escolha a tipologia dos locais entre os quais pretende efetuar     |";
    cout << '\n' << "|   a viajem (Ex.: 1B se pretende viajar de uma cidade para um        |";
    cout << '\n' << "|   aeroporto especificos).                                           |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|     1.                       Aeroporto                      A.      |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|     2.                        Cidade                        B.      |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|     3.                      Coordenadas                     C.      |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  <- Go Back (0)                                                     |";
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n';

}

void Display::displayLocalPartida() {
    string partidaType;
    if (numPicked == 1) {
        partidaType = "|                   Escolha o aeroporto pretendido                    |"
                      "\n|                   (insira o code correspondente)                    |";
    }
    else if (numPicked == 2) {
        partidaType = "|                     Escolha a cidade pretendida                     |"
                      "\n|                   (insira o nome correspondente )                   |";
    }
    if (numPicked == 3) {
        partidaType = "|                 Escolha as coordenadas pretendidas                  |"
                      "\n|           (insira as coordenadas no estilo: LAT espaço LON)         |";
    }
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                            AirTrans App                             |";
    cout << '\n' << "|                    Escolha de Local de Partida                      |";
    cout << '\n' << "|---------------------------------------------------------------------|";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << partidaType;
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  <- Go Back (0)                                                     |";
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n';

}

void Display::displayLocalChegada() {
    string chegadaType;
    if (letterPicked == "A") {
        chegadaType = "|                   Escolha o aeroporto pretendido                    |"
                      "\n|                   (insira o code correspondente)                    |";
    }
    else if (letterPicked == "B") {
        chegadaType = "|                     Escolha a cidade pretendida                     |"
                      "\n|                   (insira o nome correspondente )                   |";
    }
    if (letterPicked == "C") {
        chegadaType = "|                 Escolha as coordenadas pretendidas                  |"
                      "\n|           (insira as coordenadas no estilo: LAT espaço LON)         |";
    }
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                            AirTrans App                             |";
    cout << '\n' << "|                    Escolha de Local de Chegada                      |";
    cout << '\n' << "|---------------------------------------------------------------------|";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << chegadaType;
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  <- Go Back (0)                                                     |";
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n';
}

void Display::displayVoo(hTable hT1, Graph g) {
    list<int> listFlights;
    list<string> airlines;
    if (numPicked == 1 && letterPicked == "A") {
        listFlights = g.getLocalToLocal(hT1[apCode1].getId(), hT1[apCode2].getId(), "", "", -1, -1, -1, -1, hT1, airlines);
    }
    else if (numPicked == 1 && letterPicked == "B") {
        listFlights = g.getLocalToLocal(hT1[apCode1].getId(), -1, "", city2, -1, -1, -1, -1, hT1, airlines);
    }
    else if (numPicked == 1 && letterPicked == "C") {
        listFlights = g.getLocalToLocal(hT1[apCode1].getId(), -1, "", "", -1, -1, coordLon2, coordLat2, hT1, airlines);
    }
    else if (numPicked == 2 && letterPicked == "A") {
        listFlights = g.getLocalToLocal(-1, hT1[apCode2].getId(), city1, "", -1, -1, -1, -1, hT1, airlines);
    }
    else if (numPicked == 2 && letterPicked == "B") {
        listFlights = g.getLocalToLocal(-1, -1, city1, city2, -1, -1, -1, -1, hT1, airlines);
    }
    else if (numPicked == 2 && letterPicked == "C") {
        listFlights = g.getLocalToLocal(-1, -1, city1, "", -1, -1, coordLon2, coordLat2, hT1, airlines);
    }
    else if (numPicked == 3 && letterPicked == "A") {
        listFlights = g.getLocalToLocal(-1, hT1[apCode2].getId(), "", "", coordLon1, coordLat1, coordLon2, coordLat2, hT1, airlines);
    }
    else if (numPicked == 3 && letterPicked == "B") {
        listFlights = g.getLocalToLocal(-1, -1, "", city2, coordLon1, coordLat1, -1, -1, hT1, airlines);
    }
    else if (numPicked == 3 && letterPicked == "C") {
        listFlights = g.getLocalToLocal(-1, -1, "", "", coordLon1, coordLat1, coordLon2, coordLat2, hT1, airlines);
    }

    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                            AirTrans App                             |";
    cout << '\n' << "|                          Plano de Viagem                            |";
    cout << '\n' << "|---------------------------------------------------------------------|";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  O trajeto mais curto para o seu destino:                           |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n';
    for (auto i: listFlights) {
        cout << g.airportIDToCode(i) << "  ->  ";
    }
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|                                                                     |";
    cout << '\n' << "|  <- Go to Menu (9)                                                  |";
    cout << '\n' << "|  <- Go Back (0)                                                     |";
    cout << '\n' << "l---------------------------------------------------------------------l";
    cout << '\n';
}

void Display::displayInfo() {

}

void Display::displayAbout() {

}

//----------------------------------------

void Display::reset() {
    if (state == "localPartida") {
        setApCode1("");
        setCoordLat1(0);
        setCoordLon1(0);
    }
    else if (state == "localChegada") {
        setApCode2("");
        setCoordLat2(0);
        setCoordLon2(0);
    }
    else {
        setApCode1("");
        setCoordLat1(0);
        setCoordLon1(0);
        setCity1("");
        setApCode2("");
        setCoordLat2(0);
        setCoordLon2(0);
        setCity2("");
    }

}

void Display::processInput(string input) {
    cout << '\n';
    vector<string> inputVec;
    string current;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            inputVec.push_back(current);
            current = "";
        }
        else { current += input[i]; }
    }
    inputVec.push_back(current);
    if (input=="1" && state=="menu") {
        setState("locais");
    }
    else if (input=="2" && state=="menu") {
        setState("info");
    }
    else if (input=="3" && state=="menu") {
        setState("about");
    }
    else if (input=="4" && state=="menu") {
        setState("menu");
    }
    //--------------------------------
    else if (input=="0" && state=="locais") {
        setState("menu");
    }
    else if ((input=="1A"||input=="1a" && state=="locais")) {
        setNumPicked(1);
        setLetterPicked("A");
        setState("localPartida");
    }
    else if ((input=="1B"||input=="1b") && state=="locais") {
        setNumPicked(1);
        setLetterPicked("B");
        setState("localPartida");
    }
    else if ((input=="1C"||input=="1c") && state=="locais") {
        setNumPicked(1);
        setLetterPicked("C");
        setState("localPartida");
    }
    else if ((input=="2A"||input=="2a") && state=="locais") {
        setNumPicked(2);
        setLetterPicked("A");
        setState("localPartida");
    }
    else if ((input=="2B"||input=="2b") && state=="locais") {
        setNumPicked(2);
        setLetterPicked("B");
        setState("localPartida");
    }
    else if ((input=="2C"||input=="2c") && state=="locais") {
        setNumPicked(2);
        setLetterPicked("C");
        setState("localPartida");
    }
    else if ((input=="3A"||input=="3a") && state=="locais") {
        setNumPicked(3);
        setLetterPicked("A");
        setState("localPartida");
    }
    else if ((input=="3b"||input=="3B") && state=="locais") {
        setNumPicked(3);
        setLetterPicked("B");
        setState("localPartida");
    }
    else if ((input=="3C"||input=="3c") && state=="locais") {
        setNumPicked(3);
        setLetterPicked("C");
        setState("localPartida");
    }

    //-------------------------------------------------
    else if (input=="0" && state=="localPartida") {
        reset();
        setState("locais");
    }
    else if (state=="localPartida" && numPicked==3) {
        coordLat1 = stof(inputVec[0]);
        coordLon1 = stof(inputVec[1]);
        setState("localChegada");
    }
    else if (state=="localPartida" && numPicked==1) {
        apCode1 = input;
        setState("localChegada");
    }
    else if (state=="localPartida" && numPicked==2) {
        city1 = input;
        setState("localChegada");
    }

    //-------------------------------------------------
    else if (input=="0" && state=="localChegada") {
        reset();
        setState("localPartida");
    }
    else if (state=="localChegada" && letterPicked=="C") {
        coordLat2 = stof(inputVec[0]);
        coordLon2 = stof(inputVec[1]);
        setState("localChegada");
    }
    else if (state=="localChegada" && letterPicked=="A") {
        apCode2 = input;
        setState("localChegada");
    }
    else if (state=="localChegada" && letterPicked=="B") {
        city2 = input;
        setState("localChegada");
    }
}

//-------------------------------------------------------------



string Display::getState() const {
    return state;
}

void Display::setState(string state) {
    Display::state = state;
}

const int &Display::getNumPicked() const {
    return numPicked;
}

void Display::setNumPicked(const int &numPicked) {
    Display::numPicked = numPicked;
}

const string &Display::getLetterPicked() const {
    return letterPicked;
}

void Display::setLetterPicked(const string &letterPicked) {
    Display::letterPicked = letterPicked;
}

float Display::getCoordLat1() const {
    return coordLat1;
}

float Display::getCoordLon1() const {
    return coordLon1;
}

float Display::getCoordLat2() const {
    return coordLat2;
}

float Display::getCoordLon2() const {
    return coordLon2;
}

const string &Display::getApCode1() const {
    return apCode1;
}

const string &Display::getApCode2() const {
    return apCode2;
}

const string &Display::getCity1() const {
    return city1;
}

const string &Display::getCity2() const {
    return city2;
}

void Display::setApCode1(const string &apCode1) {
    Display::apCode1 = apCode1;
}

void Display::setApCode2(const string &apCode2) {
    Display::apCode2 = apCode2;
}

void Display::setCoordLat1(const float &coordLat1) {
    Display::coordLat1 = coordLat1;
}

void Display::setCoordLon1(const float &coordLon1) {
    Display::coordLat1 = coordLon1;
}

void Display::setCoordLat2(const float &coordLat2) {
    Display::coordLat1 = coordLat2;
}

void Display::setCoordLon2(const float &coordLaon2) {
    Display::coordLat1 = coordLon2;
}

void Display::setCity1(const string &city1) {
    Display::city1 = city1;
}

void Display::setCity2(const string &city2) {
    Display::city2 = city2;
}


