// IOC_Workers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class IWorker {
public:
    virtual void water() = 0;
    virtual void coffe() = 0;
    //virtual void food() = 0;
    //virtual void newspaper() = 0;
    //virtual void idontknow() = 0;
};

void IWorker::water() {
    std::cout << "Я пошел в ближайший магазин\n";
    std::cout << "Купил воду\n";
    std::cout << "Идя обратно, решил зайти в кофейню\n";
    std::cout << "Потом мне позвонили из Африки\n";
    std::cout << "Вернулся в офис\n";
}


void IWorker::coffe() {
    std::cout << "Я пошел в ближайшую кофейню\n";
    std::cout << "Купил кофе\n";
    std::cout << "Себе тоже кофейку бахнул\n";
    std::cout << "Потом мне позвонили из Японии\n";
    std::cout << "Вернулся в офис\n";
}

class Boss
{
private:
    //int time = 100;
    //int work = 0;
    //int workersCount = 10;
public:
    void askForSomething(IWorker* worker, int something)
    {
        switch (something) {
        case 1:
            worker->water();
        case 2:
            worker->coffe();

        }
        
    }
};


class MainDeveloper : public IWorker {
    void water() override {
        IWorker::water();
    }

    void coffe() override {
        IWorker::coffe();
    }
};



int main()
{

    setlocale(LC_ALL, "ru");

    int choise;
    Boss boss;
    IWorker* worker{nullptr};
    std::cout << "Кого посылаем?\n1. Main Developer\n";
    std::cin >> choise;
    switch (choise) {
    case 1:
       worker = new MainDeveloper;
    }

    std::cout << "За чем посылаем?\n";
    std::cout << "1. water,\n2. coffe.\n";
    std::cin >> choise;
    if (worker != nullptr) {
        boss.askForSomething(worker, choise);
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
