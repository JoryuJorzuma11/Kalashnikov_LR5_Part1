// Kalashnikov_LR5_Part1/Kalashnikov_MathTask.cpp
#include <iostream>
#include "Kalashnikov_MathTask.h"

int main() {
    // Установка русской локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Программа вычисления площади прямоугольника\n";
    std::cout << "=========================================\n";
    
    int width, height;
    
    // Ввод данных с использованием методов из модуля
    Kalashnikov::inputData(width, height);
    
    // Вычисление площади
    int area = Kalashnikov::calculateRectangleArea(width, height);
    
    // Вывод результата
    std::cout << "\nРезультат:\n";
    std::cout << "Площадь прямоугольника с шириной " << width 
              << " и высотой " << height 
              << " равна " << area << std::endl;
    
    return 0;
}