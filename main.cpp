// Бейкал Михайло ТР-35
// Курсова робота "калькулятор калорій"
// 2024р.
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

// Структура для зберігання інформації про страву
struct Food {
    int calories;
    int protein;
    int fat;
    int carbs;
};

// Функція для додавання страви та інформації про неї у мапу
void addFood(map<string, Food>& foods) {
    string foodName;
    Food food;

    cout << "Введіть назву страви: ";
    cin.ignore();
    getline(cin, foodName);

    cout << "Введіть кількість калорій: ";
    cin >> food.calories;

    cout << "Введіть кількість білків: ";
    cin >> food.protein;

    cout << "Введіть кількість жирів: ";
    cin >> food.fat;

    cout << "Введіть кількість вуглеводів: ";
    cin >> food.carbs;

    foods[foodName] = food;

    cout << "Страву успішно додано!\n";
}

// Функція для видалення страви з мапи
void removeFood(map<string, Food>& foods) {
    string foodName;

    cout << "Введіть назву страви, яку потрібно видалити: ";
    cin.ignore();
    getline(cin, foodName);

    if (foods.erase(foodName) == 0) {
        cout << "Страву з такою назвою не знайдено.\n";
    }
    else {
        cout << "Страву успішно видалено!\n";
    }
}

// Функція для відображення інформації про всі страви
void displayFoods(const map<string, Food>& foods) {
    if (foods.empty()) {
        cout << "Немає даних про страви.\n";
    }
    else {
        cout << "Список страв та їх характеристики:\n";
        for (const auto& food : foods) {
            cout << "Назва: " << food.first << endl;
            cout << "- Калорії: " << food.second.calories << endl;
            cout << "- Білки: " << food.second.protein << endl;
            cout << "- Жири: " << food.second.fat << endl;
            cout << "- Вуглеводи: " << food.second.carbs << endl;
        }
    }
}

// Функція для редагування інформації про страву
void editFood(map<string, Food>& foods) {
    string foodName;
    cout << "Введіть назву страви, яку потрібно відредагувати: ";
    cin.ignore();
    getline(cin, foodName);

    auto it = foods.find(foodName);
    if (it != foods.end()) {
        cout << "Введіть нові дані для страви " << foodName << ":\n";
        Food& food = it->second;

        cout << "Кількість калорій: ";
        cin >> food.calories;

        cout << "Кількість білків: ";
        cin >> food.protein;

        cout << "Кількість жирів: ";
        cin >> food.fat;

        cout << "Кількість вуглеводів: ";
        cin >> food.carbs;

        cout << "Інформацію про страву " << foodName << " успішно оновлено!\n";
    }
    else {
        cout << "Страву з такою назвою не знайдено.\n";
    }
}

// Функція для збереження даних у файл
void saveToFile(const map<string, Food>& foods, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& food : foods) {
            file << food.first << " " << food.second.calories << " "
                << food.second.protein << " " << food.second.fat << " "
                << food.second.carbs << endl;
        }
        cout << "Дані успішно збережено у файл " << filename << "!\n";
    }
    else {
        cout << "Не вдалося відкрити файл для збереження.\n";
    }
}

// Функція для завантаження даних з файлу
void loadFromFile(map<string, Food>& foods, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        foods.clear();
        string foodName;
        Food food;
        while (file >> foodName >> food.calories >> food.protein >> food.fat >> food.carbs) {
            foods[foodName] = food;
        }
        cout << "Дані успішно завантажено з файлу " << filename << "!\n";
    }
    else {
        cout << "Не вдалося відкрити файл для завантаження.\n";
    }
}

// Функція для обчислення загальної кількості білків, жирів і вуглеводів
void calculateTotal(const map<string, Food>& foods) {
    int totalCalories = 0;
    int totalProtein = 0;
    int totalFat = 0;
    int totalCarbs = 0;

    for (const auto& food : foods) {
        totalCalories += food.second.calories;
        totalProtein += food.second.protein;
        totalFat += food.second.fat;
        totalCarbs += food.second.carbs;
    }
    cout << "ків: " << totalProtein << " г\n";
    cout << "Загальна кількість жирів: " << totalFat << " г\n";
    cout << "Загальна кількість вуглеводів: " << totalCarbs << " г\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    map<string, Food> foods;
    string filename = "foods.txt"; // Ім'я файлу, де будуть збережені дані

    char choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Додати страву\n";
        cout << "2. Видалити страву\n";
        cout << "3. Відобразити список страв\n";
        cout << "4. Редагувати страву\n";
        cout << "5. Зберегти дані у файл\n";
        cout << "6. Завантажити дані з файлу\n";
        cout << "7. Обчислити загальні показники\n";
        cout << "8. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case '1':
            addFood(foods);
            break;
        case '2':
            removeFood(foods);
            break;
        case '3':
            displayFoods(foods);
            break;
        case '4':
            editFood(foods);
            break;
        case '5':
            saveToFile(foods, filename);
            break;
        case '6':
            loadFromFile(foods, filename);
            break;
        case '7':
            calculateTotal(foods);
            break;
        case '8':
            cout << "Дякую за використання калькулятора калорій!\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != '8');

    return 0;
}