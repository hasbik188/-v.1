#include <fstream>
#include <iostream>
#include <string>

//Для хранения данных о планшетных сканерах описать структуру вида, описанного в варианте 1.
//Написать функцию, которая записывает в бинарный файл данные о сканере из приведенной структуры.
//Структура файла: в первых 4 байтах размещается значение типа int, определяющее количество сделанных в файл записей; далее без пропусков размещаются записи о сканерах.
//Написать функцию, которая вводит данные о сканере с клавиатуры в структуру типа scan_info и помещает ее содержимое на место первой записи в файле.
//Файл должен существовать. При этом запись, ранее занимавшая первую позицию, помещается на вторую и т. д.

using namespace std;

struct scan_info
{
    string model; // наименование модели
    int price; // цена
    double x_size; // горизонтальный размер области сканирования
    double y_size; // вертикальный размер области сканирования
    int optr; // оптическое разрешение
    int grey; // число градаций серого
};

void write_file(const char* file_name, const int n);

int main() {
    // setlocale(LC_CTYPE, "Russian_Russia.1251");
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);
    cout << "Введите имя файла для записи:";
    char file_name[15];
    cin >> file_name;
    cout << "Введите число записей:";
    int n;
    cin >> n;
    cin.ignore(1);
    write_file(file_name, n);
    return 0;
}
void write_file(const char* file_name, const int n) {
    scan_info* scans = new scan_info[n];
    ofstream fout(file_name, ios::out | ios::binary);
    if (fout.fail()) {
        cerr << "Ошибка открытия выходного файла";
        exit(1);
    }
    fout.write((char*)&n, 2);
    /*Ввод структуры*/
    for (int i = 0; i < n; i++) {
        cout << "Запись №" << i + 1;
        cout << "Введите модель:";
        cin >> scans[i].model;
        fout.write((char*)& scans[i].model, sizeof scans[i].model);
        cout << "Введите цену:";
        cin >> scans[i].price;
        cout << "Введите горизонтальный размер области сканирования:";
        cin >> scans[i].x_size;
        cout << "Введите вертикальный размер области сканирования:";
        cin >> scans[i].y_size;
        cout << "Введите оптическое разрешение:";
        cin >> scans[i].optr;
        cout << "Введите число градаций серого:";
        cin >> scans[i].grey;
        cin.ignore(1);
    }
    for (int i = n - 1; i; i--){
        fout.write((char*)& scans[i].model, sizeof scans[i].model);
        fout.write((char*) & scans[i].price, 5);
        fout.write((char*) & scans[i].x_size, 5);
        fout.write((char*) & scans[i].y_size, 5);
        fout.write((char*) & scans[i].optr, 5);
        fout.write((char*) & scans[i].grey, 5);
    }
    fout.close();
}