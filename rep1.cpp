#include <iostream>
#include <string>


struct Stack { // структура стека
    char info; // информационное поле
    Stack* next;// указатель на следующую структуру
};


int prioritet(char);
Stack* add(Stack*, char);
Stack* del(Stack*, char*);
void result(std::string, Stack*);
char znach[] = { 'a', 'b', 'c', 'd', 'e' };
int kol;
double mas[5];

int main()
{
    setlocale(0, "ru");
    Stack* begin = NULL;
    char ss;
    char a = ' ';
    std::string InStr = "a/(b*(c+d))-e", OutStr;
    std::cout << "Изначальная запись: " << InStr << std::endl;
    for (int k = 0; k < InStr.size(); k++) {
        ss = InStr[k];
        if (ss == '(')
            begin = add(begin, ss);
        if (ss == ')') {
            while ((begin->info) != '(') {
                begin = del(begin, &a);
                OutStr += a;
            }
            begin = del(begin, &a);
        }
        if (ss >= 'a' && ss <= 'z') {
            kol++;
            OutStr += ss;
        }
        if (ss == '*' or ss == '/' or ss == '+' or ss == '-' or ss == '^') {
            while (begin != NULL && prioritet(begin->info) >= prioritet(ss)) {
                begin = del(begin, &a);
                OutStr += a;
            }
            begin = add(begin, ss);
        }
    }
    while (begin != NULL) {
        begin = del(begin, &a);
        OutStr += a;
    }
    std::cout << "Обратная польская запись: " << OutStr << std::endl;
    std::cout << "Значения переменных: " << std::endl;
    char ch;
    for (int i = 0; i < kol; i++) {
        ch = znach[i];
        switch (ch) {
        case 'a':
            mas[int(ch)] = 8.5;
            break;
        case 'b':
            mas[int(ch)] = 0.3;
            break;
        case 'c':
            mas[int(ch)] = 2.4;
            break;
        case 'd':
            mas[int(ch)] = 7.9;
            break;
        case 'e':
            mas[int(ch)] = 1.6;
            break;
        }
        std::cout << znach[i] << " = " << mas[int(ch)] << std::endl;
    }
    result(OutStr, begin);
    system("pause");
    return 0;
}
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