#include "Epoch.h"

int Epoch::currentId = 1;

Epoch::Epoch(std::string name, int day1, int month1, int year1, int day2, int month2, int year2)
{
    this->epochName = name;
    this->id = currentId;
    currentId++;

    initDate = {0};
    endDate  = {0};

    initDate.tm_mday = day1;
    initDate.tm_mon = month1-1;
    initDate.tm_year = year1-1900;
    initDate.tm_wday = getWeekDay(day1,month1,year1);

    endDate.tm_mday = day2;
    endDate.tm_mon = month2-1;
    endDate.tm_year = year2-1900;
    endDate.tm_wday = getWeekDay(day2,month2,year2);

    numDays = (mktime(&endDate) - mktime(&initDate)) / (24*60*60) + 1;

    global = NULL;
}

int Epoch::getNumdays() const
{
    return numDays;
}

std::string Epoch::getName() const{
    return this->epochName;
}

int Epoch::getId() const{
    return id;
}

void Epoch::addSubscription(Subscription *s) {

    subs.push_back(s);
}

void Epoch::setSchedule(Schedule *pSchedule) {
    this->global = pSchedule;
}

std::vector<Subscription *> Epoch::getSubscriptions() const{
    return this->subs;
}

std::vector<string> Epoch::getStudentExams(string student)
{
    vector<string> exams;

    for (unsigned int i = 0; i < subs.size(); ++i)
    {
        string name = subs.at(i)->getStudent()->getName();

        if(name == student)
            exams.push_back(subs.at(i)->getExam()->getClassName());
    }

    return exams;
}

vector<Student *> Epoch::getStudents(Exam *e) const {
    vector<Student *> students;

    for (unsigned int i = 0; i < subs.size(); ++i)
    {
        Student *s = subs.at(i)->getStudent();
        if(subs.at(i)->getExam() == e)
            if(notFound(students,s))
                students.push_back(s);
    }
    return students;
}

std::vector<Exam *> Epoch::getExams() const {
    vector<Exam *> exams;

    for (unsigned int i = 0; i < subs.size(); ++i)
    {
        Exam *e = subs.at(i)->getExam();
        if(notFound(exams, e))
            exams.push_back(e);
    }
    return exams;
}

int Epoch::getWeekDay(int d, int m, int y)
{
    return (d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1) % 7;
}

struct tm Epoch::getInitDate() const{
    return initDate;
}

Schedule * Epoch::getSchedule(){
    return global;
}

template<typename T>
bool Epoch::notFound(vector<T *> vector, T *temp) const {
    for (unsigned int i = 0; i < vector.size(); ++i)
        if(vector.at(i) == temp)
            return false;
    return true;
}

bool Epoch::deleteStudent(string examName, string studentName)
{
    for(unsigned int j = 0; j < this->getSubscriptions().size(); j++){
        Subscription * currentSub = this->getSubscriptions()[j];
        if(currentSub->getExam()->getClassName() == examName && currentSub->getStudent()->getName() == studentName){
            this->subs.erase(subs.begin()+j);
            return true;
        }
    }
    return false;
}

bool Epoch::addStudentExam(Student * student, Exam * exam ){
    this->subs.push_back(new Subscription(student, exam));
}

void Epoch::setInitDate(int year, int month, int day)
{
    initDate.tm_mday = day;
    initDate.tm_mon = month-1;
    initDate.tm_year = year-1900;
    initDate.tm_wday = getWeekDay(day,month,year);

    numDays = (mktime(&endDate) - mktime(&initDate)) / (24*60*60) + 1;
}

void Epoch::setEndDate(int year, int month, int day)
{
    endDate.tm_mday = day;
    endDate.tm_mon = month-1;
    endDate.tm_year = year-1900;
    endDate.tm_wday = getWeekDay(day,month,year);

    numDays = (mktime(&endDate) - mktime(&initDate)) / (24*60*60) + 1;
}
