#include <iostream>
#include <cstddef>

void remove_matrix(int** matrix, size_t rows){
    for(size_t i = 0; i < rows; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

int matrix(){
    std::cout << "Enter matrix row count:\n";
    size_t m = 0;
    if(!std::cin >> m){
        std::cout << "Couldn't write data";
        return 1;
    }
    std::cout << "Enter matrix column count:\n";
    size_t n = 0;
    if(!std::cin >> n){
        std::cout << "Couldn't write data\n";
        return 1;
    }
    const size_t rows = m;
    const size_t columns = n;
    int** matrix = nullptr;
    try{
        matrix = new int*[rows];
    }
    catch (...){
        std::cout << "Memory allocation error\n";
        return 2;
    }
    for(size_t i = 0; i < rows; i++){
        try{
            matrix[i] = new int[columns];
        }
        catch (...){
            std::cout << "Memory allocation error\n";
            remove_matrix(matrix, i);
            return 2;
        }
    }
    std::cout << "Enter matrix data:\n";
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            if(!std::cin >> matrix[i][j]){
                std::cout << "Couldn't write data\n";
                remove_matrix(matrix, rows);
                return 1;
            }
        }
    }
    std::cout << "Transposed matrix:\n";
    for(size_t i = 0; i < columns; i++){
        for(size_t j = 0; j < rows; j++){
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "\n";
    }
    remove_matrix(matrix, rows);
    return 0;
}

int main(){
    matrix();
    return 0;
}
