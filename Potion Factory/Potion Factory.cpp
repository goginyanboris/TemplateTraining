// Potion Factory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class IPotionBrew {
public:
    virtual ~IPotionBrew() {};
    virtual void  The_choice_of_container() const = 0; // выбор емкости для зелья
    virtual void Basic_ingredient() const = 0; // выбор основного ингредиента
    virtual void Seasoning() const = 0; // выбор второго ингредиента
    virtual void Spell() const = 0; // заклинание
};

void IPotionBrew::The_choice_of_container() const {
    std::cout << "Квадратная, Круглая, Овальная\n";
}

void IPotionBrew::Basic_ingredient() const {
    std::cout << "Волос единорога, корень мандрагоры, крыло летучей мыши\n";
}

void IPotionBrew::Seasoning() const {
    std::cout << "Пыльца феи, порошок из мух, личинки муравьев, слизь улиток, корица\n";
} // выбор второго ингредиента


void IPotionBrew::Spell() const {
    std::cout << "Аларте Аскендаре, Баубиллиус, Брахиам Эмендо, Випера Эванеско\n";
} // заклинание

/**
 * Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
 * Все вариации продукта должны реализовывать этот интерфейс.
 */
class Heal_potion { // противоядия против вреднных зелий
public:
    virtual ~Heal_potion() {};
    virtual std::string Brew() const = 0;
};

/**
 * Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class Potion_of_hiccups : public Heal_potion { // зелье от икоты
public:
    std::string Brew() const override {
        return "the potion of hiccups is ready\n";
    }
};

class HiccupsPotionBrew : public IPotionBrew {
private:
    Potion_of_hiccups* potion;
public:
    void Reset() {
        if (this->potion != nullptr) {
            delete potion;
        }
        this->potion = new Potion_of_hiccups;
    }

    HiccupsPotionBrew() {
        potion = new Potion_of_hiccups;
    }

    ~HiccupsPotionBrew() {
        delete potion;
        potion = nullptr;
    }

    void  The_choice_of_container() const override{
        IPotionBrew::The_choice_of_container();
    
    } // выбор емкости для зелья

    void Basic_ingredient() const {
        IPotionBrew::Basic_ingredient();
    }

    void Seasoning() const {
        IPotionBrew::Seasoning();
    } // выбор второго ингредиента

    void Spell() const {
        IPotionBrew::Spell();
    } // заклинание

    Potion_of_hiccups* GetPotion() { // Конкретные Строители должны предоставить свои собственные методы 
        Potion_of_hiccups* result = this->potion; // получения результатов.
        this->Reset();
        return result;                   
    }
};

class Potion_from_burping : public Heal_potion { // Зелье от рыгания
    std::string Brew() const override {
        return "the potion of beauty is ready\n";
    }
};

class Potion_of_silence : public Heal_potion {// зелье молчания
    std::string Brew() const override {
        return "the potion of beauty is ready\n";
    }
};


class Harmful_potion { // вредные зелья
public:
    virtual ~Harmful_potion() {};

    virtual std::string Brew() const = 0;

    virtual std::string Blend(const Heal_potion& collaborator) const = 0;


};

/**
 * Конкретные Продукты создаются соответствующими Конкретными Фабриками.
 */
class Hiccup_potion : public Harmful_potion { // икотное зелье
public:
    std::string Brew() const {
        return "the Hiccup potion is ready\n";
    }
    /**
     * Продукт Hiccup_potion может корректно работать только с Продуктом Potion_of_hiccups. Тем не менее, он
     * принимает любой экземпляр Абстрактного Продукта Heal_potion в качестве аргумента.
     */
    std::string Blend(const Heal_potion& collaborator) const override {
        const std::string result = collaborator.Brew();
        return "The mixture of Hiccup potion with ( " + result + " )";
    }
};

class Belch_potion : public Harmful_potion { // Зелье рыгания — заставляет беcперерывно рыгать.
public:
    std::string Brew() const {
        return "the Belch potion is ready\n";
    }

    std::string Blend(const Heal_potion& collaborator) const override {
        const std::string result = collaborator.Brew();
        return "The mixture of Belch potion with ( " + result + " )";
    }
};


class Potion_of_laughter : public Harmful_potion { // Зелье смеха — зелье, вызывающее смех у выпившего его.
public:
    std::string Brew() const override {
        return "the Potion of laughter is ready\n";
    }
    /**
     * Продукт B2 может корректно работать только с Продуктом A2. Тем не менее, он
     * принимает любой экземпляр Абстрактного Продукта А в качестве аргумента.
     */
    std::string Blend(const Heal_potion& collaborator) const override {
        const std::string result = collaborator.Brew();
        return "The mixture of Potion of laughter with ( " + result + " )";
    }
};


class AbstractPotionFactory {
public:
    virtual Heal_potion* CreateHealPotion() const = 0;
    virtual Harmful_potion* CreateHarmfulPotion() const = 0;
};


class Hiccup_factory : public AbstractPotionFactory {
public:
    Heal_potion* CreateHealPotion() const override {
        return new Potion_of_hiccups;
    }
    Harmful_potion* CreateHarmfulPotion() const override {
        return new Hiccup_potion;
    }
};

class Burp_factory : public AbstractPotionFactory {
public:
    Heal_potion* CreateHealPotion() const override {
        return new Potion_from_burping;
    }
    Harmful_potion* CreateHarmfulPotion() const override {
        return new Belch_potion;
    }
};

class Funny_factory : public AbstractPotionFactory {
public:
    Heal_potion* CreateHealPotion() const override {
        return new Potion_of_silence;
    }
    Harmful_potion* CreateHarmfulPotion() const override {
        return new Potion_of_laughter;
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
