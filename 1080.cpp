// two questions: 
// how to access members of vector<Applicant> in Exam
// friend compare function

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Applicant
{
    int index;
    int ge, gi;
    int choice_num;
    vector<int> priority;

    Applicant() {}
    Applicant(int choose, int i) : choice_num(choose), index(i)
    {
        ge = gi = 0;
        priority.clear();
    }
    void insertInfo()
    {
        cin >> ge >> gi;
        for (int i = 0; i < choice_num; i++)
        {
            int pri;
            cin >> pri;
            priority.push_back(pri);
        }
    }
}Applicant;

bool cmp(const Applicant &app1, const Applicant &app2)
{
    if ((app1.ge + app1.gi) * 1.0 / 2 > (app2.ge + app2.gi) * 1.0 / 2)
        return true;
    else if ((app1.ge + app1.gi) * 1.0 / 2 == (app2.ge + app2.gi) * 1.0 / 2)
        if (app1.ge > app2.ge)
            return true;
    return false;
}

class Exam
{
private:
    int appli_num, college_num, choice_num;
    vector<Applicant> applicant;
    vector<int> college_capacity;
    vector<vector<int> > college_receive;
    int *college_ge, *college_gi;
public:
    Exam() {}
    ~Exam() {}
    void init()
    {
        cin >> appli_num >> college_num >> choice_num;
        college_ge = new int[college_num];
        college_gi = new int[college_num];
        for (int i = 0; i < college_num; i++)
        {
            vector<int> temp;
            temp.clear();
            college_receive.push_back(temp);

            int cap;
            cin >> cap;
            college_capacity.push_back(cap);
        }
        for (int i = 0; i < appli_num; i++)
        {
            Applicant appli(choice_num, i);
            appli.insertInfo();
            applicant.push_back(appli);
        }
    }
    void receiveStu()
    {
        sort(applicant.begin(), applicant.end(), cmp);
        for (vector<Applicant>::iterator it = applicant.begin(); it != applicant.end(); it++)
        {
            cout << it->index << ": " << it->ge << ", " << it->gi << endl;
            for (vector<int>::iterator itp = ((*it).priority).begin(); itp != ((*it).priority).end(); itp++)
            {
                if (college_receive[*itp].size() < college_capacity[*itp])
                {
                    college_receive[*itp].push_back(it->index);
                    college_ge[*itp] = it->ge;
                    college_gi[*itp] = it->gi;
                    break;
                }
                else
                {
                    if (it->ge == college_ge[*itp] && it->gi == college_gi[*itp])
                    {
                        college_receive[*itp].push_back(it->index);
                        break;
                    }
                }
            }
        }
    }
    void print()
    {
        for (vector<vector<int> >::iterator it = college_receive.begin(); it != college_receive.end(); it++)
        {
            sort((*it).begin(), (*it).end(), less<int>());
            for (vector<int>::iterator iti = it->begin(); iti != it->end(); iti++)
            {
                if (iti != it->begin())
                {
                    cout << " ";
                }
                cout << *iti;
            }
            cout << endl;
        }
    }
};
int main(void)
{
    Exam exam;
    exam.init();
    exam.receiveStu();
    exam.print();
    return 0;
}