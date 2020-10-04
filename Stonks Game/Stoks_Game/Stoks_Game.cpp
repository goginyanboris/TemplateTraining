// Stoks_Game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class ISubscriber;

class Gold {
private:
    const int ID = 1;
    double state;
    std::vector<ISubscriber*> subMass[10];

public:
    void subscribe(ISubscriber* subscriber) {
        subMass.push_front(subscriber);
    }

    void unSubscribe() {
        subMass.pop_front();
    }

    void SendState() {
        for (int i = 0; i < subMass.size(); i++) {
            subMass[i]->OnRecive(ID, state);
        }
    }
};

class Silver {
private:
    const int ID = 2;
    double state;
    std::vector<ISubscriber> subMass[10];

public:
    void subscribe(ISubscriber* subscriber) {
        subMass.push_front(subscriber);
    }

    void unSubscribe() {
        subMass.pop_front();
    }

    void SendState() {
        for (int i = 0; i < subMass.size(), i++) {
            subMass[i]->OnRecive(ID, state);
        }
    }
};

class ISubscriber {
public:
    virtual void OnRecive(double state) {};
};

class Person1 : public ISubscriber {
private:
    const int ID = 1;
public:
    void OnRecive(const int id, double state) {
        switch (id) {
        case 1:
            std::cout << "GOLD:" << state;
        case 2:
            std::cout << "SILVER:" << state;
        }
    }


};


int main()
{
    int p;
    Gold gold;
    Silver silver;
    Person1 person1;
    int subsMass[5] = { 0 };
    double wallet = 100;
    while (true) {

        std::cout << "На бирже ведутся торги следующих активов:";
        std::cout << "gold,\nsilver.";
        std::cout << "вы подписаны на:\n";
        for (int i = 1; i < subsMass.size(); i++) {
            if (subsMass[i] != 0) {
                std::cout << subsMass[i];
            }
        }
        std::cout << "будем ли подписываться?\n 1. Yes\n2. No\n";
        std::cin >> p;
        if (p == 1) {
            std::cin >> p;
            switch (p) {
            case 1:
                gold.subscribe(&person1);
            case 2:
                silver.subscribe(&person1);
            }
        }

        subsMass[p - 1] = p; // массив подписок

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
