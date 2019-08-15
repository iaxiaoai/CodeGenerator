#include "category.h"


void 				Category::setId(QString a){this->Id = a;}
void 				Category::setName(QString a){this->Name = a;}
void 				Category::setLevel(QString a){this->Level =a;}
void 				Category::setPid(QString a){this->Pid = a;}
QString 			Category::getId(){return this->Id;}
QString 			Category::getName(){return this->Name;}
QString 			Category::getLevel(){return this->Level;}
QString 			Category::getPid(){return this->Pid;}
Category::Category()
{
}
