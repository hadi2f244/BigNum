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
    this->sign=true;
    this->digits[0]='0';
    //    digits=new char;
}
BNum::~BNum()
{
    delete[] digits;
}

BNum::BNum(const QString Str)
{
    QString str=Str;
    //this if select the sign
    if(str[0]=='+')
    {
        this->sign=true;
        str=str.mid(1); //just del the sign
    }
    else if(str[0]=='-')
    {
        this->sign=false;
        str=str.mid(1); //just del the sign
    }
    else
    {
        this->sign=true;
    }

    //    now we want to split the string to char(digits)
    if(str=="0")
    {
        char *remover=new char[1]; //me: there was an error that before this we doesn't have any this-->size !
        remover=this->digits;
        this->digits=new char[1];
        this->size=1;
        this->digits[0]='0';
        delete[] remover;
        return ;
    }

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

BNum::BNum(const int Num)
{
    //just convert int to string then do like another constructor
    //convert int to string:
    QString str;
    str=QString::number(Num);


    //this if select the sign
    if(str[0]=='+')
    {
        this->sign=true;
        str=str.mid(1); //just del the sign
    }
    else if(str[0]=='-')
    {
        this->sign=false;
        str=str.mid(1); //just del the sign
    }
    else
    {
        this->sign=true;
    }


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

BNum::BNum(const BNum &other)
{
    this->sign=other.sign;
    char *remover=new char[this->size];
    remover=this->digits;
    this->size=other.size;
    this->digits=new char[this->size];


    for(int i=0;i<size;i++)
    {
        digits[i]=other.digits[i];
    }
    delete[] remover;
}


//privateOperators:

BNum BNum::normalPlus(const BNum First, const BNum Second)
{
    BNum first=First;
    BNum second=Second; //we don't want to change First and Second nums

    //    first=*this;
    //    second
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

BNum BNum::normalMinus(const BNum First, const BNum Second)
{

    BNum first=First;
    BNum second=Second; //we don't want to change this and other nums

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

BNum BNum::normalDivide(const BNum First, const BNum Second)
{
    //    BNum result(0);
    BNum first=First;
    BNum second=Second;
    first=first-second;
    BNum i(0);
    if(second==i)//first is 0
    {
        qDebug()<<"ERROR:Divition by Zero";
        i--;
        return i; //-1 means Error!
    }
    if(!first.sign)
        return i;

    while(first.sign)
    {
        first=first-second;
        i++;
    }
    return i;
}


int BNum::normalCompare(const BNum First, const BNum Second)
{
    // (-1-->first<second) & (0-->equal) & (1-->first>second)
    if(First.size<Second.size)
    {
        return -1;
    }
    else if(First.size>Second.size)
    {
        return 1;
    }
    else
    {
        for(int i=First.size-1;i>=0;i--)
        {
            if(First.digits[i]<Second.digits[i])
            {
                return -1;
            }
            else if(First.digits[i]>Second.digits[i])
            {
                return 1;
            }
        }
    }
    return 0;
}



//operators
BNum& BNum::operator=(const BNum& other)
{
    this->sign=other.sign;
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
    *this=*this-1;
    return *this;
}


BNum BNum::operator +(const BNum &other)
{
    BNum result(0);
    BNum first=*this;
    BNum second=other;
    //    int state=normalCompare(first,second);
    //now we want to add twe BNums
    //maybe the nums are neg or positive
    //4 state:
    //1:first & second are positive
    //2:first & second are negetive
    //3:first is positive & second is negetive --> first - second
    //4:first is negetive & second is positive --> second - first

    //1:
    if(first.sign==true && second.sign==true)
    {
        result=normalPlus(first,second);
        result.sign=true;
    }
    //2:
    else if(first.sign==false && second.sign==false)
    {
        result=normalPlus(first,second);
        result.sign=false;
    }
    //3:
    else if(first.sign=true && second.sign==false)
    {
        second.sign=true;
        result = first - second ;//The sign is selected in operator- ,too
    }
    //4:
    else if(first.sign==false && second.sign==true)
    {
        first.sign=true;
        result =second - first ; //The sign is selected in operator- ,too
    }
    return result;
}

BNum BNum::operator +(const int Num)
{
    //first we create a temp BNum with that int then add
    BNum tNum(Num);
    BNum first;
    first = *this;
    return first+tNum;
}


BNum BNum::operator -(const int Num)
{
    //first we create a temp BNum with that int then minus
    BNum tNum(Num);
    BNum first;
    first = *this;
    return first-tNum;
}

BNum BNum::operator -(const BNum &other)
{
    BNum result(0);
    BNum first=*this;
    BNum second=other;
    int state=normalCompare(first,second);

    //now we want minus second from first
    //maybe the nums are neg or positive
    //4 state:
    //1: first is neg & second are positve.
    //add twe nums and the sign of result is neg
    //2: first is positive & second are negetive:
    //add twe num and the sign of resutl is positive
    //3: first and second are positive:
    //3-1:if first is bigger:
    //first - seocnd & the sign of result is positive
    //3-2:if second is bigger:
    //second - first & the sign of result is negetive
    //4: first and second are negetive:
    //4-1:if first is bigger:
    //first-second & the sign of result is negetive
    //4-2:if second is bigger:
    //second-first & the sign of result is positive

    //if i said first- second it means normal minus with twe positive

    //1:
    if(first.sign==false && second.sign==true)
    {
        result=normalPlus(first,second);
        result.sign=false;
    }
    //2:
    else if(first.sign==true && second.sign==false)
    {
        result=normalPlus(first,second);
        result.sign=true;
    }
    //3:
    else if(first.sign==true && second.sign==true)
    {
        if(state==1 || state==0)//first is bigger or equal (equal contains just for true for result.sign)
        {
            result=normalMinus(first,second);
            result.sign=true;
        }
        else//second is bigger
        {
            result=normalMinus(second,first);
            result.sign=false;
        }
    }
    //4:
    else if(first.sign==true && second.sign==true)
    {
        if(state==1)//first is bigger
        {
            result=normalMinus(first,second);
            result.sign=false;
        }
        else//second is bigger or equal
        {
            result=normalMinus(second,first);
            result.sign=true;
        }
    }
    return result;
}


BNum BNum::operator *(const BNum &other)
{
    BNum result(0);
    BNum first=*this;
    BNum second=other;
    for(int i=0;i<second.size;i++)//lets mult every second digits to first
    {
        result = result + (first.multByOneDigit(toInt(second.digits[i]))).addZero(i);
    }
    result.sign=!(first.sign ^ second.sign);
    return result;
}

BNum BNum::operator /(const BNum &other)
{

    BNum result(0);
    BNum first=*this;
    BNum second=other;
    bool tempSign;
    BNum i(0);
    tempSign=!(first.sign ^ second.sign);
    first.sign=true;//select the sign to true for normalDivition
    second.sign=true;
    result=normalDivide(first,second);
    result.sign=tempSign;
    return result;
}

void BNum::operator=(const QString& Str)
{
    QString str=Str;
    if(str[0]=='+')
    {
        this->sign=true;
        str=str.mid(1); //just del the sign
    }
    else if(str[0]=='-')
    {
        this->sign=false;
        str=str.mid(1); //just del the sign
    }
    else
    {
        this->sign=true;
    }

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
    //convert int to string:
    QString str;
    str=QString::number(Num);


    //this if select the sign
    if(str[0]=='+')
    {
        this->sign=true;
        str=str.mid(1); //just del the sign
    }
    else if(str[0]=='-')
    {
        this->sign=false;
        str=str.mid(1); //just del the sign
    }
    else
    {
        this->sign=true;
    }

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

bool BNum::operator ==(const BNum &other)
{
    if(this->sign!=other.sign)
        return false;
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
    BNum result(0);
    BNum Zero(0);
    BNum first=*this;
    BNum second=other;
    result=first-second;
    if(result==Zero)
        return false;
    else if(result.sign==false)
        return true;
    else if(result.sign==true)
        return false;
}

bool BNum::operator >(const BNum &other)
{
    BNum result(0);
    BNum Zero(0);
    BNum first=*this;
    BNum second=other;
    result=first-second;
    if(result==Zero)
        return false;
    else if(result.sign==true)
        return true;
    else if(result.sign==false)
        return false;
}

bool BNum::operator <=(const BNum &other)
{
    BNum result(0);
    BNum Zero(0);
    BNum first=*this;
    BNum second=other;
    result=first-second;
    if(result==Zero)
        return true;
    else if(result.sign==false)
        return true;
    else if(result.sign==true)
        return false;
}

bool BNum::operator >=(const BNum &other)
{
    BNum result(0);
    BNum Zero(0);
    BNum first=*this;
    BNum second=other;
    result=first-second;
    if(result==Zero)
        return true;
    else if(result.sign==true)
        return true;
    else if(result.sign==false)
        return false;
}
bool BNum::operator !=(const BNum &other)
{
    if(*this == other)
        return false;
    return true;
}

BNum BNum::operator ^(const BNum &other)
{
    BNum result(1);
    BNum i(0);
    BNum first=*this;
    BNum second=other;
    if(first==i)//0^i -->0
        return i;
    if(first==result)//1^i -->1
    {
        return result;
    }
    if(!second.sign)//i^j that j is negetive is not integer.
        return i;

    //    first=*this;
    while(i!=second)
    {
        result=result * first;
        i++;
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
//        qDebug()<<i;
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
    BNum result(0);//why we use zero here app crash
    BNum tBNum(0);
    //result size
    for(int i=0;i<this->size;i++)
    {
        //we can't multiply with pow(10,i) because of range of int ! so use add zero
        tBNum=d*toInt(this->digits[i]);
        result=result + tBNum.addZero(i);
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
    if(! this->sign)
        tempStr+="-";
    qDebug()<<"The size is : "<<this->size;

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




