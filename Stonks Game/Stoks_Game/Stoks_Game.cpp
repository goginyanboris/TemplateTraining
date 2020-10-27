// Stoks_Game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include <string>
#include <cmath>


class IObserver // interface publisher издатель
{
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string & message_from_subject) = 0;
};

class ISubject { // interface Издателя
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject // издатель
{
private:
    std::list<IObserver*> listPublisher;

public:
    virtual ~Subject(){
        std::cout << "Subject delete\n";
    }

    // Управление подпиской в Издателе
    void Attach(IObserver* observer) override {
        listPublisher.push_back(observer);
    }

    void Detach(IObserver* observer) override {
        listPublisher.remove(observer);
    }

    void Notify() override {
        std::list<IObserver*>::iterator it = listPublisher.begin();

        std::cout << "There are " << listPublisher.size() << " observers in the list.\n";

    }

    virtual void ShowName() = 0;

    virtual double getState() = 0;
    
};

class Observer : public IObserver { // подписчик, наблюдатель
private:
    std::string messageFromSubject;
    Subject& m_subject; // издатель
    static int staticNumber;
    int m_number;
    int count; // кол-во продуктов определенного издателя

    static double money;
public:
    Observer(Subject& subject) : m_subject(subject) {
        this->m_subject.Attach(this);
        ++Observer::staticNumber;
        std::cout << "Подписка оформлена.\n";
        this->m_number = Observer::staticNumber;
    }

    virtual ~Observer()
    {
        std::cout << "Observer \"" << this->m_number << "\" was delete.\n";
    }

    void PrintInfo() {
        std::cout << "Observer \"" << this->m_number << "\": a new message is available --> " << this->messageFromSubject << "\n";
    }

    void Update(const std::string& message_from_subject) override {
        messageFromSubject = message_from_subject;
        PrintInfo();
    }

    static void getBalance() {
        std::cout << "\nУ вас на счету: " << money << std::endl;
    }

    virtual void ShowSubjectName() {
        m_subject.ShowName();
    }

    virtual bool Buy(int choise) {
        if (choise * m_subject.getState() < money) {
            money -= choise * m_subject.getState();
            count += choise;
            return false;
        }
        else {
            std::cout << "Деняк не ма\n";
            return true;
        }
    }
   
};

int Observer::staticNumber = 0;
double Observer::money = 1000.0;

class Gold : public Subject {  // 
private:
    double state;
    std::string name = "Gold";
public:

    Gold() {
        state = (rand() % 100 + 1);
    }

    void UpdateState()
    {
        state += (rand() % 200 + 1) * pow(-1, rand());
    }

    void ShowState() {
        std::cout << "Price on Gold = " << state << std::endl;
    }

    virtual void ShowName() {
        std::cout << name << std::endl;
    };

    double getState() { return state; }

};

class Silver : public Subject { // издатель
private:
    double state;
    std::string name = "Silver";
public:
    Silver() {
        state = (rand() % 100 + 1);
    }

    void UpdateState()
    {
        state += (rand() % 100 + 1) * pow(-1, rand());
    }

    void ShowState() {
        std::cout << "Price on Silver = " << state << std::endl;
    }

    virtual void ShowName() {
        std::cout << name << std::endl;
    };

    double getState() { return state; }
};

class Iterator {
private: 
    Observer** m_data;
    int m_it = 0;
    int m_lenght;
public: 
    Iterator(Observer** data, int lenght) : m_lenght(lenght) {
        m_data = data;
    }

    void First() {
        //std::cout << "first\n";
        m_it = 0;
    }

    void Next() {
        //std::cout << "next\n";
        m_it++;
    }

    bool IsDone() {
        return (m_it == m_lenght);
    }

    Observer* Current() {
        //std::cout << "current\n";
        
        return m_data[m_it];
        
        
    }
};




int main()
{
    setlocale(LC_ALL, "ru");

    Gold* gold = new Gold;
    Silver* silver = new Silver;

    Observer** playerActive = new Observer*[2]{nullptr, nullptr}; //коллекция; 0- отвечает за золото // 1- отвечает за серебро

    int choise;
    double choicePrice;
    bool moneyOver = false;
    int iteration = 0;

    Iterator it(playerActive, 2);
    while (true) {
        if (iteration > 0) {
            std::cout << "У вас для продажи имеются следующие активы:\n";
            it.First();
            while (!it.IsDone()) {
                if(it.Current() != nullptr)
                    it.Current()->ShowSubjectName();
                it.Next();
            }
        }

        std::cout << "На бирже ведутся торги.\n";
        silver->ShowState();
        gold->ShowState();

        std::cout << "Чем будем торговать?\n1. Золотом \n2. Серебром\n";
        std::cin >> choise;
        if (choise == 1) {
            if (playerActive[0] == nullptr)
                playerActive[0] = new Observer(*gold);

            Observer::getBalance();
            std::cout << "\nСколько будем покупать Золота?\n";
            std::cin >> choicePrice;
            moneyOver = playerActive[0]->Buy(choicePrice);

        }
        else if  (choise == 2) {
            if (playerActive[1] == nullptr)
                playerActive[1] = new Observer(*silver);

            Observer::getBalance();
            std::cout << "\nСколько будем покупать Серебра?\n";
            std::cin >> choicePrice;
            moneyOver = playerActive[1]->Buy(choicePrice);
        }
        else {
            playerActive[0] = new Observer(*gold);
            playerActive[1] = new Observer(*silver);

            Observer::getBalance();
            std::cout << "Сколько будем покупать Золота?\n";
            std::cin >> choicePrice;
            moneyOver = playerActive[0]->Buy(choicePrice);

            std::cout << "Сколько будем покупать Серебра?\n";
            std::cin >> choicePrice;
            moneyOver = playerActive[1]->Buy(choicePrice);
        }

        if (moneyOver == true) {
            std::cout << "Game Over";
            exit(-1);
        }

        ++iteration;
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
