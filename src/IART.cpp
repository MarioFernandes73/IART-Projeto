//============================================================================
// Name        : IART.cpp
// Author      : Catarina Ramos, Ines Gomes and Mario Fernandes
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <sstream>

#include "Database.h"
#include "University.h"
#include "Genetic.h"
#include "SimulatedAnnealing.h"
#include "mainwindow.h"
#include <QApplication>

using namespace std;

vector<Student *> loadStudents(vector<vector<string>> studentsInfo);
vector<Exam *> loadExams(vector<vector<string>> examsInfo);
void loadSubscriptions(vector<vector<string>> subscribeInfo, University * university);

int main(int argc, char* argv[]) {

    //random numbers
    srand ((unsigned int) time(NULL));

    // database variables
    Database *db;

    char *filename = (char *) "../iart.db";         // QT
    //char *filename = (char *) "../proj/iart.db";  //clion
    //char * filename = (char*)"iart.db";           //eclipse

    char *selectStudentQuery = (char *) "SELECT * FROM Student";
    char *selectExamQuery = (char *) "SELECT * FROM Exam";
    char *selectSubscribeQuery = (char *) "SELECT * FROM Subscription";

    // database operations
    db = new Database(filename);
    db->open();

    //load students and exams
    vector<Student *> students = loadStudents(db->query(selectStudentQuery));
    vector<Exam *> exams = loadExams(db->query(selectExamQuery));

    // university initialization and epoch
    University * university = new University(students,exams);
    Epoch * e = new Epoch("Normal",8,5,2017,26,5,2017);
    university->addEpoch(e);

    //load subscriptions of students to exams
    loadSubscriptions(db->query(selectSubscribeQuery), university);

    db->close();

    //interface
    //initialOptions(university);

    //TESTE

   //genetic algorithm
    Genetic algorithm1(e,false,40);
    algorithm1.run();

   /* //Simulated Annealing
    SimulatedAnnealing algorithm2(e,false,20,30);
    algorithm2.run();*/

    //save .db

    //Qt setup
    QApplication a(argc, argv);
    MainWindow w;
    w.setUniversity(university);
    w.show();

    return a.exec();
}

//read students
vector<Student *> loadStudents(vector<vector<string>> studentsInfo)
{
    vector<Student *> students;

    for (vector<vector<string> >::iterator it = studentsInfo.begin(); it < studentsInfo.end(); ++it)
    {
        int student_id;
        string name;
        stringstream ss;

        for (vector<string>::iterator it2 = (*it).begin(); it2 < (*it).end(); it2++)
            ss << (*it2);

        ss >> student_id >> name;

        students.push_back(new Student(student_id, name));
    }

    return students;
}

 //read exams
vector<Exam *> loadExams(vector<vector<string>> examsInfo)
{
    vector<Exam *> exams;

    for (vector<vector<string> >::iterator it = examsInfo.begin(); it < examsInfo.end(); ++it)
    {
        int exam_id, year;
        string className;
        stringstream ss;

        for (vector<string>::iterator it2 = (*it).begin(); it2 < (*it).end(); it2++)
            ss << (*it2);

        stringstream ss2;
        ss2 << ss.str().at(ss.str().length()-1);
        ss2 >> year;
        ss2.clear();
        ss2.str("");
        string temp = ss.str();
        temp.erase(temp.length()-1);
        ss2 << temp;
        ss2 >> exam_id >> className;

        exams.push_back(new Exam(exam_id, Class(className,year)));
    }

    return exams;
}

//read subscribes
void loadSubscriptions(vector<vector<string>> subscribeInfo, University * university)
{
    for (vector<vector<string> >::iterator it = subscribeInfo.begin(); it < subscribeInfo.end(); ++it)
    {
        int exam_id = 0, student_id = 0, epoch_id = 0;
        char c;
        stringstream ss;

        for (vector<string>::iterator it2 = (*it).begin(); it2 < (*it).end(); it2++)
            ss << (*it2) << ",";

        ss >> epoch_id >> c >> exam_id >> c >> student_id;

        university->addSubscription(epoch_id,exam_id,student_id);
    }
}
