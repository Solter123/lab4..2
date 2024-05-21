#include <iostream>
#include <string>


struct Stack { // структура стека
    char info; // информационное поле
    Stack* next;// указатель на следующую структуру
};


int prioritet(char);// определение приоритета
Stack* add(Stack, char);//    добавление элемента в стек
Stack del(Stack, char);//    удаление элемента из стека
void result(std::string, Stack*);    // решение выражения
char znach[] = { 'a', 'b', 'c', 'd', 'e' };//    буквы
int kol;// количество букв
double mas[5];//    массив значений

int main()
{
    setlocale(0, "ru");//    установка русского языка
    Stack* begin = NULL;//    указатель на первый элемент стека
    char ss;//        символ
    char a = ' ';//        промежуточная переменная
    std::string InStr = "a/(b*(c+d))-e", OutStr;//    строка для обратной польской записи
    std::cout << "Изначальная запись: " << InStr << std::endl;//    вывод изначальной записи
    for (int k = 0; k < InStr.size(); k++) {//    проход по строке
        ss = InStr[k];//        записываем в ss очередный элемент из строки
        if (ss == '(')//        если символ открывающая скобка
            begin = add(begin, ss);//        добавляем в стек
        if (ss == ')') {//        если символ закрывающая скобка
            while ((begin->info) != '(') {//        пока не встретим открывающую скобку
                begin = del(begin, &a);//        удаляем из стека
                OutStr += a;//        переменную a записываем в OutStr
            }//        пока не встретим открывающую скобку
            begin = del(begin, &a);//        удаляем открывающую скобку из стека
        }//        пока не встретим открывающую скобку
        if (ss >= 'a' && ss <= 'z') {//        если символ буква
            kol++;//        увеличиваем количество букв
            OutStr += ss;//        переменную ss записываем в OutStr
        }//        если символ буква
        if (ss == '*' or ss == '/' or ss == '+' or ss == '-' or ss == '^') {//        если символ математическое действие
            while (begin != NULL && prioritet(begin->info) >= prioritet(ss)) {//        пока не встретим открывающую скобку
                begin = del(begin, &a);//        удаляем из стека
                OutStr += a;//        переменную a записываем в OutStr
            }//        пока не встретим открывающую скобку
            begin = add(begin, ss);//        добавляем в стек
        }//        если символ математическое действие
    }//        проход по строке
    while (begin != NULL) {//        пока стек не пустой
        begin = del(begin, &a);//        удаляем из стека
        OutStr += a;//        переменную a записываем в OutStr
    }//        пока стек не пустой
    std::cout << "Обратная польская запись: " << OutStr << std::endl;//    вывод обратной польской записи
    std::cout << "Значения переменных: " << std::endl;//    вывод значений переменных
    char ch;//        переменная для хранения буквы
    for (int i = 0; i < kol; i++) {//    проход по строке
        ch = znach[i];//        записываем в ch очередную букву
        switch (ch) {//        в зависимости от буквы
        case 'a'://        если буква a
            mas[int(ch)] = 8.5;//        записываем в массив значений
            break;//        прерываем цикл
        case 'b'://        если буква b
            mas[int(ch)] = 0.3;//        записываем в массив значений
            break;//        прерываем цикл
        case 'c'://        если буква c
            mas[int(ch)] = 2.4;//        записываем в массив значений
            break;//        прерываем цикл
        case 'd'://        если буква d
            mas[int(ch)] = 7.9;//        записываем в массив значений
            break;//        прерываем цикл
        case 'e'://        если буква e
            mas[int(ch)] = 1.6;//        записываем в массив значений
            break; //
        }//
        std::cout << znach[i] << " = " << mas[int(ch)] << std::endl; //    вывод значений переменных
    }//        пока не встретим открывающую скобку
    result(OutStr, begin);//    вызов функции result
    system("pause");//    задержка экрана
    return 0;//    выход из программы
}//        пока не встретим открывающую скобку
int prioritet(char a) {
    switch (a) {
    case '^':
        return 4;
    case '*': case '/':
        return 3;
    case '-': case '+':
        return 2;
    case '(':
        return 1;
    }
    return 0;
}
void result(std::string opz, Stack* begin) {
    begin = NULL;
    char ch, ch1 = ' ', ch2 = ' ';
    double op1 = 0, op2 = 0, rez = 0;
    char chr = 'z' + 1;
    for (int i = 0; i < opz.size(); i++) {
        ch = opz[i];
        if (ch >= 'a' && ch <= 'z') {
            begin = add(begin, ch);
        }
        else {
            begin = del(begin, &ch1);
            begin = del(begin, &ch2);
            op1 = mas[int(ch1)];
            op2 = mas[int(ch2)];
            switch (ch) {
            case '+': rez = op2 + op1;
                break;
            case '-': rez = op2 - op1;
                break;
            case '*': rez = op2 * op1;
                break;
            case '/': rez = op2 / op1;
                break;
            case '^': rez = pow(op2, op1);
                break;
            }
            mas[int(chr)] = rez;
            begin = add(begin, chr);
            chr++;
        }
    }
    std::cout << "Результат: " << rez << std::endl;
    return;
}
Stack* del(Stack* p, char* out) {
    Stack* t = p;
    (*out) = p->info;
    p = p->next;
    delete t;
    return p;
}
Stack* add(Stack* p, char in) {
    Stack* t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}