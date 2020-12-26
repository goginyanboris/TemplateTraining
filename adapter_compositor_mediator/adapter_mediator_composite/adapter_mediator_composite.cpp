// adapter_mediator_composite.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
/**
 * Интерфейс Посредника предоставляет метод, используемый компонентами для
 * уведомления посредника о различных событиях. Посредник может реагировать на
 * эти события и передавать исполнение другим компонентам.
 */
class Writer;

class Mediator {
public:
    virtual void Notify(Writer* sender, std::string event) const = 0;
};

/**
 * Базовый Компонент обеспечивает базовую функциональность хранения экземпляра
 * посредника внутри объектов компонентов.
 */
class Writer {
protected:
    Mediator* mediator_;

public:
    Writer(Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
};

/**
 * Конкретные Компоненты реализуют различную функциональность. Они не зависят от
 * других компонентов. Они также не зависят от каких-либо конкретных классов
 * посредников.
 */
class RomanWriter : public Writer {
public:
    void WriteRoman() {
        std::cout << "RomanWriter write a roman.\n";
        // this->mediator_->Notify(this, "R");
    }

};

/*Целевой класс объявляет интерфейс, с которым может работать функция записи текста.*/
class Target {
public:
    virtual ~Target() = default;

    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

/**
 * Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс
 * несовместим с существующим клиентским кодом. Адаптируемый класс нуждается в
 * некоторой доработке, прежде чем клиентский код сможет его использовать.
 */
class SpeechTranslateNetwork {
public:
    std::string SpecificRequest() const {
        return "tlцuбsзer eвtвaгlsnрaаrыT";
    }
};

/**
 * Адаптер делает интерфейс Адаптируемого класса совместимым с целевым
 * интерфейсом.
 */
class Adapter : public Target {
private:
    SpeechTranslateNetwork* adaptee_;

public:
    Adapter(SpeechTranslateNetwork* adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        to_reverse = "Translate result";
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};


class SpeechWriter : public Writer {
public:
    void RecordSpeech() {
        std::cout << "SpeechWriter record a speech.\n";
        this->mediator_->Notify(this, "T");
    }
    void TranslateToText() {
        std::cout << "Translate speech with adapter.\n";
        Target* target = new Target;
        

        SpeechTranslateNetwork* adaptee = new SpeechTranslateNetwork;
        Adapter* adapter = new Adapter(adaptee);
        std::cout << adapter->Request() << std::endl;
        //this->mediator_->Notify(this, "T");
    }
};

/**
 * Конкретные Посредники реализуют совместное поведение, координируя отдельные
 * компоненты.
 */
class WriteMediator : public Mediator {
private:
    RomanWriter* romans;
    SpeechWriter* speech;

public:
    WriteMediator(RomanWriter* c1, SpeechWriter* c2) : romans(c1), speech(c2) {
        this->romans->set_mediator(this);
        this->speech->set_mediator(this);
    }

    void Notify(Writer* sender, std::string event) const override {
        if (event == "R") {
            // std::cout << "Mediator reacts on R and triggers following operations:\n";
            this->romans->WriteRoman();
        }
        if (event == "S") {
            // std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->speech->RecordSpeech();
            
        }
        if (event == "T") {
            std::cout << "Mediator reacts on speech and triggers translate operation with N. network:\n";
            this->speech->TranslateToText();
        }
    }
};


int main() {
    RomanWriter* c1 = new RomanWriter;
    SpeechWriter* c2 = new SpeechWriter;
    WriteMediator* mediator = new WriteMediator(c1, c2);
    std::cout << "Write roman.\n";
    c1->WriteRoman();
    std::cout << "\n";
    std::cout << "Man speech.\n";
    c2->RecordSpeech();

    delete c1;
    delete c2;
    delete mediator;

    return 0;
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
