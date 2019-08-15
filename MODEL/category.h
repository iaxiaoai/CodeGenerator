#ifndef CATEGORY_H
#define CATEGORY_H
#include "UTILS/includes.h"
class Category
{
public:
    Category();

    void setId(QString a);
    void setName(QString a);
    void setLevel(QString a);
    void setPid(QString a);


    QString getId();
    QString getName();
    QString getLevel();
    QString getPid();
private:
    QString Id;
    QString Name;
    QString Level;
    QString Pid;

};

#endif // CATEGORY_H
