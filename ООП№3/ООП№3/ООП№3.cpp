#include <iostream>
#include <cmath>
using namespace std;

class Function {
protected:
    double x;
    double y;
public:
    Function();
    Function(double, double);
    Function(Function& );

    virtual double Evaluate(double) = 0;
    virtual void Print();
};

Function::Function() : x(0), y(0) {}

Function:: Function(double x, double y) {
    this->x = x;
    this->y = y;
}

Function::Function(Function& f) {
    x = f.x;
    y = f.y;
}

void Function::Print() {
    cout << "f(" << x << ") = " << y << endl;
}          

// лінійна функція y = kx + b
class LinearFunction : public Function {
private: 
    double k;
    double b;
public:
    LinearFunction();
    LinearFunction(double , double );
    LinearFunction(LinearFunction& );

    double Evaluate(double ) override;
    void Print() override;
};

LinearFunction ::   LinearFunction() :k(0), b(0){}

LinearFunction::LinearFunction(double k, double b) {
    this->k = k;
    this->b = b;
}

LinearFunction::LinearFunction(LinearFunction& f) : Function(f) {
    k = f.k;
    b = f.b;
}

double LinearFunction::Evaluate(double x) {
    this->x = x;
    y = k * x + b;
    return y;
}
   
void LinearFunction::Print() {
    cout << "Linear f(x) = " << k << "x + " << b << endl;
    Function::Print();
}
   
// квадратична функція y = ax^2+bx+c
class QuadraticFunction : public Function {
private:
    double a;
    double b;
    double c;
public:
    QuadraticFunction();
    QuadraticFunction(double , double , double );
    QuadraticFunction(QuadraticFunction& );

    double Evaluate(double ) override;
    void Print() override;

};

QuadraticFunction::QuadraticFunction() : a(0), b(0), c(0) {}

QuadraticFunction::QuadraticFunction(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;

}

QuadraticFunction::QuadraticFunction(QuadraticFunction& f) : Function(f) {
    a = f.a;
    b = f.b;
    c = f.c;
}

double QuadraticFunction::Evaluate(double x) {
    this->x = x;
    y = a * pow(x, 2) + b * x + c;
    return y;
}
    
void QuadraticFunction::Print() {
    cout << "Quadratic f(x) = " << a << "x^2 + " << b << "x + " << c << endl;
    Function::Print();
}


// тригонометрична функція y = sin(x) ...
class TrigonometricFunction : public Function {
public:
    TrigonometricFunction();

    double Evaluate(double) override;
    void Print() override;
};

TrigonometricFunction::TrigonometricFunction() {}
      
double TrigonometricFunction::Evaluate(double x) {
    this->x = x;
    y = sin(x);
    return y;

}

void TrigonometricFunction::Print() {
    cout << "Trigonometric f(x) = sin(x)" << endl;
    Function::Print();
}

// степенева функція y = x^a
class PowerFunction : public Function {
private:
    double a;
public:
    PowerFunction();
    PowerFunction(double);
    PowerFunction(PowerFunction&);

    double Evaluate(double) override;
    void Print() override;
 };

PowerFunction::PowerFunction() :a(0) {}

PowerFunction::PowerFunction(double a) {
    this->a = a;
}

PowerFunction::PowerFunction(PowerFunction& f) : Function(f) {
    a = f.a;
}

double PowerFunction::Evaluate(double x) {
    this->x = x;
    y = pow(x, a);
    return y;
}
    
void PowerFunction::Print() {
    cout << "Power f(x) = x^" << a << endl;
    Function::Print();
}


// показникова функція y = a^(x)
class IndicatorFunction : public Function {
private:
    double a;
public:
    IndicatorFunction();
    IndicatorFunction(double );
    IndicatorFunction(IndicatorFunction& );

    double Evaluate(double ) override;
    void Print() override;
};

IndicatorFunction::IndicatorFunction() :a(0) {}

IndicatorFunction::IndicatorFunction(double a) {
    this->a = a;
}

IndicatorFunction::IndicatorFunction(IndicatorFunction& f) : Function(f) {
    a = f.a;
}

double IndicatorFunction::Evaluate(double x) {
    this->x = x;
    y = pow(a, x);
    return y;
}

void IndicatorFunction::Print() {
    cout << "Indicator f(x) = " << a << "^x" << endl;
    Function::Print();
}   

// обернена пропорційність y = k/x 
class InverseProportionalityFunction : public Function {
private:
    double k;
public:
    InverseProportionalityFunction();
    InverseProportionalityFunction(double );
    InverseProportionalityFunction(InverseProportionalityFunction& );

    double Evaluate(double ) override;
    void Print() override;

};
InverseProportionalityFunction::InverseProportionalityFunction() : k(0) { }

InverseProportionalityFunction::InverseProportionalityFunction(double k) {
    this->k = k;
}

InverseProportionalityFunction::InverseProportionalityFunction(InverseProportionalityFunction& f) : Function(f) {
    k = f.k;
}

double InverseProportionalityFunction::Evaluate(double x) {
    if (x == 0) abort();
    this->x = x;

    y = k / x;
    return y;
}

void InverseProportionalityFunction::Print() {
    cout << "Inverse Proportiona f(x) = " << k << "/x" << endl;
    Function::Print();
}


class Container {
private:
    Function** f;
    int size;
    double sum;
    double x;
public:
    Container();

    void addFunction(Function*);
    double sumFunctionValues(double);
    
    void Print();
    ~Container();
};

Container::Container() : f(nullptr), size(0), sum(0), x(0) {}

void Container::addFunction(Function* func) {
    Function** temp = new Function * [size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = f[i];
    }
    temp[size++] = func;
    delete[] f;
    f = temp;

}
   
double Container::sumFunctionValues(double x) {
    this->x = x;
    for (int i = 0; i < size; i++) {
        sum += f[i]->Evaluate(x);
    }
    return sum;
}

void Container::Print() {
    for (int i = 0; i < size; i++) {
        f[i]->Print();
    }
    cout << "Sum function in container (x = " << x << "): " << sum;
}

Container:: ~Container() {
    delete[] f;
}

int main(){    
   
    LinearFunction L(2, 3);    
    L.Evaluate(5);
    L.Print();
 
    QuadraticFunction Q(1, 5, 8);
    Q.Evaluate(3);
    Q.Print();

    TrigonometricFunction T;
    T.Evaluate(3);
    T.Print();

    PowerFunction P(2);
    P.Evaluate(3);
    P.Print();

    IndicatorFunction I(8);
    I.Evaluate(4);
    I.Print();

    InverseProportionalityFunction IP(7);
    IP.Evaluate(4);
    IP.Print();

    cout << endl;
    cout << "Function in container: " << endl;
    Container func;      
    
    func.addFunction(&L);
    func.addFunction(&Q);
    func.addFunction(&T);
    func.addFunction(&P);
    func.addFunction(&I);
    func.addFunction(&IP);
    func.sumFunctionValues(2);
    func.Print(); 

}


