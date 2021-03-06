#ifndef UNIVERSITY_H_
#define UNIVERSITY_H_

#include <string>
#include "Epoch.h"

class University {
private:
    std::string name;
    std::vector<Exam *> exams;
    std::vector<Student *> students;
    std::vector<Epoch *> epochs;
public:
    University(std::vector<Student *> students,std::vector<Exam *> exams);
    virtual ~University() {}

    void addEpoch(Epoch * e);

    std::vector<Student *> getStudents();
    Student *findStudent(Student *tempStudent);
    void addStudent(Student *newStudent);
    void removeStudent(Student *oldStudent);

    std::vector<Exam *> getExams();
    Exam *findExam(Exam *tempExam);
    void addExam(Exam *newExam);
    void removeExam(Exam *oldExam);

    Epoch * getEpochByName(std::string name);
    std::vector<Epoch *> getEpochs();

    template<typename T>
    T* findById(vector<T*> vec, int id);
    void addSubscription(int epochId, int examId, int studentId);
    int getExamId(string examName);
    int getStudentId(string studentName);
    Epoch * deleteStudent(string studentName, string examName);
    Epoch * addStudentExam(string studentName, string examName);
};

#endif /* UNIVERSITY_H_ */
