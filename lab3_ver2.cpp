#include <iostream>
#include <Windows.h>
#include <random>

using namespace std;

typedef struct 
{
    int **matrix;
    int rows;
    int cols;
    string chainOperations;

} levenshteinData;


int cycle_Levinshtein_distance(string word1, int len1, string word2, int len2);

int recurrent_Levinshtein_distance(string word1, int len1, string word2, int len2, int **Matrix);

int recurrent_w_cache_Levinshtein_distance(string word1, int len1, string word2, int len2);

int distance_Damerau_Levinshtein(string word1, int len1, string word2, int len2);

int chooseOp(string word1, int len1, string word2, int len2, int **Matrix);

int minimum(int a, int b, int c);

// создание матрицы
int **createMatrix(int rows, int cols);

// удаление матрицы
void deleteMatrix(int **matrix, int rows);

double getCPUTime();

string getRandomString(int size);

levenshteinData createLevenshteinMatrix(string str1, int len1, string str2, int len2);

string getChainOperations(levenshteinData m);

void printMatrix(levenshteinData m);

int main()
{
    string word_1{}, word_2{};

    cout << "Input word_1 -> ";
    cin >> word_1;
    cout << "Input word_2 -> ";
    cin >> word_2;

    int len_1 = word_1.length();
    int len_2 = word_2.length();

    int choice{};
    while (1)
    {
        cout << endl << "Choose an action:" << endl;
        //cout << "\t1 - Enter two words" << endl;
        cout << "\t1 - Show Results of Levinstein distance with 4 different algorithms" << endl;
        cout << "\t2 - Show CPU_time of Levinstein distance with 4 different algorithms" << endl;
        cout << "\t3 - Show Levenshtein Matrix" << endl;
        cout << "\t0 - Exit" << endl;       
        cout << endl << "Enter your choice -> ";
        cin >> choice;
        cout << endl;

        switch(choice)
        {
            case 1:
            {
                cout << "\t cycle_Levinshtein_distance = " << cycle_Levinshtein_distance(word_1, len_1, word_2, len_2) << endl;
                cout << "\t recurrent_Levinshtein_distance = " << recurrent_Levinshtein_distance(word_1, len_1, word_2, len_2, NULL) << endl;
                cout << "\t recurrent_w_cache_Levinshtein_distance = " << recurrent_w_cache_Levinshtein_distance(word_1, len_1,  word_2, len_2) << endl;
                cout << "\t distance_Damerau_Levinshtein = " << distance_Damerau_Levinshtein(word_1, len_1,  word_2, len_2) << endl;

                break;
            }

            case 2:
            {
                // Последовательно получаем рандомные строки размером i
                for (int size = 4; size <= 10; size += 2) 
                {
                    double CPU_time_cycle_Levinshtein_distance{}, CPU_time_recurrent_Levinshtein_distance{},
                    CPU_time_recurrent_w_cache_Levinshtein_distance{}, CPU_time_distance_Damerau_Levinshtein{};

                    string str_1 = getRandomString(size);
                    string str_2 = getRandomString(size);
                    
                    cout << str_1 << endl;
                    cout << str_2 << endl;

                    double CPU_time{};

                   
                        // CPU_time_cycle_Levinshtein_distance
                        CPU_time = getCPUTime();

                        // Во вложенном цикле 10 раз сравниваем строки по каждому алгоритму
                         for (int j = 0; j < 10; j++) 
                        {
                            cycle_Levinshtein_distance(str_1, size, str_2, size);
                        }
                        CPU_time = getCPUTime() - CPU_time;

                        CPU_time_cycle_Levinshtein_distance += fabs(((double) CPU_time));

                        // CPU_time_recurrent_Levinshtein_distance
                        CPU_time = getCPUTime();
                        for (int j = 0; j < 10; j++) 
                        {
                            recurrent_Levinshtein_distance(str_1, size, str_2, size, NULL);
                        }
                        CPU_time = getCPUTime() - CPU_time;

                        CPU_time_recurrent_Levinshtein_distance += fabs(((double) CPU_time));

                        // CPU_time_recurrent_w_cache_Levinshtein_distance
                        CPU_time = getCPUTime();
                        for (int j = 0; j < 10; j++) 
                        {
                            recurrent_w_cache_Levinshtein_distance(str_1, size, str_2, size);
                        }
                        CPU_time = getCPUTime() - CPU_time;

                        CPU_time_recurrent_w_cache_Levinshtein_distance += fabs(((double) CPU_time));

                        // CPU_time_distance_Damerau_Levinshtein
                        CPU_time = getCPUTime();
                        for (int j = 0; j < 10; j++) 
                        {
                            distance_Damerau_Levinshtein(str_1, size, str_2, size);
                        }
                        CPU_time = getCPUTime() - CPU_time;

                        CPU_time_distance_Damerau_Levinshtein += fabs(((double) CPU_time));
                    }

                // => чтобы получить наносекунды, нужно разделить на 1 000 000 000.
                // Чтобы получить среднее арифметическое, нужно разделить на 10.
                //double convertNano =  10000000000; // 1 000 000 000 / 10
                /*
                cout << "\tStrings length = " << size << "\t CPU_time(cycle_Levinshtein_distance) = " << CPU_time_cycle_Levinshtein_distance / convertNano << " ns" << endl;
                cout << "\tStrings length = " << size << "\t CPU_time(recurrent_Levinshtein_distance) = " << CPU_time_recurrent_Levinshtein_distance / convertNano << " ns" << endl;
                cout << "\tStrings length = " << size << "\t CPU_time(recurrent_w_cache_Levinshtein_distance) = " << CPU_time_recurrent_w_cache_Levinshtein_distance / convertNano << " ns" << endl;
                cout << "\tStrings length = " << size << "\t CPU_time(distance_Damerau_Levinshtein) = " << CPU_time_distance_Damerau_Levinshtein / convertNano << " ns" << endl;
                */
                //}

                break;
            }

            case 3:
            {
                // вывод цепочки операций
                cout << "\tChain operations Levenshtein algorythm:" << endl;
                cout << getChainOperations(createLevenshteinMatrix(word_1, len_1, word_2, len_2)) << endl;

                // вывод матрицы Левинштейна
                printMatrix(createLevenshteinMatrix(word_1, len_1, word_2, len_2));

                break;
            }

            case 0:
            {
                cout << endl
                    << "\tExiting the program..." << endl;

                return 0;
            }

            default:
                cout << endl
                    << "Invalid choice! Try again!" << endl;
        }
    }
}

int cycle_Levinshtein_distance (string word1, int len1, string word2, int len2)
{
    int deleteOp = 1;
    int insertOp = 1;
    int replaceOp{};

    //int len1 = word1.length();
    //int len2 = word2.length();

    int **Matrix = createMatrix(len1 + 1, len2 + 1);

    for (int i = 0; i <= len1; i++)
        Matrix[i][0] = i;

    for (int j = 0; j <= len2; j++)
        Matrix[0][j] = j;

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (word1[i - 1] == word2[j - 1])
                replaceOp = 0;
            else
                replaceOp = 1;

            Matrix[i][j] = minimum(Matrix[i - 1][j] + deleteOp,       // D - удаление
                                   Matrix[i][j - 1] + insertOp,       // I - вставка
                                   Matrix[i - 1][j - 1] + replaceOp); // R - замена
        }
    }

    // сохраняем результат
    int result = Matrix[len1][len2];

    // освобождаем память
    deleteMatrix(Matrix, len1);

    return result;
}

int recurrent_Levinshtein_distance(string word1, int len1, string word2, int len2, int **Matrix)
{
    // проверяем кэш
    if (Matrix == NULL || Matrix[len1][len2] == -1)
    {
        // если не найдено, рассчитываем
        if (len1 == 0) 
            return len2;

        if (len2 == 0)
            return len1;

        // если не вычислено, то вычисляем рекурсивно
        if (Matrix != NULL)
        {
            Matrix[len1][len2] = chooseOp(word1, len1, word2, len2, Matrix); // рассчитываем и сохр. в кэш
            return Matrix[len1][len2];
        }
        else
            return chooseOp(word1, len1, word2, len2, Matrix); // 
    }
    else
        return Matrix[len1][len2];
}


int recurrent_w_cache_Levinshtein_distance (string word1, int len1, string word2, int len2)
{
    int **Matrix = createMatrix(len1 + 1, len2 + 1); // массив для кэширвоания

    if (len1 == 0) {
        return len2;
    }

    if (len2 == 0) {
        return len1;
    }

    return chooseOp(word1, len1, word2, len2, Matrix); 
}


int distance_Damerau_Levinshtein (string word1, int len1, string word2, int len2)
{
    int deleteOp = 1;
    int insertOp = 1;
    int replaceOp{};

    int **Matrix = createMatrix(len1 + 1, len2 + 1); // Создание массива для хранения промежуточных значений

    for (int i = 0; i <= len1; i++)
        Matrix[i][0] = i;

    for (int j = 0; j <= len2; j++)
        Matrix[0][j] = j;

    // Вычисление расстояния Дамерау-Левенштейна для всех символов
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (word1[i - 1] == word2[j - 1])
                replaceOp = 0;
            else
                replaceOp = 1;

            Matrix[i][j] = minimum(Matrix[i - 1][j] + deleteOp,       // D - удаление
                                   Matrix[i][j - 1] + insertOp,       // I - вставка
                                   Matrix[i - 1][j - 1] + replaceOp); // R - замена

            if (i > 1 && j > 1 && word1[i - 1] == word2[j - 2] && word1[i - 2] == word2[j - 1])
            {
                Matrix[i][j] = min(Matrix[i][j], Matrix[i - 2][j - 2] + 1); // перестановка
            }
        }
    }

    // сохраняем результат
    int result = Matrix[len1][len2];

    // освобождаем память
    deleteMatrix(Matrix, len1);

    return result;
}

int chooseOp(string word1, int len1, string word2, int len2, int **Matrix)
{
    int replaceOp{};

    if (word1[len1 - 1] == word2[len2 - 1])
        replaceOp = 0;
    else
        replaceOp = 1;

    int deletion = recurrent_Levinshtein_distance(word1.substr(0, len1 - 1), len1 - 1, word2, len2,
                                                  Matrix) + 1;

    int insertion = recurrent_Levinshtein_distance(word1, len1, word2.substr(0, len2 - 1), len2 - 1,
                                                 Matrix) + 1;

    int replace = recurrent_Levinshtein_distance(word1.substr(0, len1 - 1), len1 - 1,
                                                 word2.substr(0, len2 - 1), len2 - 1,
                                                 Matrix) + replaceOp;

    return minimum(deletion, insertion, replace);
}


int minimum(int a, int b, int c)
{
    if (a > b)
        a = b;

    if (a > c)
        a = c;

    return a;
}


// создание матрицы
int **createMatrix (int rows, int cols)
{
    int **Matrix = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        Matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            Matrix[i][j] = -1;
        }
    }

    return Matrix;
}

// удаление матрицы
void deleteMatrix (int **matrix, int rows)
{
    for (int i = 0; i <= rows; i++)
        delete[] matrix[i];

    delete[] matrix;
}


double getCPUTime () 
{
    /*  Статья, где увидел данный способ: https://habr.com/ru/articles/282301/
        Официальная документация, функция GetProcessTimes: https://learn.microsoft.com/ru-ru/windows/win32/api/processthreadsapi/nf-processthreadsapi-getprocesstimes?redirectedfrom=MSDN#return-value
        Официальная документация, структура FILETIME: https://learn.microsoft.com/ru-ru/windows/win32/api/minwinbase/ns-minwinbase-filetime
    */
    FILETIME createTime; // Указатель на структуру FILETIME , которая получает время создания процесса.
    FILETIME exitTime; // Указатель на структуру FILETIME , которая получает время выхода процесса.
    FILETIME kernelTime; // Указатель на структуру FILETIME , получающую количество времени, которое процесс выполнял в режиме ядра.
    FILETIME userTime; // Указатель на структуру FILETIME , получающую время выполнения процесса в пользовательском режиме.

    if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != -1) 
    {
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


string getRandomString(int size) 
{
    string str;

    for (int i = 0; i < size; i++) 
        str += rand() % 26 + 'a';

    return str;
}



// Создаёт матрицу с результатами расчёта расстояния Левенштейна
levenshteinData createLevenshteinMatrix(string str1, int len1, string str2, int len2) 
{
    if (len1 > len2) {
        return createLevenshteinMatrix(str1, len1, str2, len2);
    }

    int **matrix = new int *[len2 + 1];
    matrix[0] = new int[len1 + 1];

    for (int i = 0; i <= len1; i++) 
    {
        matrix[0][i] = i;
    }

    for (int i = 1; i <= len2; i++) 
    {
        matrix[i] = new int[len1 + 1];
        matrix[i][0] = i;
        for (int j = 1; j <= len1; j++) 
        {
            if (str2[i - 1] != str1[j - 1]) 
            {
                matrix[i][j] = minimum(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + 1);
            } 
            else 
            {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
        }
    }

    levenshteinData m = 
    {
        .matrix= matrix,
        .rows=len2 + 1,
        .cols=len1 + 1,
    };

    m.chainOperations = getChainOperations(m);

    return m;
}


// Выводит цепочку операций при сравнении строк
string getChainOperations(levenshteinData m) 
{
    int **matrix = m.matrix;
    int i = m.rows - 1, j = m.cols - 1;
    string chain = "";

    while (i != 0 || j != 0) 
    {
        if (i != 0 && matrix[i][j] > matrix[i - 1][j]) 
        {
            i--;
            chain += "D-";
            continue;
        }

        if (j != 0 && matrix[i][j] > matrix[i][j - 1]) 
        {
            j--;
            chain += "I-";
            continue;
        }

        if (j != 0 && i != 0 && matrix[i][j] > matrix[i - 1][j - 1]) 
        {
            j--;
            i--;
            chain += "R-";
            continue;
        }

        if (j != 0 && i != 0 && matrix[i][j] == matrix[i - 1][j - 1]) 
        {
            j--;
            i--;
            chain += "M-";
        }
    }

    chain.pop_back();

    return chain;
}


// Выводит последовательно все элементы матрицы
void printMatrix(levenshteinData m) 
{
    cout << "\tResult Levenshtein matrix " << m.rows << "x" <<  m.cols << ":" << endl;

    for (int i = 0; i < m.rows; i++) 
    {
        for (int j = 0; j < m.cols; j++) 
        {
            cout << m.matrix[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
}
