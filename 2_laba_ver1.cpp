#include <iostream>
#include <math.h>

using namespace std;


// Функция, которую мы будем интегрировать
double calculated_function(double);

//Вычисление шага интегрирования
double step_calculator(double,double,int);

// Метод левых прямоугольников для численного интегрирования
double left_rect_method(double, double, int);

// Метод правых прямоугольников для численного интегрирования
double right_rect_method(double, double, int);

// Метод трапеций для численного интегрирования
double trapez_method(double, double, int);

// Метод вычисления интеграла с заданной точностью и начальным шагом
void integration_precision(double integral_method(double, double, int), double, double, int, int, double, double);




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


                // метод левых прямоугольников
                cout << "\tIntegral_left_rect_method = " << left_rect_method(x_min, x_max, qty_segments) << endl;;

                // метод правых прямоугольников
                cout << "\tIntegral_right_rect_method = " << right_rect_method(x_min, x_max, qty_segments) << endl;

                // метод трапеций
                cout << "\tIntegral_trapez_method = " << trapez_method(x_min, x_max, qty_segments) << endl;

                break;
            }


            case 2: // Calculate integral WITH precision
            {
                double precision{}; // точность
                int qty_segments, qty_segments_max = 1000000;
                double x_min, x_max, mult;

                cout << "Input x_min = ";
                cin >> x_min;
                cout << "Input x_max = ";
                cin >> x_max;
                cout << "Input qty_segments = ";
                cin >> qty_segments;
                cout << "Enter multiplier = ";
                cin >> mult;
                cout << "Enter precision = ";
                cin >> precision;

                // метод левых прямоугольников
                cout << "\tIntegral_left_rect_method_precision(e) -> ";
                integration_precision(left_rect_method, x_min, x_max, qty_segments, qty_segments_max, mult, precision);
                
                // метод правых прямоугольников
                cout << "\tIntegral_right_rect_method_precision(e) -> ";
                integration_precision(right_rect_method, x_min, x_max, qty_segments, qty_segments_max, mult, precision);

                // метод тарпеций 
                cout << "\tIntegral_trapez_method_precision(e) -> ";
                integration_precision(trapez_method, x_min, x_max, qty_segments, qty_segments_max, mult, precision);

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
double calculated_function(double x) 
{
    return x/8 + sin(x * x);
    //return (cos(0.8*x+1.2))/(1/5+sin(x*x+0.6));
}

//Вычисление шага интегрирования
double step_calculator(double x_min,double x_max, int qty_segments){
    double step;
    step = (x_max - x_min) / qty_segments;

    return step;
}


// Метод левых прямоугольников для численного интегрирования
double left_rect_method(double x_min, double x_max, int qty_segments) 
{
    double x_left = x_min;
    double step = step_calculator(x_min, x_max, qty_segments);
    double integral{};

    // Цикл для вычисления суммы значений функции на каждом прямоугольнике
    for (int i = 0; i < qty_segments - 1; i++) 
    {
        integral += fabs(calculated_function(x_left) * step); // Площадь i-го прямоугольника идет в сумму
        x_left += step;
    }

    // Вычисление последней(остаточной) площади отдельно
    // Левую границу последнего прямоугольника умножаем на размер последнего шага
    integral += fabs(calculated_function(x_left) * (x_max - x_left));

    return integral;
}


// Метод правых прямоугольников для численного интегрирования
double right_rect_method(double x_min, double x_max, int qty_segments) 
{
    double x_right = x_max;
    double step = step_calculator(x_min, x_max, qty_segments);
    double integral{};

    
    for (int i = 0; i < qty_segments - 1; i++)
    {
        integral += fabs(calculated_function(x_right) * step); // Суммируем значения функции в точках правых краев прямоугольников
        x_right -= step;
    }

    // Вычисление последней(остаточной) площади отдельно
    integral += fabs(calculated_function(x_right) * (x_right - x_min));

    return integral;
}


// Метод трапеций для численного интегрирования
double trapez_method(double x_min, double x_max, int qty_segments) 
{
    double step = step_calculator(x_min, x_max, qty_segments);
    double x_left = x_min;
    double x_next = x_min + step;
    double integral{};

    // Суммируем значения внутри интервала с использованием трапеций
    for (int i = 0; i < qty_segments - 1; i++)
    {
        integral += fabs((calculated_function(x_left) + calculated_function(x_next)) / 2 * step);
        x_left = x_next;
        x_next += step;
    }

    // Вычисление последней(остаточной) площади отдельно 
    integral += fabs((calculated_function(x_left) + calculated_function(x_max)) / 2 * (x_max - x_left));

    return integral;
}

// Метод вычисления интеграла с заданной точностью и начальным шагом
void integration_precision(double integral_method(double, double, int), double x_min, double x_max, int qty_segments, int qty_segments_max, double mult, double precision)
{
    double I1, I2;//, precision;

    while (fabs(I1 - I2) >= precision || qty_segments < qty_segments_max)
    {
        I1 = I2;
        qty_segments *= mult; // увеличиваем кол-во шагов
        I2 = integral_method(x_min, x_max, qty_segments);


        if (fabs(I1 - I2) < precision && qty_segments < qty_segments_max)
        {
           cout << " " << I2 << "\n";
           return;
        }
    }

}
