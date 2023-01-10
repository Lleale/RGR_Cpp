#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Тема: #2 Заказы на производстве

// Задание:
// Создать программу по управлению объектами данных по указанной теме с  использованием ООП и реализовывать изученные паттерны.
// Необходимо создать минимум 3 объекта сущности разных видов и указать взаимодействие между объектами.Реализовать интерфейсы ввод,
// вывода и редактитрвоания сущьностей.Реализовать ручной ввод сущностей, загрузку из файла и сохранения в файл, удаление выбранных сущностей.
// Данные между запусками программы хранить в структурированном текстовом файле.


// Генератор случайных чисел
int GetRandomNumber(int min, int max)
{
    // Установить генератор случайных чисел
    srand(time(NULL));
    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);

    return num;
}

// Товар
class Product {
protected:
	string name;
	int cost, vol;
public:
    // конструктор товара (присваивает значения по умолчанию)
    Product() { name = "\t"; cost = 0; vol = 0; }
    // присвоить конкретные значения переменным
    void create(const string n, const int v, const int c) { name = n; vol = v; cost = c; }
    // функции возвращающие значения переменных
    string getName() { return name; }
    int getVolume() { return vol; }
	int getCost() { return cost; }
};

// Фабрика товара
class fabrikaOr {
public:
    // создает товар с заданными параметрами и возвращает его
    Product* create(string* mas) {
        Product* res = new Product;
        res->create(mas[0], stoi(mas[1]), stoi(mas[2]));
        return res;
    }
};

// Заказ
class Order {
protected:
	fabrikaOr store;
    int id = GetRandomNumber(100000, 999999); // номер заказа (шестизначное число)
    int countItems = 0; // настоящее количество элементов массива
    Product* items[100] = {};
    string name, phone;

public:
    // функции возвращающие значения переменных
    int getID() { return id; }
    int getCount() { return countItems; }
    Product** getItems() { return items; }
    string getName() { return name; }
    string getPhone() { return phone; }

    // присваивает значения имени и номера телефона клиента
	void create(const string n, const string ph, const int count, string (*ms)[3], const int id_in) {
        // если был передан номер заказа то сохраняет и его (подразумевается что номер как минимум не равен нулю)
        if (id_in != 0) id = id_in;
        name = n;
        phone = ph;
        //заполняет массив товарами
        for (int i = 0; i < count; i++) {
            items[i] = store.create(ms[i]);
            countItems++;
        }
	}
    // выводит информацию о заказе и о каждом товаре в нём
    void printOrder() {
        cout << "#id " << id << endl;
        cout << "\tClient's name: " << name << endl;
        cout << "\tClient's phone: " << phone << endl;
        for (int i = 0; i < countItems; i++) {
            cout << "\t\t|Name: " << items[i]->getName() << " | Price per unit: " << items[i]->getCost() << " | Amount: " << items[i]->getVolume() << '|' << endl;
        }
    }
};


class fabrikaDep {
public:
    // создает заказ с заданными параметрами и возвращает его
    Order* create(const string n, const string ph, const int count, string(*ms)[3], const int id) {
        Order* res = new Order;
        res->create(n, ph, count, ms, id);
        return res;
    }
};

// "Бухгалтерия"
class depart {
private:
    fabrikaDep store;
    Order* orders[100] = {};
    int countOrders = 0; // настоящее количество элементов массива

public:
    // функции возвращающие количество заказов и сам массив заказов
    int getCount() { return countOrders; }
    Order** getOrders() { return orders; }

    // вывод всех заказов
    void printOrders() {
        for (int i = 0; i < countOrders; i++) {
            cout << '[' << i + 1 << "] ";
            orders[i]->printOrder();
        }
    }
    // вывод одного заказа по индексу
    void printOneOrder(const int ind) {
        cout << '[' << ind + 1 << "] ";
        orders[ind]->printOrder();
    }
    // вызов создания нового заказа
    void newOrder(const string n, const string ph, const int count, string (*ms)[3], const int id, const int edit) {
        // если edit равен 0, то создается новый заказ в конце списка
        if (edit == 0) {
            orders[countOrders] = store.create(n, ph, count, ms, id);
            countOrders++;
        }
        else
        {
            // если же edit равен отличному от 0 значению, то производится перезапись заказа
            orders[edit-1] = store.create(n, ph, count, ms, id);
        }
    }
    // удаляет заказ по индексу путем сдвига части массива на одну ячейку и уменьшения его размера
    void delOrder(const int ind) {
        if ((ind >= 0) && (ind < countOrders)) {
            for (int i = ind; i < countOrders - 1; i++) { orders[i] = orders[i + 1]; }
            countOrders--;
        }
    }
};

// Меню v2.0
class Goodctrl {
private:
    int choice1 = 0; // выбор пользователя в главном меню
    int kg = 0; // останавливает программу, чтобы можно было прочитать вывод данных
    depart* Byhgalter = new depart; // бухгалтерия

    // Главное меню
    void mainMenu(void) {
        system("cls");
        cout << "Main Menu\n\n";
        cout << "[1] Show all orders\n";
        cout << "[2] New order\n";
        cout << "[3] Edit order\n";
        cout << "[4] Delete order from list\n";
        cout << "[5] Export to file\n";
        cout << "[6] Import from file\n";
        cout << "[0] Quit\n";
        cout << "Please choose: ";
        cin >> choice1;
    }

    // Вывод всех заказов в консоль
    void print(void) {
        system("cls");
        Byhgalter->printOrders();
    }

    // Вывод одного заказа в консоль
    void printOne(const int ind) {
        system("cls");
        Byhgalter->printOneOrder(ind);
    }
    
    // во всех последующих функциях используется getline(),
    // так как удобно работать с тиипом string и может принимать строки с пробелом.
    
    // Создание нового заказа
    void newOrderMenu(void) {
        string c, name, phone;
        string mas[100][3];
        system("cls");
        cout << "Enter client's name: ";
        getline(cin >> ws, name);
        cout << "Enter phone number: ";
        getline(cin >> ws, phone);
        cout << "Enter number of items in the list: ";
        getline(cin >> ws, c);
        for (int i = 0; i < stoi(c); i++) {
            cout << "Product name: ";
            getline(cin >> ws, mas[i][0]);
            cout << "Cost: ";
            getline(cin >> ws, mas[i][2]);
            cout << "Volume: ";
            getline(cin >> ws, mas[i][1]);
        }
        Byhgalter->newOrder(name, phone, stoi(c), mas, 0, 0);

        cout << "Complete!\n";
        cout << "Enter 0 to continue: ";
        cin >> kg;
    }

    // Создание нового заказа
    void editOrderMenu(void) {
        string c, name, phone, ind;
        string mas[100][3];
        print();
        cout << "\nPlease choose the order to edit: ";
        getline(cin >> ws, ind);
        cout << "\nEnter new client's name: ";
        getline(cin >> ws, name);
        cout << "Enter new phone number: ";
        getline(cin >> ws, phone);
        cout << "Enter new number of items in the list: ";
        getline(cin >> ws, c);
        for (int i = 0; i < stoi(c); i++) {
            cout << "New product name: ";
            getline(cin >> ws, mas[i][0]);
            cout << "New cost: ";
            getline(cin >> ws, mas[i][2]);
            cout << "New volume: ";
            getline(cin >> ws, mas[i][1]);
        }
        Byhgalter->newOrder(name, phone, stoi(c), mas, 0, stoi(ind));

        cout << "Complete!\n";
        cout << "Enter 0 to continue: ";
        cin >> kg;
    }
    
    // Удаление заказа из базы
    void delOrderMenu(void) {
        string c;
        system("cls");
        cout << "Delete Order Menu\n\n";
        cout << "[0] Back\n";
        Byhgalter->printOrders();
        cout << "Please choose order: ";
        getline(cin >> ws, c);
        Byhgalter->delOrder(stoi(c)-1);
        system("cls");
        cout << "Complete!" << endl;
        cout << "Enter 0 to continue:";
        cin >> kg;
    }

    // Сохранение данных в файл "data.txt"
    void saveToFile(const string path) {
        ofstream fout;
        fout.open(path);

        // проверка открытия файла
        if (!fout.is_open()) {
            cout << "File opening error!" << endl;
        }
        else {
            Order** ord = Byhgalter->getOrders();
            fout << Byhgalter->getCount() << '\n'; // количество клиентов
            for (int i = 0; i < Byhgalter->getCount(); i++) {
                fout << ord[i]->getID() << '\n'; // номер заказа
                fout << ord[i]->getName() << '\n'; // имя клиента
                fout << ord[i]->getPhone() << '\n'; // номер телефона клиента
                fout << ord[i]->getCount() << '\n'; // количество пунктов в заказе
                Product** prod = ord[i]->getItems();
                for (int j = 0; j < ord[i]->getCount(); j++) {
                    fout << prod[j]->getName() << endl; // название товара
                    fout << prod[j]->getVolume() << endl; // количество товара в заказе
                    fout << prod[j]->getCost() << endl; // цена единицы товара
                }
            }
        }
        fout.close();
    }

    // Импорт из файла "data.txt"
    void takeFromFile(const string path, const bool start = false) {
        ifstream fin;
        string str, id, nm, ph, cnt;
        string mas[100][3];
        fin.open(path);

        //проверка открытия файла
        if (!fin.is_open()) {
            // исключает вывод ошибки в случае если
            // программа запущена впервые и файла (бызы данных) ещё нет в директории
            // по завершении работы он будет создан
            if (start == false) {
                cout << "File opening error!" << endl;
            }
        }
        else {
            getline(fin, str, '\n');
            int ordersCount = stoi(str);
            for (int i = 0; i < ordersCount; i++) {
                getline(fin, id, '\n');
                getline(fin, nm, '\n');
                getline(fin, ph, '\n');
                getline(fin, cnt, '\n');
                int itemsCount = stoi(cnt);
                for (int j = 0; j < itemsCount; j++) {
                    getline(fin, mas[j][0], '\n');
                    getline(fin, mas[j][1], '\n');
                    getline(fin, mas[j][2], '\n');
                }
                Byhgalter->newOrder(nm, ph, stoi(cnt), mas, stoi(id), 0);
            }
        }
        fin.close();
    }

public:
    void menu() {
        // загружаем данные из "базы"
        takeFromFile("base.txt", true);
        do {
            mainMenu();
            switch (choice1) {
            case 1:
                print();
                cout << "Enter 0 to continue:";
                cin >> kg;
                break;
            case 2:
                newOrderMenu();
                break;
            case 3:
                editOrderMenu();
                break;
            case 4:
                delOrderMenu();
                break;
            case 5:
                system("cls");
                cout << "All data wil be save to file \"data.txt\"" << endl;
                cout << "The old data will be lost, if you want to save it,\ntransfer it to another file." << endl;
                cout << "Enter 0 to continue:";
                cin >> kg;

                saveToFile("data.txt");

                system("cls");
                cout << "Complete!" << endl;
                cout << "Enter 0 to continue:";
                cin >> kg;
                break;
            case 6:
                system("cls");
                cout << "All data wil be import from file \"data.txt\"" << endl;
                cout << "Enter 0 to continue:";
                cin >> kg;

                takeFromFile("data.txt");

                system("cls");
                cout << "Complete!" << endl;
                cout << "Enter 0 to continue:";
                cin >> kg;
                break;
            case 0:
                saveToFile("base.txt");
                break;
            }
        } while (choice1 != 0);
    }
};

// Тело программы
int main()
{
    Goodctrl ctrl;
    ctrl.menu();

	return 0;
}