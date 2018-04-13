#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

class TableTennis;
class People
{
friend class TableTennis;
friend bool comp(const People &p1, const People &p2);
private:
    int index;
    int start_time;
    int duration;
    int end_time;
    bool isVIP;
public:
    People(int i, string start, int dur, bool vip) : index(i), duration(dur), isVIP(vip)
    {
        int sum = 0;
        for (int i = 0; i < 3; i++)
        {
            sum *= 60;
            sum += (start[i * 3] - '0') * 10 + start[i * 3 + 1] - '0';
            //cout << sum << endl;
        }
        start_time = sum;
    }
    bool operator<(const People &other)
    {
        return start_time < other.start_time;
    }
};

bool comp(const People &p1, const People &p2)
{
    return p1.end_time < p2.end_time;
}

class TableTennis
{
private:
    int open_time, close_time;
    int people_num, table_num, vip_table_num;
    int *table_end_time;
    int *table_count;
    bool *is_vip_table;
    bool *vip_table_empty;
    vector<People> guest;
    vector<int> VIP;
public:
    TableTennis() : open_time(8 * 60 * 60), close_time(21 * 60 * 60) {}
    void input()
    {
        cin >> people_num;
        for (int i = 0; i < people_num; i++)
        {
            string start;
            int dur;
            bool vip;
            cin >> start >> dur >> vip;
            dur = min(dur, 120);
            if (start[0] == '0' && start[1] < '8')
            {
                people_num--;
                continue;
            }
            guest.push_back(People(i, start, dur * 60, vip));
            if (vip == true)
            {
                VIP.push_back(i);
            }
            //cout << guest[i].start_time << endl;
        }
        cin >> table_num >> vip_table_num;
        table_end_time = new int[table_num];
        is_vip_table = new bool[table_num];
        table_count = new int[table_num];
        for (int i = 0; i < table_num; i++)
        {
            table_end_time[i] = open_time;
            is_vip_table[i] = false;
            table_count[i] = 0;
        }
        for (int i = 0; i < vip_table_num; i++)
        {
            int temp;
            cin >> temp;
            is_vip_table[temp - 1] = true;
        }
    }
    int find_early_end(bool isVIP = false)
    {
        int min_index = 0;
        for (int i = 0; i < table_num; i++)
        {
            if (table_end_time[i] < table_end_time[min_index])
            {
                min_index = i;
            }
        }
        return min_index;
    }
    void process()
    {
        sort(guest.begin(), guest.end());
        int flag = 0;
        for (vector<People>::iterator it = guest.begin(); it != guest.end(); it++)
        {
            it->index = flag++;
        }
        int VIP_num = 0;
        vector<People>::iterator begin_pos = guest.begin();
        vector<int> arrive_guest; // record guest in queue's index
        map<int, int> VIP_pos; // record vip position in queue
        for (int i = 0; i < people_num; i++)
        {
            int early_end = find_early_end();
            table_count[early_end]++;
            vector<People>::iterator it;
            for (it = begin_pos; it != guest.end(); it++)
            {
                if (it->start_time >= table_end_time[early_end])
                {
                    break;
                }
                arrive_guest.push_back(it->index);
                //cout << it->duration << " ";
                if (it->isVIP == true)
                {
                    VIP_pos[it->index] = arrive_guest.size() - 1;
                    VIP_num++;
                }
            }
            begin_pos = it;
            //cout << endl;
            if (arrive_guest.empty())
            {
                begin_pos->end_time = begin_pos->start_time;
                if (begin_pos->end_time >= close_time)
                    table_count[early_end]--;
                int temp = -1;
                for (int i = 0; i < table_num; i++)
                {
                    if (table_end_time[i] <= begin_pos->start_time)
                    {
                        temp = i;
                        break;
                    }
                }
                if (begin_pos->isVIP == true)
                {
                    for (int i = 0; i < table_num; i++)
                    {
                        if (is_vip_table[i] == true && table_end_time[i] <= begin_pos->start_time)
                        {
                            temp = i;
                            break;
                        }   
                    }
                }
                if (temp != -1)
                {
                    table_end_time[temp] = begin_pos->end_time + begin_pos->duration;
                    table_count[temp]++;
                    table_count[early_end]--;
                }
                begin_pos++;
            }
            else
            {
                vector<int>::iterator current_pos;
                if (is_vip_table[early_end] == true && VIP_num != 0)
                {
                    for (vector<int>::iterator it = arrive_guest.begin(); it != arrive_guest.end(); it++)
                    {
                        if (guest[*it].isVIP == true)
                        {
                            current_pos = it;
                            break;
                        }
                    }
                    /*
                    current_pos = arrive_guest.begin() + VIP_pos.begin()->second;
                    VIP_pos.erase(VIP_pos.begin());
                    for (map<int, int>::iterator it = VIP_pos.begin(); it != VIP_pos.end(); it++)
                    {
                        it->second--;
                    }*/
                    VIP_num--;
                }
                else
                {
                    current_pos = arrive_guest.begin();
                }
                guest[*current_pos].end_time = table_end_time[early_end];
                if (guest[*current_pos].end_time >= close_time)
                    table_count[early_end]--;
                table_end_time[early_end] += guest[*current_pos].duration;
                arrive_guest.erase(current_pos);
            }
        }
    }
    void convertTime(int t)
    {
        cout << setw(2) << setfill('0') << t / 3600 << ":";
        cout << setw(2) << setfill('0') << t / 60 - static_cast<int>(t / 3600) * 60 << ":";
        cout << setw(2) << setfill('0') << t % 60 << " ";
    }
    void print()
    {
        sort(guest.begin(), guest.end(), comp);
        for (vector<People>::iterator it = guest.begin(); it != guest.end(); it++)
        {
            if (it->end_time >= close_time)
            {
                break;
            }
            convertTime(it->start_time);
            convertTime(it->end_time);
            cout << (it->end_time - it->start_time + 30) / 60 << endl;
        }
        for (int i = 0; i < table_num; i++)
        {
            if (i) cout << " ";
            cout << table_count[i];
        }
        cout << endl;
    }
};
int main(void)
{
    TableTennis t;
    t.input();
    t.process();
    t.print();
    return 0;
}