#ifndef BNUM_H
#define BNUM_H
#include <QString>


class BNum
{
private:
    int size;
    char *digits=new char[1]; //storing the digits of the num
    void removeZero(); //remove extra zero from left
public:
    BNum();
    BNum(QString str);
    BNum(int Num);
    BNum& operator=(const BNum& other); //copy constructor
    ~BNum();

    void operator=(const QString& str); //some times we need to change the num with str
    void operator=(const int& Num);//some times we need to change the num with int
    BNum operator++(int);//++
    BNum operator--(int);//>>
    void shiftR();//>>
    void shiftL();//<<
    void shiftR(int n);//>>n
    void shiftL(int n);//<<n

    //why we use the & before other?!
    BNum operator +(const BNum &other);//+
    BNum operator +(const int &other);
    BNum operator -(const BNum &other);//-
    BNum multByOneDigit(int d);

    bool operator ==(const BNum &other);
    bool operator <(const BNum &other);
    bool operator >(const BNum &other);
    bool operator <=(const BNum &other);
    bool operator >=(const BNum &other);
    bool operator !=(const BNum &other);

    BNum operator *(const BNum &other);//*
    BNum operator /(const BNum &other);// /    //just current dividing
    BNum operator ^(const BNum &other);//^
    static BNum factorial(int Num);// this is not a bigNumber operator & just calculate factorial that is bigNum
    QString toString(); // just convert to Qstring!
    void printLog(); //print the number in Debugin
    BNum addZero(int d);//we need this in multiply to add some zero to nums and return new one
};

#endif // BNUM_H
