#include "AVL.h"
#include "HashTable.h"
void insert_in_del(std::vector<int> del,int k)
{
    auto insertPosition = std::lower_bound(del.begin(), del.end(), k);
    del.insert(insertPosition, k);
}
int main() {
    std::vector<Person*> client = ReadFromFile("Clients.txt");
    std::vector<int> del;
    BST<DB> DB_Tree;
    BST<FIO> FIO_Tree;
    BST<Adress> AD_Tree;

    HashTable HT(10);

    for (const auto& person : client) {
        if (person != nullptr) {
            DB_Tree.insert(person->getDB());
            FIO_Tree.insert(person->getFIO());
            AD_Tree.insert(person->getADRESS());
            HT.add(*person);
        }
    }

    DB_Tree.printSideways();
    FIO_Tree.printSideways();
    AD_Tree.printSideways();
    HT.print();

    int n;
    std::cout << "Что вы хотите удалить?" << std::endl;
    std::cout << "[1] Номер Телефона" << std::endl;
    std::cout << "[2] Дата Рождения" << std::endl;
    std::cout << "[3] ФИО" << std::endl;
    std::cout << "[4] Адрес" << std::endl;
    std::cin >> n;
        if (n == 1){
            int phoneNumber;
            std::cout << "Введите номер" << std::endl;
            std::cin >> phoneNumber;

//            for (auto& person : client) {
//                if (person != nullptr && person->getNUM().number == phoneNumber) {
//                    HT.remove(*person);
//                    AD_Tree.remove(person->getADRESS());
//                    FIO_Tree.remove(person->getFIO());
//                    DB_Tree.remove(person->getDB());
//                    delete person;
//                    person = nullptr;
//                    break;
//                }
//            }
            for (int i = 0; i < client.size(); i++) {
                if (client[i] != nullptr && client[i]->getNUM().number == phoneNumber) {
                    insert_in_del(del,i);
                    // Удаление элементов
                    HT.remove(*client[i]);
                    AD_Tree.remove(client[i]->getADRESS());
                    FIO_Tree.remove(client[i]->getFIO());
                    DB_Tree.remove(client[i]->getDB());
                    delete client[i];
                    client[i] = nullptr;
                    // Используйте переменную "i" как индекс удаляемого элемента
                    break;
                }
            }

        }
        if (n == 2){
            // Удаление элемента из вектора с использованием пользовательского ввода
            if (!client.empty()) {
                std::cout << "Напишите дату рождения (формат: DD MM YYYY): ";
                int day,month,year;
                std::cin >> day >> month >> year;
                DB Date(day,month,year);
                // Поиск всех элементов с указанной датой рождения
                std::vector<Person*> matchingPersons;
                for (const auto& person : client) {
                    if (person != nullptr &&  person->getDB().operator==(Date)) {
                        matchingPersons.push_back(person);
                    }
                }

                // Вывод найденных элементов
                std::cout << "Все клиенты с даннной датой рождения:\n";
                for (std::size_t i = 0; i < matchingPersons.size(); ++i) {
                    std::cout << i + 1 << ". " << *matchingPersons[i] << "\n";
                }

                // Запрос пользователя на удаление элемента
                if (!matchingPersons.empty()) {
                    std::cout << "Выберите кого удалить: ";
                    int deleteIndex;
                    std::cin >> deleteIndex;

                    if (deleteIndex >= 1 && deleteIndex <= static_cast<int>(matchingPersons.size())) {
                        int clientIndex = std::distance(client.begin(), std::find(client.begin(), client.end(), matchingPersons[deleteIndex - 1]));
                        insert_in_del(del,clientIndex);
                        HT.remove(*client[clientIndex]);
                        AD_Tree.remove(client[clientIndex]->getADRESS());
                        FIO_Tree.remove(client[clientIndex]->getFIO());
                        DB_Tree.remove(client[clientIndex]->getDB());

                        delete client[clientIndex];
                        client[clientIndex] = nullptr;
                    }
                    else {
                        std::cout << "Неправильный воод.\n";
                    }
                }
                else {
                    std::cout << "Ненайдено людей с такой датой рождения.\n";
                }
            }
        }
        if (n == 3){
            // Удаление элемента из вектора с использованием пользовательского ввода
            if (!client.empty()) {
                std::cout << "Напишите ФИО: ";
                std::string f,i,o;
                std::cin >> f >> i >> o;
                FIO fio(f,i,o);
                // Поиск всех элементов с указанной датой рождения
                std::vector<Person*> matchingPersons;
                for (const auto& person : client) {
                    if (person != nullptr &&  person->getFIO().operator==(fio)) {
                        matchingPersons.push_back(person);
                    }
                }

                // Вывод найденных элементов
                std::cout << "Все клиенты с данным ФИО:\n";
                for (std::size_t i = 0; i < matchingPersons.size(); ++i) {
                    std::cout << i + 1 << ". " << *matchingPersons[i] << "\n";
                }

                // Запрос пользователя на удаление элемента
                if (!matchingPersons.empty()) {
                    std::cout << "Выберите кого удалить: ";
                    int deleteIndex;
                    std::cin >> deleteIndex;

                    if (deleteIndex >= 1 && deleteIndex <= static_cast<int>(matchingPersons.size())) {
                        int clientIndex = std::distance(client.begin(), std::find(client.begin(), client.end(), matchingPersons[deleteIndex - 1]));
                        insert_in_del(del,clientIndex);
                        HT.remove(*client[clientIndex]);
                        AD_Tree.remove(client[clientIndex]->getADRESS());
                        FIO_Tree.remove(client[clientIndex]->getFIO());
                        DB_Tree.remove(client[clientIndex]->getDB());

                        delete client[clientIndex];
                        client[clientIndex] = nullptr;
                    }
                    else {
                        std::cout << "Неправильный воод.\n";
                    }
                }
                else {
                    std::cout << "Ненайдено людей с таким ФИО.\n";
                }
            }
        }
        if (n == 4){
            // Удаление элемента из вектора с использованием пользовательского ввода
            if (!client.empty()) {
                std::cout << "Напишите Адрес: ";
                std::string ad;
                std::cin.ignore(); // Игнорируем символ новой строки после предыдущего ввода
                std::getline(std::cin, ad);
                Adress adress(ad);
                // Поиск всех элементов с указанной датой рождения
                std::vector<Person*> matchingPersons;
                for (const auto& person : client) {
                    if (person != nullptr &&  person->getADRESS().operator==(adress)) {
                        matchingPersons.push_back(person);
                    }
                }

                // Вывод найденных элементов
                std::cout << "Все клиенты с данным Адресом:\n";
                for (std::size_t i = 0; i < matchingPersons.size(); ++i) {
                    std::cout << i + 1 << ". " << *matchingPersons[i] << "\n";
                }

                // Запрос пользователя на удаление элемента
                if (!matchingPersons.empty()) {
                    std::cout << "Выберите кого удалить: ";
                    int deleteIndex;
                    std::cin >> deleteIndex;

                    if (deleteIndex >= 1 && deleteIndex <= static_cast<int>(matchingPersons.size())) {
                        int clientIndex = std::distance(client.begin(), std::find(client.begin(), client.end(), matchingPersons[deleteIndex - 1]));
                        insert_in_del(del,clientIndex);
                        HT.remove(*client[clientIndex]);
                        AD_Tree.remove(client[clientIndex]->getADRESS());
                        FIO_Tree.remove(client[clientIndex]->getFIO());
                        DB_Tree.remove(client[clientIndex]->getDB());

                        delete client[clientIndex];
                        client[clientIndex] = nullptr;
                    }
                    else {
                        std::cout << "Неправильный воод.\n";
                    }
                }
                else {
                    std::cout << "Ненайдено людей с таким адресом.\n";
                }
            }
        }


    DB_Tree.printSideways();
    FIO_Tree.printSideways();
    AD_Tree.printSideways();
    HT.print();


    int phone;
    std::string surname, name, f_name;
    int day, month, year;
    std::string address;
    std::cout << "Для добавления введите новый элемент" << std::endl;
    std::cout << "Номер телефона: " << std::endl;
    std ::cin >> phone;
    std::cout << "ФИО: "<< std::endl;
    std ::cin >> surname >> name >> f_name;
    std::cout << "Дата рождения [День]: "<< std::endl;
    std ::cin >> day;
    std::cout << "Дата рождения [Месяц]: "<< std::endl;
    std:: cin >> month;
    std::cout << "Дата рождения [Год]: "<< std::endl;
    std:: cin >> year;
    std::cout << "Адрес: " << std::endl;
    std::getline(std::cin >> std::ws, address);
    auto g = new Person(phone, surname, name, f_name, day, month, year, address);

    bool added = false;
    if (!del.empty()) {
            client.assign(del[0], g);
            del.erase(del.cbegin());
            AD_Tree.insert(g->getADRESS());
            FIO_Tree.insert(g->getFIO());
            DB_Tree.insert(g->getDB());
            HT.add(*g);
            added = true;
    }


    if (del.empty()) {
        client.push_back(g);
        AD_Tree.insert(g->getADRESS());
        FIO_Tree.insert(g->getFIO());
        DB_Tree.insert(g->getDB());
        HT.add(*g);
    }



    DB_Tree.printSideways();
    FIO_Tree.printSideways();
    AD_Tree.printSideways();
    HT.print();

    return 0;
}