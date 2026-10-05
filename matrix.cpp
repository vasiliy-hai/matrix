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
    if(!(std::cin >> m)){
        std::cerr << "Couldn't write data";
        return 1;
    }
    std::cout << "Enter matrix column count:\n";
    size_t n = 0;
    if(!(std::cin >> n)){
        std::cerr << "Couldn't write data" << std::endl;
        return 1;
    }
    if(m <= 0 || n <= 0){
        std::cerr << "invalid matrix size" << std::endl;
        return 1;
    }
    const size_t rows = m;
    const size_t columns = n;
    int** matrix = nullptr;
    try{
        matrix = new int*[rows];
    }
    catch (...){
        std::cerr << "Memory allocation error" << std::endl;
        return 2;
    }
    for(size_t i = 0; i < rows; i++){
        try{
            matrix[i] = new int[columns];
        }
        catch (...){
            std::cerr << "Memory allocation error" << std::endl;
            remove_matrix(matrix, i);
            return 2;
        }
    }
    std::cout << "Enter matrix data:\n";
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            if(!(std::cin >> matrix[i][j])){
                std::cerr << "Couldn't write data" << std::endl;
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
