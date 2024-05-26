#include <bits/stdc++.h>
#include <fstream>
using namespace std;


void readdata1(string &id, string &temp, int &cr)
{
    while (temp[cr] != ',')
    {
        id += temp[cr++];
    }
    cr++;
}

void readdata2(vector<string> &id, string &temp, int &cr)
{
    while (true)
    {
        string course = "";
        while (temp[cr] != ',' && temp[cr] != ']')
        {
            course += temp[cr++];
        }
        id.push_back(course);

        if (temp[cr] == ']')
            break;
        cr++;
    }
    cr++;
}

class LinkedList;
int number = 0;

class StudentRecord
{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName()
    {
        return studentName;
    }
    void set_studentName(string Name)
    {
        studentName = Name;
    }
    string get_rollNumber()
    {
        return rollNumber;
    }
    void set_rollNumber(string rollnum)
    {
        rollNumber = rollnum;
    }
};

vector<StudentRecord> students(500);

class Node
{
private:
    Node *next = NULL;
    StudentRecord *element = NULL;

public:
    Node *get_next()
    {
        return next;
    }
    StudentRecord *get_element()
    {
        return element;
    }

    void set_next(Node *value)
    {
        next = value;
    }
    void set_element(StudentRecord *student)
    {
        element = student;
    }
};

class Entity
{
private:
    string name;
    Node *iterator = NULL;

public:
    string get_name()
    {
        return name;
    }
    void set_name(string Name)
    {
        name = Name;
    }
    Node *get_iterator()
    {
        return iterator;
    }
    void set_iterator(Node *iter)
    {
        iterator = iter;
    }
};

class LinkedList : public Entity
{
    // Implement LinkedList members here

public:
    void read_add()
    {
        Node *curr = this->get_iterator();

        while (curr->get_next() != NULL)
        {
            curr = curr->get_next();
        }

        Node *n1 = new Node;
        n1->set_element(&students[number - 1]);
        curr->set_next(n1);
    }
    void add_student(StudentRecord student)
    {
        for (auto &i : students)
        {
            if (student.get_studentName() == i.get_studentName() && student.get_rollNumber() == i.get_rollNumber())
            {
                // cout << "same  ";
                Node *curr = this->get_iterator();
                if (curr == NULL)
                {
                    Node *n1 = new Node;
                    n1->set_element(&i);
                    this->set_iterator(n1);
                    return;
                }
                while (curr->get_next() != NULL)
                {
                    curr = curr->get_next();
                }

                Node *n1 = new Node;
                n1->set_element(&i);
                curr->set_next(n1);

                return;
            }
        }

        students[number] = student;
        number++;

        Node *curr = (*this).get_iterator();
        if (curr == NULL)
        {
            Node *n1 = new Node;
            n1->set_element(&students[number - 1]);
            (*this).set_iterator(n1);
            return;
        }
        while (curr->get_next() != NULL)
        {
            curr = curr->get_next();
        }

        Node *n1 = new Node;
        n1->set_element(&students[number - 1]);
        curr->set_next(n1);

        return;
    }

    void delete_student(string studentName)
    {

        auto &i = (*this);

        Node *curr = i.get_iterator();

        if (curr->get_element()->get_studentName() == studentName)
        {
            Node *temp = curr->get_next();
            delete curr;
            i.set_iterator(temp);
        }
        else
        {
            while (curr->get_next() != NULL && curr->get_next()->get_element()->get_studentName() != studentName)
            {
                curr = curr->get_next();
            }

            if (curr->get_next() != NULL)
            {
                Node *temp = curr->get_next()->get_next();

                delete curr->get_next();

                curr->set_next(temp);
            }
        }
    }
};

vector<LinkedList> EntityArray;

void read_input_file(string path)
{
    fstream readdata;

    readdata.open(path, ios::in);

    string temp;

    while (readdata >> temp)
    {
        string Name, RollNo, Deparment, Hostel;
        vector<string> Courses, Clubs;

        int cr = 0;
        Name = "";
        readdata1(Name, temp, cr);

        RollNo = "";
        readdata1(RollNo, temp, cr);

        Deparment = "";
        readdata1(Deparment, temp, cr);

        cr++;
        readdata2(Courses, temp, cr);
        cr++;

        cr++;
        Hostel = "";
        readdata1(Hostel, temp, cr);

        cr++;
        readdata2(Clubs, temp, cr);

        students[number].set_studentName(Name);
        students[number].set_rollNumber(RollNo);
        number++;

        bool hostel = 0;
        bool department = 0;
        vector<bool> courses(Courses.size(), 0);
        vector<bool> clubs(Clubs.size(), 0);

        for (auto &i : EntityArray)
        {
            if (i.get_name() == Hostel)
            {
                i.read_add();
                hostel = 1;
            }

            if (i.get_name() == Deparment)
            {
                i.read_add();
                department = 1;
            }

            for (int j = 0; j < Courses.size(); ++j)
            {
                if (i.get_name() == Courses[j])
                {
                    i.read_add();
                    courses[j] = 1;
                }
            }

            for (int j = 0; j < Clubs.size(); ++j)
            {
                if (i.get_name() == Clubs[j])
                {
                    i.read_add();
                    clubs[j] = 1;
                }
            }
        }

        if (!hostel)
        {

            LinkedList e1;
            e1.set_name(Hostel);
            Node *n1 = new Node;
            n1->set_element(&students[number - 1]);
            e1.set_iterator(n1);
            EntityArray.push_back(e1);
        }

        if (!department)
        {
            LinkedList e1;
            e1.set_name(Deparment);
            Node *n1 = new Node;
            n1->set_element(&students[number - 1]);
            e1.set_iterator(n1);
            EntityArray.push_back(e1);
        }

        for (int j = 0; j < Courses.size(); ++j)
        {
            if (!courses[j])
            {
                LinkedList e1;
                e1.set_name(Courses[j]);
                Node *n1 = new Node;
                n1->set_element(&students[number - 1]);
                e1.set_iterator(n1);
                EntityArray.push_back(e1);
            }
        }

        for (int j = 0; j < Clubs.size(); ++j)
        {
            if (!clubs[j])
            {
                LinkedList e1;
                e1.set_name(Clubs[j]);
                Node *n1 = new Node;
                n1->set_element(&students[number - 1]);
                e1.set_iterator(n1);
                EntityArray.push_back(e1);
            }
        }
    }
}
