#include <iostream>

void remove_matrix(int** hs, size_t n){
    for(size_t i = 0; i < n; ++i){
        delete[] hs[i];
    }
    delete[] hs;
}

int** initialize(size_t n, size_t m){
    int** hs = nullptr;
    try {
        hs = new int*[n];
    } catch(...) {
        std::cerr << "Memory allocation error";
        throw 2;
    }
    for(size_t i = 0; i < n; ++i){
        try {
            hs[i] = new int[m];
        } catch(...) {
            std::cerr << "Memory allocation error";
            remove_matrix(hs, i);
            throw 2;
        }
    }
    return hs;
}

int** concat_rows(const int* const* lhs, size_t n1, size_t m1, const int* const* rhs, size_t n2, size_t m2){
    int** fhs = nullptr;
    try {
        fhs = initialize(std::max(n1, n2), m1 + m2);
    } catch(...) {}
    for(size_t i = 0; i < n1; ++i){
        for(size_t j = 0; j < m1; ++j){
            fhs[i][j] = lhs[i][j];
        }
    }
    for(size_t i = 0; i < n2; ++i){
        for(size_t j = 0; j < m2; ++j){
            if(i < n1){
                fhs[i][j + m1] = rhs[i][j];
            } else {
                fhs[i][j] = rhs[i][j];
            }
        }
    }
    return fhs;
}

int all_and_all(){
    std::cout << "Enter matrix row count: ";
    size_t n1 = 0;
    if(!(std::cin >> n1)){
        std::cerr << "Wrong data";
        return 1;
    }
    if(n1 <= 0){
        std::cerr << "invalid matrix size" << std::endl;
        return 1;
    }
    std::cout << "Enter matrix column count: ";
    size_t m1 = 0;
    if(!(std::cin >> m1)){
        std::cerr << "Wrong data" << std::endl;
        return 1;
    }
    if(m1 <= 0){
        std::cerr << "Invalid matrix size" << std::endl;
        return 1;
    }
    int** lhs = nullptr;
    try {
        lhs = initialize(n1, m1);
    } catch(...) {
        return 2;
    }
    std::cout << "Enter matrix data:\n";
    for(size_t i = 0; i < n1; i++){
        for(size_t j = 0; j < m1; j++){
            if(!(std::cin >> lhs[i][j])){
                std::cerr << "Wrong data" << std::endl;
                remove_matrix(lhs, n1);
                return 1;
            }
        }
    }

    std::cout << "Enter matrix row count: ";
    size_t n2 = 0;
    if(!(std::cin >> n2)){
        std::cerr << "Wrong data";
        return 1;
    }
    if(n2 <= 0){
        std::cerr << "invalid matrix size" << std::endl;
        return 1;
    }
    std::cout << "Enter matrix column count: ";
    size_t m2 = 0;
    if(!(std::cin >> m2)){
        std::cerr << "Wrong data" << std::endl;
        return 1;
    }
    if(m2 <= 0){
        std::cerr << "Invalid matrix size" << std::endl;
        return 1;
    }
    int** rhs = nullptr;
    try {
        rhs = initialize(n2, m2);
    } catch(...) {
        return 2;
    }
    std::cout << "Enter matrix data:\n";
    for(size_t i = 0; i < n2; i++){
        for(size_t j = 0; j < m2; j++){
            if(!(std::cin >> rhs[i][j])){
                std::cerr << "Wrong data" << std::endl;
                remove_matrix(rhs, n2);
                return 1;
            }
        }
    }

    int** fhs = nullptr;
    try {
        fhs = concat_rows(lhs, n1, m1, rhs, n2, m2);
    } catch(...) {
        return 2;
    }
    for(size_t i = 0; i < std::max(n1, n2); ++i){
        for(size_t j = 0; j < m1 + m2; ++j){
            std::cout << fhs[i][j] << " ";
        }
        std::cout << "\n";
    }
    remove_matrix(fhs, std::max(n1, n2));
    return 0;
}

int main(){
    int res = all_and_all();
    std::cout << "\nResult: " << res;
    return 0;
}
