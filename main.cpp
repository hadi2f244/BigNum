#include <QCoreApplication>
#include <bnum.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //    BNum first("77");
    BNum result;
    BNum first("53");
    BNum second("52");

   first.test();


//    result=BNum::factorial(400);//just can calculate until 500!
//    result=first * second;
//    result=first - second;
    result.printLog();
    return a.exec();
}
