#ifndef BNUM_H
#define BNUM_H
#include <QString>


class BNum
{
private:
    //these initializions to avoid memory errors!
    int size=1;
    char *digits=new char; //storing the digits of the num
    bool sign=true;//true --> positive & false --> negetive
    void removeZero(); //remove extra zero from left
    BNum normalPlus(const BNum First,const BNum Second);//add twe positive BNums
    BNum normalMinus(const BNum First,const BNum Second);//minus twe negetive BNums that we know result is positive
    int normalCompare(const BNum First,const BNum Second);//compare twe positive BNum : (-1-->first<second) & (0-->equal) & (1-->first>second)
    BNum normalDivide(const BNum First,const BNum Second);//devide twe positive BNums

public:
    BNum();
    BNum(const QString Str);
    BNum(const int Num);
    BNum(const BNum& other);//copy constructor
    BNum& operator=(const BNum& other);
    ~BNum();

    void operator=(const QString& Str); //some times we need to change the num with str
    void operator=(const int& Num);//some times we need to change the num with int
    BNum operator++(int);//++
    BNum operator--(int);//>>
    void shiftR();//>>
    void shiftL();//<<
    void shiftR(int n);//>>n
    void shiftL(int n);//<<n

    //why we use the & before other?!
    BNum operator +(const BNum &other);//+
    BNum operator +(const int Num);
    BNum operator -(const BNum &other);//-
    BNum operator -(const int Num);
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
