#include <iostream>
#include <string>

using namespace std;

int* generate_row(int n, int* prev_row);

int main(int argc, char **argv) {

    // Obtain number of rows, check this is a positive integer
    int i;
    if (argc != 2) {
        cerr << "Error: incorrect usage, please provide an integer\n"; 
        return 1;      
    } else {
        try {
            i = std::stoi(argv[1]);
            cout << "Input: " << i << "\n";
        }
        catch (const invalid_argument) {
            cerr << "Error: Please input an integer\n";
            return 2;
        }
    }
    if (i < 1) {
        cerr << "Error: Integer must be positive\n";
        return 3;
    }

    int* row = new int [1];
    *row = 1;
    int* row_ptr = row;

    for (int j = 0; j < i; j++) {

        // Print the current row
        cout << "[";
        for (int k = 0; k < j; k++) {
            cout << row[k] << ", ";
        }
        cout << row[j] << "]\n";

        // Free the memory for the last row and return
        if (j == i - 1) {
            delete [] row;
            return 0;
        }

        // Get next row and then free previous row
        row_ptr = generate_row(j + 2, row);
        delete [] row;
        row = row_ptr;
    }
}

// Generates nth row which has n entries
int* generate_row(int n, int* prev_row) {
    int* output = new int [n];
    output[0] = 1;
    output[n - 1] = 1;
    for (int i = 1; i < n - 1; i++) {
        output[i] = prev_row[i - 1] + prev_row[i];
    }
    return output;
}