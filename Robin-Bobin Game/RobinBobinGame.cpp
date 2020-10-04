// RobinBobinGame.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Робин барабек
//Виртуальный Метод готовки и Метод поедания
//На выходе предлагается слово : объект, который нужно правильно съесть.
//Игрок вводит через пробел числа(1 2 4) методы готовки, потом методы поедания.
//Если последовательность верная, игра продолжается, иначе барабек умирает

#include <iostream>
#include <fstream>


class RobinCookStrategy {
public:
    virtual void Cook() = 0;
};


class Pot_CookStategy : public RobinCookStrategy{ // кастрюля
    void Cook() { std::cout << "\nВарим в кастрюле\n"; }
};

class Oven_CookStategy : public RobinCookStrategy { // духовка
    void Cook() { std::cout << "\nЗапекаем в духовке\n"; }
};

class Nuke_CookStategy : public RobinCookStrategy { // микроволновка
    void Cook() { std::cout << "\nПодогреваем в микроволновке\n"; }
};


class RobinEatStrategy {
public:
    virtual void Eat() = 0;
};

class Chew_EatStrategy : public RobinEatStrategy{
public:
    void Eat() { std::cout << "\nТщательно прожуем\n"; }
};

class Swallow_EatStrategy : public RobinEatStrategy {
public:
    void Eat() { std::cout << "\nГлотаем залпом\n"; }
};

class Lubrikate_EatStrategy : public RobinEatStrategy {
public:
    void Eat() { std::cout << "\nЗальем масла\n"; }
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

    void executeStrategy(const int* eatMethod, const int* cookMethod) {
        for (int i = 0; i < 3; i++) {
            if (cookMethod[i] == 0) {
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
            if (eatMethod[i] == 0) {
                break;
            }
            switch (eatMethod[i]) {
            case 1:
                // тщательное разжевывание
                e_strategy = new Swallow_EatStrategy;
                break;
            case 2:
                // програтывание залпом
                e_strategy = new Chew_EatStrategy;
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

void writeMass(int* mass) {
    bool errorFlag = true;
    while (errorFlag) {
        if (mass[0] / 100 == 0 && mass[0] / 10 != 0) // число двузначное
        {
            // std::cout << "2 s\n";
            mass[1] = mass[0] % 10;
            mass[0] = mass[0] / 10;
            errorFlag = false;
        }
        else if (mass[0] / 1000 == 0 && mass[0] / 100 != 0 && mass[0] / 10 != 0) { // число трехзначное
            // std::cout << "3 s\n";
            mass[2] = mass[0] % 10;
            mass[0] = mass[0] / 10;
            mass[1] = mass[0] % 10;
            mass[0] = mass[0] / 10;
            errorFlag = false;
        }
        else if (mass[0] / 1000 == 0 && mass[0] / 100 != 0) { //   четрехзначное
            std::cout << "Введено больше действий, чем возможно для выполнения" << std::endl;
            std::cout << mass[0] / 100 << " " << mass[0] / 10 << " " << mass[0] << std::endl;
            std::cin >> mass[0];
        }
        else {
            // std::cout << "1 s\n";
            errorFlag = false;
        }
    }

    // std::cout << "mass: " << mass[0] << mass[1] << mass[2];
}


int main()
{
    setlocale(LC_ALL, "ru");

    std::ifstream file;
    file.open("RB_Game_products.txt");

    if (!file.is_open()) {// вызов метода is_open()
        std::cout << "Файл не открыт\n\n" << std::endl;
        return -1;
    }
    else {
        std::cout << "Файл открыт!\n" << std::endl;
        std::string product;

        int eatMass[3] = { 0 };
        int cookMass[3] = { 0 };
        while (!file.eof()) {
            
            file >> product;
            std::cout << "Робин Бобин проголодался. Следующее его блюдо: " << product;
                
            std::cout << "\nВыберете как и/или в какой последовательности его следует приготовить:\n" <<
                    "1. сварить в кастрюле\n2. запечь в духовке\n3. подогреть в микроволновке\n";
                
            std::cin >> cookMass[0];

            writeMass(cookMass);

            std::cout << "\nВыберете как и/или в какой последовательности его следует принимать внутрь:\n" <<
                    "1. програтывать залпом\n2. тщательно прожевать\n3. предварительно залив маслом\n";

            std::cin >> eatMass[0];

            writeMass(eatMass);

            //std::cout << "\ncookmass: " << cookMass[0] << cookMass[1] << cookMass[2];
            //std::cout << "\neatmass: " << eatMass[0] << eatMass[1] << eatMass[2];

            Robin game;
            game.executeStrategy(eatMass, cookMass);

            
            // проверка ввода
            int cookCheck[3] = { 0 };
            int eatCheck[3] = { 0 };
            file >> cookCheck[0];
            writeMass(cookCheck);

            file >> eatCheck[0];
            writeMass(eatCheck);

            //std::cout << "\ncookmass: " << cookCheck[0] << cookCheck[1] << cookCheck[2];
            //std::cout << "\neatmass: " << eatCheck[0] << eatCheck[1] << eatCheck[2] << std::endl;
            
            bool winCheck = true;
            for(int i = 0; i < 4; i++) {
                if (cookMass[i] != cookCheck[i] ) {
                    std::cout << "неправильно приготовленная пища вызвала несварение. GAME OVER\n\n";
                    exit(-1);
                }
                if (eatMass[i] != eatCheck[i]) {
                    std::cout << "Робин подавился и умер. GAME OVER\n\n";
                    exit(-1);
                }
            }

            if (winCheck) {
                std::cout << "Поздравляем, продукт " << product << "съеден. \n";
            }
        }
    }

    
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
