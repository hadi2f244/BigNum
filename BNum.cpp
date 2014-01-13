#include "bnum.h"
#include <math.h>
#include <QDebug>


// remains: operator/ and one operator optimizing & operator ^ & optimizing factorial

int toInt(char);
char toChar(int num);

//constructors
BNum::BNum()
{
    this->size=1;
    this->digits[0]='0';
    //    digits=new char;
}
BNum::~BNum()
{
    delete digits;
}

BNum::BNum(QString str)
{
    //now we want to split the string to char(digits)
    this->size=str.size();
    char *remover=new char[this->size];
    remover=this->digits;
    this->digits=new char[str.size()];
    for(int i=0;i<str.size()+1;i++)
    {
        digits[str.size()-i-1]=str[i].toLatin1();
    }
    delete[] remover;

}
BNum::BNum(int Num)
{
    if(Num==0)
    {
        char *remover=new char[this->size];
        remover=this->digits;
        this->digits=new char[1];
        this->size=1;
        this->digits[0]='0';
        delete[] remover;
        return ;
    }
    //now we want to convert the int to chars(digits)
    this->size=log10(Num)+1; //calculating the Num size
    int digit,numCopy;
    numCopy=Num;
    int tSum=0; //save the digitarary sum like : 1000+200+30+4

    char *remover=new char[this->size];
    remover=this->digits;
    this->digits=new char[this->size];
    delete[] remover;
    for(int i=size-1;i>=0;i--) //with this loop split the digits
    {
        numCopy=Num-tSum;
        digit =numCopy / pow(10,i);
        tSum+=digit*pow(10,i);
        digits[i]=(char)digit+48;
    }
}
BNum& BNum::operator=(const BNum& other)
{

    char *remover=new char[this->size];
    remover=this->digits;
    this->size=other.size;
    this->digits=new char[this->size];


    for(int i=0;i<size;i++)
    {
        digits[i]=other.digits[i];
    }
    delete[] remover;
    return *this;
}

//operators
BNum BNum::operator ++(int)
{
    //now we want to add just a one num to big number
    //so we can use + operator
    *this=*this+1;
    return *this;
}
BNum BNum::operator --(int)
{
    //now we want to minus one from our num
    //so we can use - operator
    //    *this=*this-1;
    return *this;
}
BNum BNum::operator +(const BNum &other)
{
    //now we want to add to bin num

    BNum first;
    BNum second; //we don't want to change this and other nums
    first=*this;
    second = other;
    //    qDebug()<<this->size<<other.size;
    int maxSize= first.size > second.size ? first.size : second.size;
    if(maxSize==first.size)
    {
        //lets improve the second one to upper digits
        char *tempDigits=new char[maxSize];
        for(int i=0;i<second.size;i++)
            tempDigits[i]=second.digits[i];
        for(int i=second.size;i<maxSize;i++)
            tempDigits[i]='0';
        //delet second.digits and reset
        char *remover=new char[second.size];
        remover=second.digits;
        second.size=maxSize;
        second.digits=tempDigits;
        delete[] remover;
    }
    else if(maxSize==second.size)
    {
        //lets improve the second one to upper digits
        char *tempDigits=new char[maxSize];
        for(int i=0;i<first.size;i++)
            tempDigits[i]=first.digits[i];
        for(int i=first.size;i<maxSize;i++)
            tempDigits[i]='0';
        //delet first.digits and reset
        char *remover=new char[first.size];
        remover=first.digits;
        first.size=maxSize;
        first.digits=tempDigits;
        delete[] remover;
    }

    BNum result(0); //we will return
    result.size=maxSize;
    char *remover=new char[maxSize];
    remover=result.digits;
    result.digits=new char[maxSize]; //maybe we have carry at last
    delete[] remover;
    //now we add some zero to the lower one
    //lets add to nums
    int carry=0;
    int tempInt;
    for(int i=0;i<maxSize;i++)
    {
        tempInt=toInt(first.digits[i])+toInt(second.digits[i])+carry;

        result.digits[i]=toChar(tempInt % 10);
        carry=(tempInt-(tempInt%10))/10;
    }
    if(carry!=0)
    {
        char *tempDigits=new char[maxSize+1];
        char *remover=new char[maxSize];
        remover=result.digits;
        result.size++;
        for(int i=0;i<maxSize;i++)
            tempDigits[i]=result.digits[i];
        tempDigits[maxSize]=toChar(carry);
        result.digits=new char[maxSize+1];
        result.digits=tempDigits;
        delete[] remover;
    }
    return result;
}
BNum BNum::operator +(const int &other)
{
    //first we create a temp BNum with that int then add
    BNum tNum(other);
    BNum first;
    first = *this;
    return first+tNum;
}

BNum BNum::operator -(const BNum &other)
{
    BNum first=*this;
    BNum second=other; //we don't want to change this and other nums

    int maxSize= first.size > second.size ? first.size : second.size;
    if(maxSize==first.size)
    {
        //lets improve the second one to upper digits
        char *tempDigits=new char[maxSize];
        for(int i=0;i<second.size;i++)
            tempDigits[i]=second.digits[i];
        for(int i=second.size;i<maxSize;i++)
            tempDigits[i]='0';
        //delet second.digits and reset
        char *remover=new char[second.size];
        remover=second.digits;
        second.size=maxSize;
        second.digits=tempDigits;
        delete[] remover;

    }
    if(maxSize==second.size)
    {
        //lets improve the second one to upper digits
        char *tempDigits=new char[maxSize];
        for(int i=0;i<first.size;i++)
            tempDigits[i]=first.digits[i];
        for(int i=first.size;i<maxSize;i++)
            tempDigits[i]='0';
        //delet first.digits and reset
        char *remover=new char[first.size];
        remover=first.digits;
        first.size=maxSize;
        first.digits=tempDigits;
        delete[] remover;
    }


    BNum result; //we will return
    result.size=maxSize;
    char *remover=new char[result.size];
    remover=result.digits;
    result.digits=new char[maxSize];
    delete[] remover;
    int minCarry=0;
    //now we have twe num with imporoved size
    for(int i=0;i<maxSize;i++)
    {
        if(toInt(first.digits[i])>=toInt(second.digits[i])+minCarry)
        {
            result.digits[i]=toChar(toInt(first.digits[i])-toInt(second.digits[i])-minCarry);
            minCarry=0;
        }
        else
        {
            result.digits[i]=toChar(10 + toInt(first.digits[i]) - toInt(second.digits[i])-minCarry);
            minCarry=1;
        }
    }
    result.removeZero(); //there are some extra zero
    return result;
}

BNum BNum::operator *(const BNum &other)
{
    BNum result(0);
    BNum first=*this;
    BNum second=other;
    BNum temp;
    for(int i=0;i<second.size;i++)//lets mult every second digits to first
    {
        result = result + (first.multByOneDigit(toInt(second.digits[i]))).addZero(i);
    }
//    second.printLog();

    return result;
}

void BNum::operator=(const QString& str)
{
    char *remover=new char[this->size];
    remover=this->digits;
    this->size=str.size();
    this->digits=new char[str.size()];
    delete[] remover;
    for(int i=0;i<str.size();i++)
    {
        digits[str.size()-i-1]=str[i].toLatin1();
    }
}
void BNum::operator=(const int& Num)
{
    if(Num==0)
    {
        char *remover=new char[this->size];
        remover=this->digits;
        this->digits=new char[1];
        this->digits[0]='0';
        this->size=1;
        delete[] remover;
        return ;
    }
    //now we want to convert the int to chars(digits)
    this->size=log10(Num)+1; //calculating the Num size
    int digit,numCopy;
    numCopy=Num;
    int tSum=0; //save the digitarary sum like : 1000+200+30+4
    char *remover=new char[this->size];
    remover=this->digits;
    this->digits=new char[this->size];
    delete[] remover;
    for(int i=size-1;i>=0;i--) //with this loop split the digits
    {
        numCopy=Num-tSum;
        digit =numCopy / pow(10,i);
        tSum+=digit*pow(10,i);
        digits[i]=(char)digit+48;
    }
}


bool BNum::operator ==(const BNum &other)
{
    if(this->size!=other.size)
        return false;
    for(int i=0;i<this->size;i++)
    {
        if(this->digits[i]!=other.digits[i])
            return false;
    }
    return true;
}
bool BNum::operator <(const BNum &other)
{
    if(this->size<other.size)
        return true;
    for(int i=this->size-1;i>=0;i--)
    {
        if(this->digits[i]<other.digits[i])
            return true;
    }
    return false;
}
bool BNum::operator >(const BNum &other)
{
    if(this->size>other.size)
        return true;
    for(int i=this->size-1;i>=0;i--)
    {
        if(this->digits[i]>other.digits[i])
            return true;
    }
    return false;
}
bool BNum::operator <=(const BNum &other)
{
    if(*this==other)
        return true;
    if(this->size<other.size)
        return true;
    for(int i=this->size-1;i>=0;i--)
    {
        if(this->digits[i]<other.digits[i])
            return true;
    }
    return false;
}
bool BNum::operator >=(const BNum &other)
{
    if(*this==other)
        return true;
    if(this->size>other.size)
        return true;
    for(int i=this->size-1;i>=0;i--)
    {
        if(this->digits[i]>other.digits[i])
            return true;
    }
    return false;
}
bool BNum::operator !=(const BNum &other)
{
    if(this->size!=other.size)
        return true;
    for(int i=0;i<this->size;i++)
    {
        if(this->digits[i]!=other.digits[i])
            return true;
    }
    return false;
}

BNum BNum::operator ^(const BNum &other)
{
    BNum result(1);
//    BNum i(0);
    BNum first(3);
//    first=*this;
    for(int i=0;i<=5;i++)
    {
        result.printLog();
        result = result * first;
    }
    return result;
}



//otherFuncs

BNum BNum::factorial(int Num)
{
    BNum result(1);
    BNum temp;
    for(int i=1;i<=Num;i++)
    {
        temp=i;
        qDebug()<<i;
        result= result * temp;
    }
    return result;
}

void BNum::removeZero()
{
    int tSize=this->size; //have a size copy
    int step=tSize-1; //just for whileLoop
    while(step!=0)
    {
        if(this->digits[step]=='0')
        {
            tSize--;
            step--;
        }
        else
            step=0;
    }

    this->size=tSize;

    //now we have new size ,lets handle the digits
    char *tDigits=new char[tSize];
    for(int i=0;i<tSize;i++)
    {
        tDigits[i]=this->digits[i];
    }

    char *remover=new char[this->size];
    remover=this->digits;
    this->digits=tDigits;
    delete[] remover;
}
BNum BNum::multByOneDigit(int d)
{
    //now lets do new job
    BNum result(0);//why we use zero here app crash!!!
    BNum temp;
    //result size
    for(int i=0;i<this->size;i++)
    {
        temp=d*toInt(this->digits[i]); //we cant multiply the nums with pow(10,i) because we work with bNums!
        //        temp.printLog();
        result=result + temp.addZero(i);
    }
    return result;
}


BNum BNum::addZero(int d)
{
    BNum temp;
    int tSize=this->size+d;
    temp.size=tSize;

    char *remover = new char[temp.size];
    remover=temp.digits;
    temp.digits=new char[tSize];
    delete[] remover;
    for(int i=0;i<d;i++)
    {
        temp.digits[i]='0';
    }
    for(int i=d;i<tSize;i++)
    {
        temp.digits[i]=this->digits[i-d];
    }

    return temp;
}

QString BNum::toString()
{
    QString tempStr="";

    for(int i=size-1;i>=0;i--)
    {
        tempStr+=digits[i];
    }
    return tempStr;
}
void BNum::printLog()
{
    QString tempStr="";

    qDebug()<<"The num is : ";

    for(int i=size-1;i>=0;i--)
    {
        tempStr+=digits[i];
    }
    qDebug()<<tempStr;
}

int toInt(char ch)
{
    return  (int)ch-48;
}
char toChar(int num)
{
    return (char)num+48;
}




