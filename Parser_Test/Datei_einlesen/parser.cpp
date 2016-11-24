//Erster Enwurf einer Einlese Funktion

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include <stdlib.h>
#include<vector>

using namespace std;

class parser{
    public:

    public:
        parser(){

        }

        void gamesize(string filename, vector<int> &xy_size)
        {
            ifstream infile (filename.c_str());
            char buffer[80];
            int MAX=80;
            int found;

//            if (infile==NULL)                     Gibt Probleme bei QT
//            {
//                printf("Fehler beim einlesen");
//                return;
//            }

            infile.getline(buffer, MAX);

            found = string(buffer).find("x=") + 2;
            if (isdigit(buffer[found]))
            {
                xy_size.at(0) = atoi (buffer + found);
            }

            found = string(buffer).find("y=") + 2;
            if (isdigit(buffer[found]))
            {
                xy_size.at(1) = atoi (buffer + found);
            }


        }

        void gameallocation(string filename, vector<vector<int> >  &xy_values)
        {
            ifstream infile (filename.c_str());
            char buffer[80];
            int MAX=80;
            int x, y, z, found;

//            if (infile==NULL)
//            {
//                printf("Fehler beim einlesen");
//                return;
//            }

            infile.getline(buffer, MAX);            //Die ersten zwei Zeilen überspringen
            infile.getline(buffer, MAX);
            infile.getline(buffer, MAX);            //Hier stehen jetzt die Daten für die Felder

            while (!infile.eof())
            {
                found = string(buffer).find("x") + 1;

                if (isdigit(buffer[found]))
                {
                    x = atoi (buffer + found);      //String in Zahl umwandeln
                }

                found = string(buffer).find("y") + 1;
                if (isdigit(buffer[found]))
                {
                    y = atoi (buffer + found);
                }

                found = string(buffer).find("z=") + 2;
                if (isdigit(buffer[found]))
                {
                    z = atoi (buffer + found);
                }

                xy_values[x][y] = z;

                infile.getline(buffer, MAX);
            }

            return;
        }

        ~parser(){}
};

int main()
{
    string file = "game.txt";
    int ausgabe;
    parser loadgame;
    vector<int>size(2);
    vector<vector<int> > values;

    loadgame.gamesize (file, size);

    values.resize(size[0]);					//Passe Werte Vektor auf Spielfeldgr��e an, x-Werte

    for (int i=0; i<size[0]; i++)                //Passe Werte Vektor auf Spielfeldgr��e an, y-Werte
    {
        values[i].resize(size[1]);
    }

    loadgame.gameallocation (file, values);

    for (int i=0; i<size[0]; i++)
    {
        for (int j=0; j<size[1]; j++)
        {
            printf("%d, ", values[j][i]);
        }
        printf("\n");
    }

    return 0;
}

