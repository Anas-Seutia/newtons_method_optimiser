#include <iostream>
#include <cmath> 
#include <fstream>
#include <sstream>
#define jml_data 13
using namespace std;
const double h = 1.e-3;
double ra; double rb; double rc;
double a; double b; double c;
double ha; double hb; double hc;
double x[10];
int n=10;


void createX(int realChoice) {
    switch (realChoice) {
        case 1:
            for (int i=0; i<n; i++) {
                x[i] = ra*i + rb;
            }
            break;
        case 2:
            for (int i=0; i<n; i++) {
                x[i] = ra*pow(i,2) + rb*i + rc;
            }
            break;
        case 3:
            for (int i=0; i<n; i++) {
                cout << "Input data for " << i << ": ";
                cin >> x[i];
            }
            break;
        default:
            for (int i=0; i<n; i++) {
                x[i] = ra*i + rb;
            }
            break;
    }
}


double model_lnr(int i) {
    return a*i + b;
}

double model_sqr(int i) {
    return a*pow(i,2) + b*i + c;
}

double obj_func(int modelChoice) {
    double sum=0;

    switch (modelChoice) {
        case 1:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_lnr(i)), 2);
            }
            break;
        case 2:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_sqr(i)), 2);
            }
            break;
        default:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_lnr(i)), 2);
            }
            break;
    }
    return(sum/n);
}

void obj_compare(int modelChoice) {
    switch (modelChoice) {
        case 1:
            for (int i = 0; i<n; i++) {
                cout << "predict: " << model_lnr(i) << " | real: " << x[i] << endl;
            }
            break;
        case 2:
            for (int i = 0; i<n; i++) {
                cout << "predict: " << model_sqr(i) << " | real: " << x[i] << endl;
            }
            break;
        default:
            for (int i = 0; i<n; i++) {
                cout << "predict: " << model_lnr(i) << " | real: " << x[i] << endl;
            }
            break;
    }   

}

double getDevA(int modelChoice) {
    a+=h;
    double left = obj_func(modelChoice);
    a-=2*h;
    double right = obj_func(modelChoice);
    a+=h;
    // cout << left << ":" << right << " = " << (left - right)/(h) << endl;
    return (left - right)/(h);
}

double getDevA2(int modelChoice) {
    a+=h;
    double left = obj_func(modelChoice);
    a-=2*h;
    double right = obj_func(modelChoice);
    a+=h;
    // cout << left << ":" << (2 * obj_func()) << ":" << right << " = " << (left - (2 * obj_func()) + right)/pow(h,2) << endl;
    return (left - (2 * obj_func(modelChoice)) + right)/pow(h,2);
}

double getDevB(int modelChoice) {
    b+=h;
    double left = obj_func(modelChoice);
    b-=2*h;
    double right = obj_func(modelChoice);
    b+=h;
    //cout << left << ":" << right << endl;
    return (left - right)/(h);
}

double getDevB2(int modelChoice) {
    b+=h;
    double left = obj_func(modelChoice);
    b-=2*h;
    double right = obj_func(modelChoice);
    b+=h;
    return (left - (2 * obj_func(modelChoice)) + right)/pow(h,2);
}

double getDevC(int modelChoice) {
    c+=h;
    double left = obj_func(modelChoice);
    c-=2*h;
    double right = obj_func(modelChoice);
    c+=h;
    //cout << left << ":" << right << endl;
    return (left - right)/(h);
}

double getDevC2(int modelChoice) {
    c+=h;
    double left = obj_func(modelChoice);
    c-=2*h;
    double right = obj_func(modelChoice);
    c+=h;
    return (left - (2 * obj_func(modelChoice)) + right)/pow(h,2);
}

void newtons(int modelChoice) {
    a=0.1; b=0.1; c=0.1;
    ha=1.; hb=1.; hc=1.;
    while (obj_func(modelChoice) >= 1.e-2) {
        ha = (getDevA(modelChoice) / getDevA2(modelChoice));
        // cout << -getDevA() << ":" << getDevA2() << "=" << ha << endl;
        hb = (getDevB(modelChoice) / getDevB2(modelChoice));
        // cout << -getDevB() << ":" << getDevB2() << "=" << hb << endl;
        hc = (getDevC(modelChoice) / getDevC2(modelChoice));
        a -= ha * h;
        b -= hb * h;
        c -= hc * h;
        //cout << a << " " << b << " " << c << endl;
        //cout << ha << " " << hb << " " << hc << endl;
    }
    cout << "a = " << a << ", b = " << b << ", c = " << c << ": error = " << obj_func(modelChoice) << endl;
}

int main() {
    int modelChoice = -1;

    cout << "Pick model: " << endl;
    cout << "1. Linear" << endl;
    cout << "2. Square" << endl;
    cout << "Choice: ";
    cin >> modelChoice;

    system("cls");

    int realChoice = -1;

    cout << "Pick Real Model: " << endl;
    cout << "1. Linear: a*x + b" << endl;
    cout << "2. Square: a*x^2 + b*x + c" << endl;
    cout << "3. Manual input (x = 0 -> 10)" << endl;
    cout << "Choice: ";
    cin >> realChoice;

    if (realChoice != 6) {
        cout << "Input Coefficients: " << endl;
        cout << "Input a: ";
        cin >> ra;
        cout << "Input b: ";
        cin >> rb;
        if (realChoice == 2) {
            cout << "Input c: ";
            cin >> rc;
        }
    }

    system("cls");

    createX(realChoice);
    newtons(modelChoice);
    
    obj_compare(modelChoice);
    cin >> n;
}