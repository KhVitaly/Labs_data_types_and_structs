#include <iostream>
#include <Windows.h>

using namespace std;

// Функция для создания матрицы с заданными размерами и возвращения указателя на нее
int **create_matrix(int, int);

// Функция для ввода значений матрицы
void input_matrix(int **, int, int);

// Функция для печати матрицы
void print_matrix(int **, int, int);

// Функция для освобождения памяти, выделенной под матрицу
void free_matrix(int **, int);

// Функция для умножения двух матриц
int **std_matrix_mul(int **, int **, int, int, int);

// Функция для заполнения матрицы случайными целыми числами
void fill_matrix_random(int **, int, int);

// Функция для умножения двух матриц по алгоритму Винограда
int **vinograd_matrix_mul(int **, int **, int, int, int);

// Функция для замера процессорного времени
double getCPUTime();

int main() {

    int **matrix_A, a_rows, a_cols; // Матрица matrix_A[a_rows * a_cols]
    int **matrix_B, b_rows, b_cols; // Матрица matrix_B[b_rows * b_cols]
    int **std_alg_matrix_C;         // Матрица полученная по стандартному алгоритму std_alg_matrix_C[a_rows * b_cols]
    int **vinograd_alg_matrix_C;    // Матрица полученная по алгоритму Винограда vinograd_alg_matrix_C[a_rows * b_cols]

    /*
    // Получаем размеры матриц
    cout << endl << "Input size matrix_A [a_rows * a_cols]: "; // Запрос у пользователя размеров матрицы A
    cin >> a_rows >> a_cols;
    cout << endl << "Input size matrix_B [b_rows * b_cols]: "; // Запрос у пользователя размеров матрицы B
    cin >> b_rows >> b_cols;

    if (a_cols != b_rows){
        cout << endl << "\t Matrix multiplication is not possible, a_cols != b_rows!" << endl << "\t The program is completed..." << endl;
        return 0;
    }
    */

    int choice;
    while (1) {
        cout << endl
             << "\t Choose an action:" << endl;
        cout << "\t1 - Enter size matrix:" << endl;      // ввод размеров матриц
        cout << "\t2 - Keyboard Input elements" << endl; // ручной ввод
        cout << "\t3 - Auto Input elements" << endl;     // автозаполнение
        cout << "\t0 - Exit" << endl;
        cout << endl
             << "Enter your choice -> ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            // Получаем размеры матриц
            cout << endl
                 << "Input size matrix_A [a_rows * a_cols]: "; // Запрос у пользователя размеров матрицы A
            cin >> a_rows >> a_cols;
            cout << endl
                 << "Input size matrix_B [b_rows * b_cols]: "; // Запрос у пользователя размеров матрицы B
            cin >> b_rows >> b_cols;

            // Проверяем, что перемножение матриц возможно
            if (a_cols != b_rows)
            {
                cout << endl
                     << "\t Matrix multiplication is not possible, a_cols != b_rows!" << endl
                     << "\t The program is completed..." << endl;
                return 0;
            }

            break;
        }

        case 2: {
            // Заполнение эл-тов матрицы вручную
            matrix_A = create_matrix(a_rows, a_cols); // Создание матрицы А с заданными размерами
            cout << endl
                 << "Input " << a_rows * a_cols << " elements matrix_A: ";
            input_matrix(matrix_A, a_rows, a_cols); // Вызов функции для ввода значений матрицы

            matrix_B = create_matrix(b_rows, b_cols); // Создание матрицы В с заданными размерами
            cout << endl
                 << "Input " << b_rows * b_cols << " elements matrix_B: ";
            input_matrix(matrix_B, b_rows, b_cols); // Вызов функции для ввода значений матрицы

            // Вызов функций для печати матриц
            cout << endl
                 << "matrix_A:" << endl;
            print_matrix(matrix_A, a_rows, a_cols);
            cout << endl
                 << "matrix_B:" << endl;
            print_matrix(matrix_B, b_rows, b_cols);

            // Стандартный алгоритм перемножения матриц
            cout << endl
                 << "\t Standard matrix multiplication algorithm (std_alg_matrix_C = matrix_A * matrix_B):" << endl;
            std_alg_matrix_C = std_matrix_mul(matrix_A, matrix_B, a_rows, a_cols, b_cols);
            cout << endl
                 << "std_alg_matrix_C:" << endl;
            print_matrix(std_alg_matrix_C, a_rows, b_cols);

            // Алгоритм Винограда
            cout << endl
                 << "\t Vinograd matrix multiplication algorithm (vinograd_alg_matrix_C = matrix_A * matrix_B):" << endl;
            vinograd_alg_matrix_C = vinograd_matrix_mul(matrix_A, matrix_B, a_rows, a_cols, b_cols);
            cout << endl
                 << "vinograd_alg_matrix_C:" << endl;
            print_matrix(vinograd_alg_matrix_C, a_rows, b_cols); // для больших матриц печать очень долгая, лучше убрать)

            break;
        }

        case 3: {
            // Создание матриц А и В с заданными размерами
            matrix_A = create_matrix(a_rows, a_cols);
            matrix_B = create_matrix(b_rows, b_cols);

            // Заполнение матриц случайными целыми числами
            fill_matrix_random(matrix_A, a_rows, a_cols);
            fill_matrix_random(matrix_B, b_rows, b_cols);

            // для больших матриц печать очень долгая, лучше убрать)
            /*
            // Вызов функций для печати матриц
            cout << endl << "matrix_A:" << endl;
            print_matrix(matrix_A, a_rows, a_cols);
            cout << endl << "matrix_B:" << endl;
            print_matrix(matrix_B, b_rows, b_cols);
            */

            // Стандартный алгоритм перемножения матриц
            cout << endl
                 << "\t Standard matrix multiplication algorithm (std_alg_matrix_C = matrix_A * matrix_B):" << endl;
            double startTime_std_alg = getCPUTime();
            std_alg_matrix_C = std_matrix_mul(matrix_A, matrix_B, a_rows, a_cols, b_cols);
            double endTime_std_alg = getCPUTime();
            // cout << endl << "std_alg_matrix_C:" << endl;
            // print_matrix(std_alg_matrix_C, a_rows, b_cols); // для больших матриц печать очень долгая, лучше убрать)
            double CPU_time_std_alg_matrix = endTime_std_alg - startTime_std_alg;
            cout << endl
                 << "startTime = " << startTime_std_alg << "\t"
                 << "endTime = " << endTime_std_alg << endl;
            cout << "CPU time(std_alg_matrix) = " << endTime_std_alg - startTime_std_alg << " sec" << endl;

            // Алгоритм Винограда
            cout << endl
                 << "\t Vinograd matrix multiplication algorithm (vinograd_alg_matrix_C = matrix_A * matrix_B):" << endl;
            double startTime_vinograd_alg = getCPUTime();
            vinograd_alg_matrix_C = vinograd_matrix_mul(matrix_A, matrix_B, a_rows, a_cols, b_cols);
            double endTime_vinograd_alg = getCPUTime();
            // cout << endl << "vinograd_alg_matrix_C:" << endl;
            // print_matrix(vinograd_alg_matrix_C, a_rows, b_cols); // для больших матриц печать очень долгая, лучше убрать)
            double CPU_time_vinograd_alg_matrix = endTime_vinograd_alg - startTime_vinograd_alg;
            cout << endl
                 << "startTime = " << startTime_vinograd_alg << "\t"
                 << "endTime = " << endTime_vinograd_alg << endl;
            cout << "CPU time(vinograd_alg_matrix) = " << endTime_vinograd_alg - startTime_vinograd_alg << " sec" << endl;

            // Вывод процессорного времени двух алгоритмов
            cout << endl
                 << "\t Result CPU time for 2 algorithms:" << endl;
            cout << (a_cols % 2 == 0 ? "N(a_cols = b_rows) is EVEN!" : "N(a_cols = b_rows) is ODD!") << endl; // выводим четное или нечетное N
            cout << "CPU time(std_alg_matrix) = " << CPU_time_std_alg_matrix << " sec" << endl;
            cout << "CPU time(vinograd_alg_matrix) = " << CPU_time_vinograd_alg_matrix << " sec" << endl;

            break;
        }

        case 0: {
            cout << endl
                 << "\tExiting the program..." << endl;
            return 0;
        }

        default:
            cout << endl
                 << "Invalid choice! Try again!" << endl;
        }
    }

    // Освобождение памяти
    free_matrix(matrix_A, a_rows);
    free_matrix(matrix_B, b_rows);
    free_matrix(std_alg_matrix_C, a_rows);
    free_matrix(vinograd_alg_matrix_C, a_rows);

    return 0;
}

// Функция для создания матрицы с заданными размерами и возвращения указателя на нее
int **create_matrix (int rows, int cols) {
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new int[cols];

    return matrix;
}

// Функция для ввода значений матрицы(ввод пользователя)
void input_matrix (int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
}

// Функция для печати матрицы
void print_matrix (int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Функция для освобождения памяти, выделенной под матрицу
void free_matrix (int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

// Функция для умножения двух матриц (Стандартный алгоритм умножения 2-х матриц)
int **std_matrix_mul(int **matrix_A, int **matrix_B, int a_rows, int a_cols, int b_cols) {
    // Создаем результирующую матрицу C размером a_rows x b_cols
    int **C = new int *[a_rows];
    for (int i = 0; i < a_rows; i++) {
        C[i] = new int[b_cols]();
    }

    // Перемножаем матрицы A и B
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            C[i][j] = 0; // начальное значение эл-та
            for (int k = 0; k < a_cols; k++) {
                C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }

    return C;
}

// Функция для заполнения матрицы случайными целыми числами
void fill_matrix_random(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // matrix[i][j] = rand() % 100; // случайное число от 0 до 99
            matrix[i][j] = rand() % 21 - 10; // случайное число от -10 до 10
            // matrix[i][j] = rand() % 11 - 5; // случайное число от -5 до 5
        }
    }
}

// Функция для умножения двух матриц по алгоритму Винограда
int **vinograd_matrix_mul(int **matrix_A, int **matrix_B, int a_rows, int a_cols, int b_cols) {
    // Создаем результирующую матрицу C размером a_rows x b_cols
    int **C = new int *[a_rows];
    for (int i = 0; i < a_rows; i++)
        C[i] = new int[b_cols]();

    // Предварительные вычисления для алгоритма Винограда
    int *row_factor = new int[a_rows]();
    int *col_factor = new int[b_cols]();

    // Вычисляем для каждой строки матрицы A значение row_factor[i], которое представляет собой сумму произведений пар элементов этой строки.
    // Для каждой строки матрицы А, вычисляем сумму произведений пар эл-тов соотв. столбцов матрицы В
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < a_cols / 2; j++) {
            row_factor[i] += matrix_A[i][2 * j] * matrix_A[i][2 * j + 1];
        }
    }

    // Вычисляем для каждого столбца матрицы B значение col_factor[j], которое представляет собой сумму произведений пар элементов этого столбца.
    // Для каждого столбца матрицы В, вычисляем сумму произведений пар эл-тов соотв. строк матрицы А
    for (int i = 0; i < b_cols; i++) {
        for (int j = 0; j < a_cols / 2; j++) {
            col_factor[i] += matrix_B[2 * j][i] * matrix_B[2 * j + 1][i];
        }
    }

    // Вычисление произведения по алгоритму Винограда
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            C[i][j] = -row_factor[i] - col_factor[j]; // Инициализация суммы суммой предварительных вычислений
            for (int k = 0; k < a_cols / 2; k++) {
                C[i][j] += (matrix_A[i][2 * k] + matrix_B[2 * k + 1][j]) * (matrix_A[i][2 * k + 1] + matrix_B[2 * k][j]);
            }
        }
    }

    // Если размер N(a_cols = b_rows) нечетный, добавляем к результату произведения дополнительное произведение последних элементов соответствующих строк и столбцов.
    if (a_cols % 2 == 1) {
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < b_cols; j++) {
                C[i][j] += matrix_A[i][a_cols - 1] * matrix_B[a_cols - 1][j];
            }
        }
    }

    delete[] row_factor;
    delete[] col_factor;

    return C;
}

double getCPUTime () {
    /*  Статья, где увидел данный способ: https://habr.com/ru/articles/282301/
        Официальная документация, функция GetProcessTimes: https://learn.microsoft.com/ru-ru/windows/win32/api/processthreadsapi/nf-processthreadsapi-getprocesstimes?redirectedfrom=MSDN#return-value
        Официальная документация, структура FILETIME: https://learn.microsoft.com/ru-ru/windows/win32/api/minwinbase/ns-minwinbase-filetime
    */
    FILETIME createTime; // Указатель на структуру FILETIME , которая получает время создания процесса.
    FILETIME exitTime; // Указатель на структуру FILETIME , которая получает время выхода процесса.
    FILETIME kernelTime; // Указатель на структуру FILETIME , получающую количество времени, которое процесс выполнял в режиме ядра.
    FILETIME userTime; // Указатель на структуру FILETIME , получающую время выполнения процесса в пользовательском режиме.

    if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != -1) {
        SYSTEMTIME userSystemTime;
        if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
            return (double)userSystemTime.wHour * 3600.0 +
                   (double)userSystemTime.wMinute * 60.0 +
                   (double)userSystemTime.wSecond +
                   (double)userSystemTime.wMilliseconds / 1000.0;
    }

    //ULARGE_INTEGER li = {{userTime.dwLowDateTime, userTime.dwHighDateTime }};
    //    return (li.QuadPart % 864000000000) / 10000000.;
    // Надо делить на 10000000, потому что измеряется в 100-наносекундных интервалах, а получить нужно секунды.
}