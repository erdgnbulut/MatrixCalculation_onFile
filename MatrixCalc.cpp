// ***************************************************************************
// ******              STUDENT NAME : ERDOGAN BULUT                      *****
// *****             STUDENT NUMBER : B221202021                         *****
// *****               ASSIGNMENT 1 : PROJECT / DESIGN                   *****
// *****                    - HONOR CODE -                               *****
// *****            I declare that this work is my own.                  *****
// *****   I already try to explaint everything with comment lines       *****
// *****    but I can explain why I did this which line you want.             *****
// ***************************************************************************

// This is a program which is create random square matrices have a random sizes and calculate special operation.

#include <iostream>     // Main C++ library.
#include <ctime>        // The library which is include srand function. We can assign variables to random values because of this library.
#include <string>       // The library which is include getline() function.
#include <fstream>      // The library which is include ifstream and ofstream libraries.
using namespace std;

class Matrices {                // It's a class which is called Matrices.
public:                         // We can access class variables everywhere because of this command.
    int coreRowSize = 0;        // We defined integer value which is called coreRowSize and assign it to 0.
    int inputRowSize = 0;       // We defined integer value which is called inputRowSize and assign it to 0.

    int** coreMatrix;           // We defined pointer to pointer matrix which is called coreMatrix.
    int** inputMatrix;          // We defined pointer to pointer matrix which is called inputMatrix.

    Matrices() {                // Constructor: Initializes coreMatrix and inputMatrix to nullptr.
        coreMatrix = nullptr;
        inputMatrix = nullptr;
    }

    ~Matrices() {               // Destructor: Cleans up memory for coreMatrix and inputMatrix.
        deleteMatrix(coreMatrix, coreRowSize);
        deleteMatrix(inputMatrix, inputRowSize);
    }

    void deleteMatrix(int** matrix, int rows) {         // This is a function which is clean memory.
        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }

    void allocateMatrices(int rows, int cols, int*** matrix) {      // This is a function which takes place from memory.
        *matrix = new int* [rows];
        for (int i = 0; i < rows; i++) {
            (*matrix)[i] = new int[cols];
        }
    }
    // These are the parameters for their own functions.
    //***************************
    int generateCoreSize();
    int generateInputSize();

    void generateCoreMatrix();
    void generateInputMatrix();

    void writeToFile();
    void readFromFile_CalculateOutput();
    //***************************
};

int main() {
    Matrices matrix;                    // We defined an object from Matrices class which is called matrix.

    int select;             // We defined variable which is called select.
    do {        // This is a loop for select operations which operation wanted from user.
        cout << "1 - Generate new matrices\n";            // Print the message to screen.
        cout << "2 - Read matrices from file\n";          // Print the message to screen.
        cin >> select;                                    // Gets select value from user.

        switch (select) {
        case 1:
            system("cls");      //This command clean the output screen.
            // These are call the functions.
            //***************************************************************************************
            matrix.coreRowSize = matrix.generateCoreSize();
            matrix.inputRowSize = matrix.generateInputSize();
            matrix.allocateMatrices(matrix.coreRowSize, matrix.coreRowSize, &matrix.coreMatrix);
            matrix.allocateMatrices(matrix.inputRowSize, matrix.inputRowSize, &matrix.inputMatrix);
            matrix.generateCoreMatrix();
            matrix.generateInputMatrix();
            matrix.writeToFile();
            //***************************************************************************************
            break;
        case 2:
            system("cls");      // This command clean the output screen.
            matrix.readFromFile_CalculateOutput(); // Call the funciton which is called readFromFile_CalculateOutput, in matrix object.
            break;
        }

    } while ((select == 1) || (select == 2));     //This line shows the continuation condition of the loop.

    return 0;
}

int Matrices::generateCoreSize() {              // This is a function which is create random core size between 2 and 5.
    srand(time(NULL));
    return rand() % 4 + 2;
}

int Matrices::generateInputSize() {             // This is a function which is create random input size between 5 and 20.
    srand(time(NULL));
    return rand() % 16 + 5;
}

void Matrices::generateCoreMatrix() {           // This is a function which is create [coreSize x coreSize] Core Matrix with random values between 1 and 10.
    srand(time(NULL));
    for (int i = 0; i < coreRowSize; i++) {
        for (int j = 0; j < coreRowSize; j++) {
            coreMatrix[i][j] = rand() % 10 + 1;
        }
    }
}

void Matrices::generateInputMatrix() {          // This is a function which is create [inputSize x inputSize] Input Matrix with random values between 10 and 20.
    srand(time(NULL));
    for (int i = 0; i < inputRowSize; i++) {
        for (int j = 0; j < inputRowSize; j++) {
            inputMatrix[i][j] = rand() % 11 + 10;
        }
    }
}

void Matrices::writeToFile() {                  // This is a function write input and core matrices to data.txt file.
    ofstream writeData("data.txt", ios::out);

        writeData << "Input Matrix\n";
        for (int i = 0; i < inputRowSize; i++) {
            for (int j = 0; j < inputRowSize; j++) {
                writeData << inputMatrix[i][j] << " ";
            }
            writeData << endl;
        }

        writeData << "Core Matrix\n";
        for (int i = 0; i < coreRowSize; i++) {
            for (int j = 0; j < coreRowSize; j++) {
                writeData << coreMatrix[i][j] << " ";
            }
            writeData << endl;
        }

        writeData.close();
}

void Matrices::readFromFile_CalculateOutput() {                 // This is function calculate outputMatrix from input and core matrices which are coming from data. And shows all matrices to screen.
    ifstream file("data.txt", ios::in);              // Open the file.
    if (file.is_open()) {               // Checks the file exists or not.

        int inputSize = 0;          // Create a variable which is called inputSize and initialize it to 0.
        int coreSize = 1;           // Create a variable which is called inputSize and initialize it to 1.

        string line;                // Create a string which is called line.
        bool foundInputMatrix = false;
        bool foundCoreMatrix = false;

        while (getline(file, line)) {
            if (line == ("Input Matrix")) {        // Checks the line is it "Input Matrix" or not.
                string::npos;
                foundInputMatrix = true;
                foundCoreMatrix = false;
            }
            else if (foundInputMatrix && line==("Core Matrix")) {        // Checks the line is it "Core Matrix" or not.
                string::npos;
                foundInputMatrix = false;
                foundCoreMatrix = true;

                getline(file, line);
            }
            else {
                if (foundInputMatrix) {
                    inputSize++;
                }
                else if (foundCoreMatrix) {
                    coreSize++;
                }
            }
        }

        file.clear();                   //This line resets the status of the file reading operation, clearing any potential errors.
        file.seekg(0, ios::beg);        // This line moves the file reading position to the beginning of the file, allowing you to continue reading the file from the start.

        getline(file, line);

        int value;

        int** matrix1 = new int* [inputSize];           // Create a dynamic array which is called matrix1.
        for (int i = 0; i < inputSize; ++i) {           // This is a loop which is assign input matrix values from data to matrix1.
            matrix1[i] = new int[inputSize];
            for (int j = 0; j < inputSize; ++j) {
                file >> value;
                matrix1[i][j] = value;
            }
        }

        getline(file, line);
        getline(file, line);

        int** matrix2 = new int* [coreSize];           // Create a dynamic array which is called matrix2.
        for (int i = 0; i < coreSize; ++i) {           // This is a loop which is assing core matrix values from data to matrix2.
            matrix2[i] = new int[coreSize];
            for (int j = 0; j < coreSize; ++j) {
                file >> value;
                matrix2[i][j] = value;
            }
        }

        int outputRowSize = inputSize - coreSize + 1;       // Create a variable which is called outputRowSize and calculate it.
        int** outputMatrix = new int* [outputRowSize];      // Create a dynamic array which is called outputMatrix.

        for (int i = 0; i < outputRowSize; ++i) {
            outputMatrix[i] = new int[outputRowSize];
        }

        for (int i = 0; i < outputRowSize; i++) {          // This is a loop which is calculating outputMatrix's values.
            for (int j = 0; j < outputRowSize; j++) {
                outputMatrix[i][j] = 0;
                for (int k = 0; k < coreSize; k++) {
                    for (int m = 0; m < coreSize; m++) {
                        outputMatrix[i][j] += matrix2[k][m] * matrix1[coreSize - k - 1 + i][coreSize - m - 1 + j];
                    }
                }
                outputMatrix[i][j] = outputMatrix[i][j] / (coreSize * coreSize);
            }
        }

        cout << "Input Matrix\n";                          // Print the message.
        for (int i = 0; i < inputSize; i++) {              // This is a loop which is print the input matrix from data.txt to screen.
            for (int j = 0; j < inputSize; j++) {
                cout << matrix1[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Core Matrix\n";                           // Print the message.
        for (int i = 0; i < coreSize; i++) {               // This is a loop which is print the core matrix from data.txt to screen.
            for (int j = 0; j < coreSize; j++) {
                cout << matrix2[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Output Matrix\n";                         // Print the message.
        for (int i = 0; i < outputRowSize; i++) {          // This a loop which is print the calculated output matrix.
            for (int j = 0; j < outputRowSize; j++) {
                cout << outputMatrix[i][j] << " ";
            }
            cout << endl;
        }

        file.close();                                       // Close the file.
    }
    else {      // If the data.txt file doesn't exists calls the following functions.
        coreRowSize = generateCoreSize();
        inputRowSize = generateInputSize();
        allocateMatrices(coreRowSize, coreRowSize, &coreMatrix);
        allocateMatrices(inputRowSize, inputRowSize, &inputMatrix);
        generateCoreMatrix();
        generateInputMatrix();
        writeToFile();
        readFromFile_CalculateOutput();
    }
}
