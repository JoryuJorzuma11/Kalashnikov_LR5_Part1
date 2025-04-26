// Kalashnikov_LR5_Part1/Kalashnikov_MathTask.h
#ifndef KALASHNIKOV_MATHTASK_H
#define KALASHNIKOV_MATHTASK_H

#include <iostream>
#include <limits>

namespace Kalashnikov {
    // Функция контроля ввода целых чисел
    int inputControl(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                break; // Успешный ввод
            } else {
                std::cout << "Ошибка ввода! Пожалуйста, введите целое число.\n";
                std::cin.clear(); // Сброс флагов ошибок
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            }
        }
        return value;
    }

    // Метод ввода данных (ширины и высоты прямоугольника)
    void inputData(int& width, int& height) {
        std::cout << "Введите размеры прямоугольника:\n";
        width = inputControl("Ширина: ");
        height = inputControl("Высота: ");
    }

    // Метод вычисления площади прямоугольника
    int calculateRectangleArea(int width, int height) {
        return width * height;
    }
}

#endif // KALASHNIKOV_MATHTASK_H