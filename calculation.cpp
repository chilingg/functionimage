#include "calculation.h"
#include <QDebug>
#include <QRegExp>

Calculation::Calculation(QString str):
    funcStr(str),
    status(false),
    x(2)//构造时用于测试
{
    str = str.remove(QRegExp("\\s"));
    if(str.isEmpty())
        return;

    try{
        //查看是否都是合法字符
        QRegExp reg("[\\d+-/*()^]*x[\\d+-/*()x^]*");
        if(!reg.exactMatch(str))
            throw "Calculation: unexpected character: " + str;

        calculating(str);
        status = true;
    }
    catch(const QString &msg)
    {
        qDebug() << msg;
        status = false;
    }
}

Calculation::Calculation(const char *c):
    Calculation(QString(c))
{
    
}

double Calculation::operator()(double input)
{
    if(status)
    {
        x = input;
        QString str = funcStr;
        input = calculating(str);
    }
    return  input;
}

double Calculation::calculating(QString &str)
{
    //若有括号则先处理
    QRegExp reg("([\\dx]?)\\(([^\\(\\)]+)\\)([\\dx]?)");
    int index = reg.indexIn(str);
    while(index != -1)
    {
        if(!reg.cap(1).isEmpty() || !reg.cap(3).isEmpty())
            throw "Bad parentheses: " + reg.cap();

        QString inParentheses = reg.cap(2);
        QString result = QString::number(calculating(inParentheses), 'f', 2);
        str.replace(index, reg.cap(2).size()+2, result);
        index = reg.indexIn(str);

    }

    //第一个项
    double value = 0;
    value += popFristTermValue(str);

    //若有一个以上的项
    while(!str.isEmpty())
    {
        char operater = str.front().toLatin1();
        str = str.mid(1);
        if(operater == '+')
            value += calculating(str);
        else if(operater == '-')
            value -= calculating(str);
        else if(operater == '*')
            value *= popFristTermValue(str);
        else if(operater == '/')
            value /= popFristTermValue(str);
        else
            throw "Operator Error: " + str;
    }

    return value;
}

double Calculation::popFristTermValue(QString &str)
{
    //获取第一个项
    double value = 0;
    QRegExp reg("(-?)((\\d+(?:\\.\\d+)?)?x|\\d+(?:\\.\\d+)?)(\\^\\d)?");
    int index = reg.indexIn(str);//能否从开头匹配第一个项
    if(index != 0)
        throw "Term Error: " + str;
    str = reg.cap().size() == str.size() ? "" : str.mid(reg.cap().size());

    //是否包含未知数
    if(reg.cap(2).back() == 'x')
    {
        value = x;
        if(!reg.cap(1).isEmpty() && reg.cap(3).isEmpty())//符号是否在未知数前
            value = -value;
        if(!reg.cap(4).isEmpty())//指数
        {
            double power = 1;
            for(int i = reg.cap(4).mid(1).toInt(); i > 0; --i)
                power *= value;
            value = power;
        }
        if(!reg.cap(3).isEmpty())//倍数
        {
            value *= reg.cap(3).toDouble();
            if(!reg.cap(1).isEmpty())
                value = -value;
        }
    }
    else
    {
        value = reg.cap(2).toDouble();
        if(!reg.cap(1).isEmpty())
            value = -value;
        if(!reg.cap(4).isEmpty())//指数
        {
            double power = 1;
            for(int i = reg.cap(4).mid(1).toInt(); i > 0; --i)
                power *= value;
            value = power;
        }
    }
    return value;
}
