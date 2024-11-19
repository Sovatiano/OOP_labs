#include "Department_Savostianov.h"
#include "BooleanFuncs.h"


void Department::addEmployee(bool is_manager) {
    if (is_manager) {
        shared_ptr<Manager> new_ptr{ make_shared<Manager>(Manager().CreateManager()) };
        employees.push_back(new_ptr);
    }
    else {
        shared_ptr<Employee> new_ptr{ make_shared<Employee>(Employee().CreateEmployee()) };
        employees.push_back(new_ptr);
    }
}


bool Department::removeEmployee() {
    string employeeID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Введите ID сотрудника: ";
        getline(cin, employeeID);
        if (isInteger(employeeID) && stoi(employeeID) > 0) {
            break;
        }
        else {
            cout << "Неверный ввод. Введите положительное целое число." << endl;
        }
    }

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getEmployeeID() == stoi(employeeID)) {
            employees.erase(it);
            cout << "Сотрудник успешно удалён" << endl;
            return true;
        }
    }
    cout << "Не удалось найти сотрудника с таким id" << endl;
    return false;
}


void Department::clearEmployees() {
    employees.clear();
}


void Department::saveToFile() {
    string file_name;
    cout << "Введите название файла для записи:";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    getline(cin, file_name);
    while (file_name == "")
    {
        cin.clear();
        cout << "Введите корректное имя: ";
        getline(cin, file_name);
    }
    ofstream fout(file_name, ios::out);
    if (fout.is_open()) {
        for (const auto& employee : employees) {
            employee->WriteToFile(fout);
        }
        fout.close();
    }
    else {
        cout << "Открыть файл не удалось." << endl;
    }
}


void Department::loadFromFile() {
    string file_name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    std::cout << "Укажите имя файла с данными: ";
    std::getline(std::cin, file_name);

    ifstream fin(file_name);
    while (!fin.is_open()) {
        std::cin.clear();
        std::cout << "Файл не найден, попробуйте ещё раз: ";
        std::getline(std::cin, file_name);
        ifstream fin(file_name);
    }

    if (fin.is_open()) {
        clearEmployees();


        while (fin.peek() != EOF) {
            try {
                /*boost::archive::text_iarchive ia(fin);*/
                //shared_ptr<Manager> new_ptr = Manager().ReadFromFile(ia);
                streampos current_pos = fin.tellg();
                shared_ptr<Employee> new_ptr = Employee().ReadFromFile(fin);
                if (new_ptr->getName() == "") {
                    fin.seekg(current_pos);
                    shared_ptr<Manager> mng_ptr = Manager().ReadFromFile(fin);
                    employees.push_back(mng_ptr);
                }
                

                if (new_ptr->getName() != "") {
                        employees.push_back(new_ptr);
                }
            }
            catch (boost::archive::archive_exception& ex) {
                break;
            }
        }

        fin.close();
    }
}


void Department::showEmployees() const {
    if (employees.size() == 0) {
        cout << "Список пуст." << endl;
    }

    else {
        for (const auto& employee : employees) {
            employee->ShowInfo();
        }
    }
}