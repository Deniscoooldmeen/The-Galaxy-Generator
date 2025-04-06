#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>

using namespace std;

// Структура везды
struct Star {
    int x, y;
};

// Структура галактики
struct Galaxy {
    string name;
    int x, y; // Координаты галактики на карте
    vector<Star> stars;
};

vector<Galaxy> galaxies; // Вектор для хранения галактик
vector<vector<char>> galaxy_grid; // Двумерный массив карты галактик
int width = 20, height = 10, zoom = 1; // Размеры карты и уровень зума

// Генерация случайного имени галактики
string generate_galaxy_name() {
    string names[] = { "Andromeda", "Orion", "Pegasus", "Centauri", "Draco", "Phoenix", "Lyra", "Hercules", "Perseus" }; //Массив закготовленных имен
    return names[rand() % (sizeof(names) / sizeof(names[0]))] + "_"+to_string(rand() % 100);
}

// Функция генерации случайных галактик
void generate_galaxies(int num_galaxies) {
    galaxies.clear();
    srand(time(0));
    set<pair<int, int>> used_positions;
    for (int i = 0; i < num_galaxies; ++i) {
        Galaxy g;
        g.name = generate_galaxy_name();
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (used_positions.count({ x, y }));
        g.x = x;
        g.y = y;
        used_positions.insert({ x, y });

        int num_stars = rand() % 10 + 5;
        for (int j = 0; j < num_stars; ++j) {
            g.stars.push_back({ rand() % width, rand() % height });
        }
        galaxies.push_back(g);
    }
}

// Отрисовка карты галактик
void print_galaxy_map() {
    vector<vector<char>> galaxy_map(height, vector<char>(width, '.')); //'.' - мустое местов в "бесконечной" галактике
    for (const auto& galaxy : galaxies) {
        galaxy_map[galaxy.y][galaxy.x] = 'G'; // 'G' - символ галактики
    }
    for (const auto& row : galaxy_map) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << '\n';
    }
}

// Отображение списка галактик
void print_galaxies() {
    cout << "\nAvailable Galaxies:\n";
    for (size_t i = 0; i < galaxies.size(); ++i) {
        cout << i + 1 << ". " << galaxies[i].name << " (" << galaxies[i].stars.size() << " stars)\n";
    }
    cout << "\nSelect galaxy (1-" << galaxies.size() << ") or [q] Quit: ";
}

// Отображение звезд выбранной галактики
void print_stars(const Galaxy& galaxy) {
    vector<vector<char>> star_map(height * zoom, vector<char>(width * zoom, '.'));
    for (const auto& star : galaxy.stars) {
        star_map[star.y * zoom][star.x * zoom] = '*'; // '*' - символ для звезды
    }
    for (const auto& row : star_map) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << '\n';
    }
}

// Очистка экрана
void clear_screen() {
    system("cls");
}

// Увеличение масштаба
void zoom_in() {
    if (zoom < 4) 
        zoom *= 2;
}

// Уменьшение масштаба
void zoom_out() {
    if (zoom > 1) 
        zoom /= 2;
}

int main() {
    int num_galaxies = 5; // Количество галактик
    generate_galaxies(num_galaxies);

    char command;
    while (true) {
        clear_screen(); //чистим истоию вывода консоли
        print_galaxy_map();// Рисуем галактики
        print_galaxies();//Отображаем список галактик для выбора
        string input;
        cin >> input;
        if (input == "q") break;
        int choice = stoi(input); //stoi преобразует строку в целое число
        if (choice >= 1 && choice <= (int)galaxies.size()) {
            while (true) {
                clear_screen();
                cout << "Galaxy: " << galaxies[choice - 1].name << "\n";
                print_stars(galaxies[choice - 1]);
                cout << "\nCommands: [+] Zoom In  [-] Zoom Out  [c] Clear Screen  [b] Back\n";
                cin >> command;
                if (command == '+') zoom_in();
                else if (command == '-') zoom_out();
                else if (command == 'c') clear_screen();
                else if (command == 'b') break;
            }
        }
    }
    return 0;
}


//system("cls"); // Функция стирает пред выводы в консоли. (Для Linux/macOS, заменить на "clear")
// можно сделать в виде классов (один для галактики, один для звезды)
