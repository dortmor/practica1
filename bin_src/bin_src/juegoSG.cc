#include "motorlib.hpp"
#include <fstream>

MonitorJuego monitor;

int main(int argc, char **argv)
{
  list<pair<pair<int, int>, int>> listo;

  if (argc < 6)
  {
    cout << "Faltan parametros..." << endl;
    cout << "Se necesita indicar: " << endl;
    cout << "1) Mapa" << endl
         << "2) Semilla" << endl
         << "3) Nivel (1, 2, 3 o 4)" << endl;
    cout << "4) Origen Jugador (F)" << endl
         << "5) Origen Jugador (C)"
         << "6) Orientacion Jugador" << endl;
    cout << "7) Origen Sonanbulo (F)" << endl
         << "8) Origen Sonanbulo (C)"
         << "9) Orientacion Sonanbulo" << endl;
    cout << "10) Destino (F)" << endl
         << "11) Destino (C)" << endl;
    cout << "...) Destino (F)" << endl
         << "...) Destino (C)" << endl;
  }
  else
  {
    // 1 -> mapa
    // 2 -> semilla
    // 3 -> nivel
    // 4,5 -> origen
    // 6 -> origentacion (0= norte, 1=este, 2=sur, 3=oeste)
    // 6,7 -> destino1
    // 8,9 -> destino2
    // ...
    monitor.setMapa(argv[1]);
    srand(atoi(argv[2]));
    monitor.startGame(atoi(argv[3]));

    ifstream ifile;
    ifile.open(argv[1], ios::in);

    unsigned int colSize, filSize;
    ifile >> colSize;
    ifile >> filSize;

    vector<vector<unsigned char>> mapAux;
    vector<unsigned char> colAux(colSize);

    for (unsigned int i = 0; i < filSize; i++)
    {
      mapAux.push_back(colAux);
    }

    for (unsigned int i = 0; i < filSize; i++)
    {
      for (unsigned int j = 0; j < colSize; j++)
      {
        ifile >> mapAux[i][j];
      }
    }
    ifile.close();
    // Reviso si es una posicion valida del rescatador
    if (atoi(argv[4]) != -1)
    {
      if (mapAux[atoi(argv[4])][atoi(argv[5])] == 'P' or mapAux[atoi(argv[4])][atoi(argv[5])] == 'M' or mapAux[atoi(argv[4])][atoi(argv[5])] == 'B')
      {
        cout << "Posicion (" << argv[4] << "," << argv[5] << ") no es de tipo válido para el rescatador" << endl;
        return 0;
      }
    }

    // Reviso si es una posicion valida del auxiliar
    if (atoi(argv[7]) != -1)
    {
      if (mapAux[atoi(argv[7])][atoi(argv[8])] == 'P' or mapAux[atoi(argv[7])][atoi(argv[8])] == 'M' or mapAux[atoi(argv[7])][atoi(argv[8])] == 'B')
      {
        cout << "Posicion (" << argv[7] << "," << argv[8] << ") no es de tipo válido para el colaborador" << endl;
        return 0;
      }
    }

    int i = 10;

    while (argc > i + 1)
    {
      // Reviso si es una posicion valida
      if (mapAux[atoi(argv[i])][atoi(argv[i + 1])] == 'P' and mapAux[atoi(argv[i])][atoi(argv[i + 1])] == 'M')
      {
        cout << "Posicion (" << argv[i] << "," << argv[i + 1] << ") no es de tipo válido para el objetivo" << endl;
      }
      pair<pair<int,int>,int> aux;
      aux.first.first = atoi(argv[i]);
      aux.first.second = atoi(argv[i + 1]);
      aux.second = atoi(argv[i+2]);
      listo.push_back(aux);
      i += 3;
    }

    monitor.setListObj(listo);

    monitor.inicializar(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[2]));
    monitor.get_entidad(0)->setOrientacion(static_cast<Orientacion>(atoi(argv[6])));
    monitor.get_entidad(0)->setBateria(3000);
    //monitor.get_entidad(0)->Cogio_Bikini(false);
    //monitor.get_entidad(0)->Cogio_Zapatillas(false);
    monitor.get_entidad(1)->setOrientacion(static_cast<Orientacion>(atoi(argv[9])));
    monitor.get_entidad(1)->setBateria(3000);
    //monitor.get_entidad(1)->Cogio_Bikini(false);
    //monitor.get_entidad(1)->Cogio_Zapatillas(false);
    monitor.setPasos(3000);
    monitor.setRetardo(0);

    // Reviso si es una posicion valida
    // if (mapAux[atoi(argv[7])][atoi(argv[8])] == 'P' and mapAux[atoi(argv[7])][atoi(argv[8])] == 'M')
    //   cout << "Posicion (" << argv[7] << "," << argv[8] << ") no es de tipo válido para el objetivo" << endl;

    // monitor.addObjetivo(atoi(argv[7]),atoi(argv[8]));
    // monitor.setObjFil(atoi(argv[7]));
    // monitor.setObjCol(atoi(argv[8]));

    monitor.juegoInicializado();

    lanzar_motor_juego2(monitor);
  }
  exit(EXIT_SUCCESS);
}
