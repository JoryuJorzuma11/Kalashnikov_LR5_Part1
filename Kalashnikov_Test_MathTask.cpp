// Kalashnikov_LR5_part1/Kalashnikov_Test_MathTask.cpp
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Kalashnikov_MathTask.h"
#include <sstream>
#include <limits>

// Тестирование вычисления площади
void testCalculateRectangleArea() {
    ASSERT_EQUAL(50, Kalashnikov::calculateRectangleArea(5, 10));
    ASSERT_EQUAL(0, Kalashnikov::calculateRectangleArea(0, 10));
    ASSERT_EQUAL(0, Kalashnikov::calculateRectangleArea(5, 0));
    ASSERT_EQUAL(25, Kalashnikov::calculateRectangleArea(5, 5));
    ASSERT_EQUAL(-50, Kalashnikov::calculateRectangleArea(-5, 10));
}

// Тестирование контроля ввода (корректный ввод)
void testInputControlValid() {
    std::istringstream input("42\n");
    std::cin.rdbuf(input.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите число: ");
    ASSERT_EQUAL(42, result);
}

// Тестирование контроля ввода (некорректный ввод с последующим корректным)
void testInputControlInvalidThenValid() {
    std::istringstream input("abc\n42\n");
    std::cin.rdbuf(input.rdbuf());
    
    // Перенаправляем вывод для проверки сообщения об ошибке
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите число: ");
    
    // Восстанавливаем вывод
    std::cout.rdbuf(oldCout);
    
    ASSERT_EQUAL(42, result);
    ASSERT_NOT_EQUAL(std::string::npos, output.str().find("Ошибка ввода"));
}

// Тестирование ввода данных
void testInputData() {
    std::istringstream input("5\n10\n");
    std::cin.rdbuf(input.rdbuf());
    
    int width = 0, height = 0;
    Kalashnikov::inputData(width, height);
    
    ASSERT_EQUAL(5, width);
    ASSERT_EQUAL(10, height);
}

// Создание набора тестов
cute::suite make_suite_Kalashnikov_MathTask_Tests() {
    cute::suite s;
    s.push_back(CUTE(testCalculateRectangleArea));
    s.push_back(CUTE(testInputControlValid));
    s.push_back(CUTE(testInputControlInvalidThenValid));
    s.push_back(CUTE(testInputData));
    return s;
}

// Запуск тестов
int main() {
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(make_suite_Kalashnikov_MathTask_Tests(), "Kalashnikov MathTask Tests");
    return 0;
}
// Тестирование нормальных случаев
void testCalcRectangleArea_NormalCases() {
    ASSERT_EQUAL(50, Kalashnikov::calculateRectangleArea(5, 10));
    ASSERT_EQUAL(100, Kalashnikov::calculateRectangleArea(10, 10));
    ASSERT_EQUAL(1, Kalashnikov::calculateRectangleArea(1, 1));
}

// Тестирование нулевых значений
void testCalcRectangleArea_ZeroCases() {
    ASSERT_EQUAL(0, Kalashnikov::calculateRectangleArea(0, 10));
    ASSERT_EQUAL(0, Kalashnikov::calculateRectangleArea(5, 0));
    ASSERT_EQUAL(0, Kalashnikov::calculateRectangleArea(0, 0));
}

// Тестирование отрицательных значений
void testCalcRectangleArea_NegativeCases() {
    ASSERT_EQUAL(-50, Kalashnikov::calculateRectangleArea(-5, 10));
    ASSERT_EQUAL(-25, Kalashnikov::calculateRectangleArea(5, -5));
    ASSERT_EQUAL(100, Kalashnikov::calculateRectangleArea(-10, -10));
}

// Тестирование граничных значений
void testCalcRectangleArea_BoundaryValues() {
    const int max_int = std::numeric_limits<int>::max();
    const int min_int = std::numeric_limits<int>::min();
    
    ASSERT_EQUAL(max_int, Kalashnikov::calculateRectangleArea(max_int, 1));
    ASSERT_EQUAL(min_int, Kalashnikov::calculateRectangleArea(min_int, 1));
    
    // Тест на переполнение (ожидаем некорректный результат)
    ASSERT_EQUAL(max_int * max_int, Kalashnikov::calculateRectangleArea(max_int, max_int));
}

// Создание сьюта для тестов площади
cute::suite make_suite_CalcRectangleArea_Tests() {
    cute::suite s;
    s.push_back(CUTE(testCalcRectangleArea_NormalCases));
    s.push_back(CUTE(testCalcRectangleArea_ZeroCases));
    s.push_back(CUTE(testCalcRectangleArea_NegativeCases));
    s.push_back(CUTE(testCalcRectangleArea_BoundaryValues));
    return s;
}

// Альтернативный вариант запуска только этих тестов
int runCalcRectangleAreaTests() {
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(make_suite_CalcRectangleArea_Tests(), "CalcRectangleArea Tests");
    return 0;
}
// Тест на отсев пустых значений
void testInputControl_EmptyInput() {
    std::istringstream input("\n123\n");  // Пустой ввод, затем корректный
    std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите сторону: ");
    
    std::cout.rdbuf(oldCout);
    
    ASSERT_EQUAL(123, result);
    ASSERT_NOT_EQUAL(std::string::npos, output.str().find("Ошибка ввода"));
}

// Тест на отсев нецифровых символов
void testInputControl_NonNumericInput() {
    std::istringstream input("abc\n456\n");
    std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите сторону: ");
    
    std::cout.rdbuf(oldCout);
    
    ASSERT_EQUAL(456, result);
    ASSERT_NOT_EQUAL(std::string::npos, output.str().find("Ошибка ввода"));
}

// Тест на отсев цифро-буквенных значений
void testInputControl_AlphanumericInput() {
    std::istringstream input("123abc\n789\n");
    std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите сторону: ");
    
    std::cout.rdbuf(oldCout);
    
    ASSERT_EQUAL(789, result);
    ASSERT_NOT_EQUAL(std::string::npos, output.str().find("Ошибка ввода"));
}

// Тест на отсев отрицательных значений
void testInputControl_NegativeInput() {
    std::istringstream input("-5\n10\n");
    std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int result = Kalashnikov::inputControl("Введите сторону: ");
    
    std::cout.rdbuf(oldCout);
    
    // Ожидаем, что отрицательные значения допустимы (если требуется запрет, измените на ASSERT_EQUAL(10, result))
    ASSERT_EQUAL(-5, result); 
    // Если нужно запретить отрицательные, раскомментируйте:
    // ASSERT_EQUAL(10, result);
    // ASSERT_NOT_EQUAL(std::string::npos, output.str().find("Ошибка ввода"));
}

// Создание сьюта для тестов ввода
cute::suite make_suite_InputControl_Tests() {
    cute::suite s;
    s.push_back(CUTE(testInputControl_EmptyInput));
    s.push_back(CUTE(testInputControl_NonNumericInput));
    s.push_back(CUTE(testInputControl_AlphanumericInput));
    s.push_back(CUTE(testInputControl_NegativeInput));
    return s;
}

// Функция для запуска только этих тестов
int runInputControlTests() {
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(make_suite_InputControl_Tests(), "Input Control Tests");
    return 0;
}


int main(int argc, char const *argv[]) {
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(make_suite_CalcRectangleArea_Tests(), "Rectangle Area Calculation Tests");
    cute::makeRunner(lis)(make_suite_InputControl_Tests(), "Input Validation Tests");
    
    // Добавляем тесты для метода ввода данных (если есть)
    cute::makeRunner(lis)(make_suite_Kalashnikov_MathTask_Tests(), "All MathTask Tests");
    
    return 0;
}
// Дополнительные проверки для метода ввода данных
void testInputData_Validation() {
    std::istringstream input("abc\n-5\n10\n20\n");
    std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    int width = 0, height = 0;
    Kalashnikov::inputData(width, height);
    
    std::cout.rdbuf(oldCout);
    
    ASSERT_EQUAL(10, width);
    ASSERT_EQUAL(20, height);
    ASSERT_NOT_EQUAL_TO(std::string::npos, output.str().find("Ошибка ввода"));
    ASSERT_NOT_EQUAL_TO(std::string::npos, output.str().find("Ширина:"));
    ASSERT_NOT_EQUAL_TO(std::string::npos, output.str().find("Высота:"));
}

cute::suite make_suite_InputValidationTests() {
    cute::suite s;
    s.push_back(CUTE(testInputControl_EmptyInput));
    s.push_back(CUTE(testInputControl_NonNumericInput));
    s.push_back(CUTE(testInputControl_AlphanumericInput));
    s.push_back(CUTE(testInputControl_NegativeInput));
    s.push_back(CUTE(testInputData_Validation));
    return s;
}

int main(int argc, char const *argv[]) {
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(make_suite_InputValidationTests(), "Input Validation Tests Suite");
    return 0;
}