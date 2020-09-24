// RobinBobinGame.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Робин барабек
//Виртуальный Метод готовки и Метод поедания
//На выходе предлагается слово : объект, который нужно правильно съесть.
//Игрок вводит через пробел числа(1 2 4) методы готовки, потом методы поедания.
//Если последовательность верная, игра продолжается, иначе барабек умирает

#include <iostream>

class RobinCookStrategy {
public:
    virtual void Cook() = 0;
};


class Pot_CookStategy : public RobinCookStrategy{ // кастрюля
    void Cook() { std::cout << "Варим в кастрюле"; }
};

class Oven_CookStategy : public RobinCookStrategy { // духовка
    void Cook() { std::cout << "Запекаем в духовке"; }
};

class Nuke_CookStategy : public RobinCookStrategy { // микроволновка
    void Cook() { std::cout << "Подогреваем в микроволновке"; }
};


class RobinEatStrategy {
public:
    virtual void Eat() = 0;
};

class Chew_EatStrategy : public RobinEatStrategy{
public:
    void Eat() { std::cout << "Тщательно прожуем"; }
};

class Swallow_EatStrategy : public RobinEatStrategy {
public:
    void Eat() { std::cout << " Глотаем залпом"; }
};

class Lubrikate_EatStrategy : public RobinEatStrategy {
public:
    void Eat() { std::cout << "Зальем сначала масла"; }
};


class Robin {
    RobinCookStrategy* c_strategy = {};
    RobinEatStrategy* e_strategy = {};
public:
    // Robin() {} // конструктор по умолчанию

    void setCookStrategy(RobinCookStrategy* strategy) {
        c_strategy = strategy;
    }
    void setEatStrategy(RobinEatStrategy* strategy) {
        e_strategy = strategy;
    }

    void executeStrategy(int* eatMethod, int* cookMethod) {
        for (int i = 0; i < 3; i++) {
            if (cookMethod[i] == -1) {
                break;
            }
            switch (cookMethod[i]) {
            case 1:
                // варка в кастрюле
                c_strategy = new Pot_CookStategy;
                break;
            case 2:
                // запекание в духовке
                c_strategy = new Oven_CookStategy;
                break;
            case 3:
                // подогрев в микроволновке
                c_strategy = new Nuke_CookStategy;
                break;
            } 
            c_strategy->Cook(); 
        } 

        for (int i = 0; i < 3; i++) {
            if (eatMethod[i] == -1) {
                break;
            }
            switch (eatMethod[i]) {
            case 1:
                // програтывание залпом
                e_strategy = new Chew_EatStrategy;
                break;
            case 2:
                // тщательное разжевывание
                e_strategy = new Swallow_EatStrategy;
                break;
            case 3:
                // предварительный залив масла
                e_strategy = new Lubrikate_EatStrategy;
                break;
            }
            e_strategy->Eat();
        }

    }
};


int main()
{

    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
