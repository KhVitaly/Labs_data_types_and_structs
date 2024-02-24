#include <iostream>
#include <math.h>

using namespace std;


// Функция, которую мы будем интегрировать
double function(double);

// Метод левых прямоугольников для численного интегрирования
double left_rect_method(double, double, int);

// Метод правых прямоугольников для численного интегрирования
double right_rect_method(double, double, int);

// Метод трапеций для численного интегрирования
double trapez_method(double, double, int);

// Метод левых прямоугольников для численного интегрирования с заданной точностью
double left_rect_method_precision(double, double, int, int, double);

// Метод правых прямоугольников для численного интегрирования с заданной точностью
double right_rect_method_precision(double, double, int, int, double);

// Метод трапеций для численного интегрирования с заданной точностью
double trapez_method_precision(double, double, int, int, double);


int main()
{
    double x_min{}, x_max{};
    int qty_segments{}; // кол-во отрезков разбиения


    int choice;
    while (1)
    {
        cout << endl << "Choose an action:" << endl;
        //cout << "\t1 - Enter: x_min, x_max, qty_segments" << endl; 
        cout << "\t1 - Calculate integral WITHOUT precision" << endl;
        cout << "\t2 - Calculate integral WITH precision" << endl;
        cout << "\t0 - Exit" << endl;
        cout << endl << "Enter your choice -> ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            /*case 1:
            {
                cout << "Input x_min = ";
                cin >> x_min;
                cout << "Input x_max = ";
                cin >> x_max;
                cout << "Input qty_segments = ";
                cin >> qty_segments;
                break;
            }
            */
            case 1: // Calculate integral WITHOUT precision
            {
                cout << "Input x_min = ";
                cin >> x_min;
                cout << "Input x_max = ";
                cin >> x_max;
                cout << "Input qty_segments = ";
                cin >> qty_segments;


                double Integral_left_rect_method = left_rect_method(x_min, x_max, qty_segments); // метод левых прямоугольников
                cout << "\tIntegral_left_rect_method = " << Integral_left_rect_method << endl;;

                double Integral_right_rect_method = right_rect_method(x_min, x_max, qty_segments); // метод правых прямоугольников
                cout << "\tIntegral_right_rect_method = " << Integral_right_rect_method << endl;

                double Integral_trapez_method = trapez_method(x_min, x_max, qty_segments); // метод трапеций
                cout << "\tIntegral_trapez_method = " << Integral_trapez_method << endl;

                break;
            }

            case 2: // Calculate integral WITH precision
            {
                double precision{}; // точность
                int start_qty_segments{}; // начальное значение кол-ва шагов

                cout << "Input precision(E) = ";
                cin >> precision;                
                cout << "Input start_qty_segments = ";
                cin >> start_qty_segments;

                double Integral_left_rect_method_precision = left_rect_method_precision(x_min, x_max, start_qty_segments, qty_segments, precision); // метод левых прямоугольников
                cout << "\tIntegral_left_rect_method_precision = " << Integral_left_rect_method_precision << endl;
                
                double Integral_right_rect_method_precision = right_rect_method_precision(x_min, x_max, start_qty_segments, qty_segments, precision); // метод правых прямоугольников
                cout << "\tIntegral_right_rect_method_precision = " << Integral_right_rect_method_precision << endl;

                double Integral_trapez_method_precision = trapez_method_precision(x_min, x_max, start_qty_segments, qty_segments, precision); // метод тарпеций 
                cout << "\tIntegral_trapez_method_precision = " << Integral_trapez_method_precision << endl;

                break;
            }

            case 0:
            {
                cout << endl << "\tExiting the program..." << endl;
                return 0;
            }

            default:
                cout << endl << "Invalid choice! Try again!" << endl;
        }
    }

    return 0;
}


// Функция, которую мы будем интегрировать
double function(double x) 
{
    return x/8 + sin(x * x);
    //return (cos(0.8*x+1.2))/(1/5+sin(x*x+0.6));
}

// Метод левых прямоугольников для численного интегрирования
double left_rect_method(double x_min, double x_max, int qty_segments) 
{
    double step = (x_max - x_min) / qty_segments; // Шаг разбиения интервала интегрирования
    double integral{};

    // Цикл для вычисления суммы значений функции на каждом прямоугольнике
    for (int i = 0; i <= qty_segments - 1; i++) 
    {
        integral += function(x_min + step * i) * step; // Площадь i-го прямоугольника идет в сумму
    }

    // Вычисление последней(остаточной) площади отдельно
    // Левую границу последнего прямоугольника умножаем на размер последнего шага
    double x_left_last = x_min + (qty_segments - 1) * step;
    double last_step = x_max - x_min - (qty_segments - 1) * step;
    integral += function(x_left_last) * last_step;

    return integral;
}


// Метод правых прямоугольников для численного интегрирования
double right_rect_method(double x_min, double x_max, int qty_segments) 
{
    double step = (x_max - x_min) / qty_segments; // Шаг интегрирования
    double integral{};

    
    for (int i = 1; i <= qty_segments; i++)
    {
        integral += function(x_min + step * i) * step; // Суммируем значения функции в точках правых краев прямоугольников
    }

    // Вычисление последней(остаточной) площади отдельно
    double x_right_last = x_max;
    double last_step = x_max - x_min - (qty_segments - 1) * step;
    integral += function(x_right_last) * last_step;

    return integral;
}


// Метод трапеций для численного интегрирования
double trapez_method(double x_min, double x_max, int qty_segments) 
{
    double step = (x_max - x_min) / qty_segments; // Вычисляем шаг
    double integral = function(x_min) + function(x_max); // Суммируем краевые точки

    // Суммируем значения внутри интервала с использованием трапеций
    for (int i = 1; i <= qty_segments - 1; i++)
    {
        integral += 2 * function(x_min + step * i);
    }

    integral *= step/2;

    // Вычисление последней(остаточной) площади отдельно        ??????
    double x_left_last = x_min + (qty_segments - 1) * step;
    double x_right_last = x_max;
    double last_step = x_max - x_min - (qty_segments - 1) * step;
    integral += (function(x_left_last) + function(x_right_last)) * last_step / 2;
    //integral += ((function(x_min + (qty_segments - 1) * step) + function(x_max)) / 2) * step;

    return integral;
}


// Метод левых прямоугольников для численного интегрирования с заданной точностью
double left_rect_method_precision(double x_min, double x_max, int start_qty_segments, int qty_segments, double precision) 
{   
    double I1, I2;
    I2 = left_rect_method(x_min, x_max, start_qty_segments);
    do
    {
        I1 = I2;
        start_qty_segments *= 2;
        I2 = left_rect_method(x_min, x_max, start_qty_segments);
    }
    while (fabs(I1 - I2) <= precision || start_qty_segments > qty_segments);

    return I2;
}


// Метод правых прямоугольников для численного интегрирования с заданной точностью
double right_rect_method_precision(double x_min, double x_max, int start_qty_segments, int qty_segments, double precision) 
{   
    double I1, I2;
    I2 = right_rect_method(x_min, x_max, start_qty_segments);
    do
    {
        I1 = I2;
        start_qty_segments *= 2;
        I2 = right_rect_method(x_min, x_max, start_qty_segments);
    }
    while (fabs(I1 - I2) <= precision || start_qty_segments > qty_segments);

    return I2;
}


// Метод трапеций для численного интегрирования с заданной точностью
double trapez_method_precision(double x_min, double x_max, int start_qty_segments, int qty_segments, double precision) 
{   
    double I1, I2;
    I2 = trapez_method(x_min, x_max, start_qty_segments);
    do
    {
        I1 = I2;
        start_qty_segments *= 2;
        I2 = trapez_method(x_min, x_max, start_qty_segments);
    }
    while (fabs(I1 - I2) <= precision || start_qty_segments > qty_segments);

    return I2;
}
