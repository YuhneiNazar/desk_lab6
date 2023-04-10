#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

int** incidence;
int** adjacency;
int vertices;
int edges;

void initGraph(string fname);
void makeIncidenceMatrix(string line, int lineNumber);
void makeAdjacencyMatrix(string line);
string adjacencyMatrixToString();
string incidenceMatrixToString();
void printMatrix(string matrix);
void saveMatrixToFile(string matrix, string filePath);

int main()
{
    char fname[] = "graph_01.txt";
    initGraph(fname);
    string fileToSave;
    int menu;
    do
    {
        cout << "Vyberit operatsiyu:" << endl;
        cout << "1 - Vyvesty matrytsyu intsydentnosti na konsol" << endl;
        cout << "2 - Vyvesty matrytsyu sumizhnosti na konsol" << endl;
        cout << "3 - Zberehty matrytsyu intsydentnosti u fail" << endl;
        cout << "4 - Zberehty matrytsyu sumizhnosti u fail" << endl;
        cout << "0 - Exit" << endl;
        cin >> menu;
        switch (menu)
        {
        case 1:
            printMatrix(incidenceMatrixToString());
            break;

        case 2:
            printMatrix(adjacencyMatrixToString());
            break;

        case 3:
            cout << "Vvedit nazvy file dlya zberezhennya: ";
            cin.ignore();
            getline(cin, fileToSave);
            fileToSave += ".txt";
            saveMatrixToFile(incidenceMatrixToString(), fileToSave);
            break;
        case 4:
            cout << "Vvedit nazvy file dlya zberezhennya: ";
            cin.ignore();
            getline(cin, fileToSave);
            fileToSave += ".txt";
            saveMatrixToFile(adjacencyMatrixToString(), fileToSave);
            break;

        default:
            break;
        }
    } while (menu != 0);
}

void initGraph(string fname) {
    ifstream input(fname);
    if (!input.is_open()) {
        cout << "Pomylka vidkryttya faylu " << fname << endl;
        return;
    }

    string line;
    getline(input, line);
    if (!line.empty()) {
        istringstream iss(line);
        iss >> vertices >> edges;
        incidence = new int* [vertices];
        adjacency = new int* [vertices];
        for (int i = 0; i < vertices; i++) {
            incidence[i] = new int[edges];
            adjacency[i] = new int[vertices];
        }
    }
    else {
        cout << "Porozhniy vkhidnyy fayl" << endl;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacency[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            incidence[i][j] = 0;
        }
    }

    int lineNumber = 0;
    while (getline(input, line)) {
        makeIncidenceMatrix(line, lineNumber);
        makeAdjacencyMatrix(line);
        lineNumber++;
    }

    input.close();
}

void makeIncidenceMatrix(string line, int lineNumber) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));

    if (from == to) {
        incidence[from - 1][lineNumber] = 2;
    }
    else {
        incidence[from - 1][lineNumber] = -1;
        incidence[to - 1][lineNumber] = 1;
    }
}

void makeAdjacencyMatrix(string line) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));
    adjacency[from - 1][to - 1]++;
}

string adjacencyMatrixToString() {
    stringstream result;
    result << "| v\\v |";
    for (int i = 1; i <= vertices; i++) {
        result << " v" << setw(2) << setfill(' ') << i << "|";
    }
    for (int i = 0; i < vertices; i++) {
        result << "\n| v" << setw(2) << setfill(' ') << i + 1 << " |";
        for (int j = 0; j < vertices; j++) {
            result << " " << setw(2) << setfill(' ') << adjacency[i][j] << " |";
        }
    }
    return result.str();
}

string incidenceMatrixToString() {
    stringstream result;
    result << "| v\\e |";
    for (int i = 1; i <= edges; i++) {
        result << " e" << setw(2) << setfill(' ') << i << "|";
    }
    for (int i = 0; i < vertices; i++) {
        result << "\n| v" << setw(2) << setfill(' ') << i + 1 << " |";
        for (int j = 0; j < edges; j++) {
            result << " " << setw(2) << setfill(' ') << incidence[i][j] << " |";
        }
    }
    return result.str();
}

void printMatrix(string matrix) {
    cout << matrix << endl;
}

void saveMatrixToFile(string matrix, string filePath) {
    ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << matrix;
        outputFile.close();
    }
    else {
        cerr << "Nemozhlyvo vidkryty fayl dlya zapysu" << endl;
    }
}
