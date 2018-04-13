#include <iostream>
#include <vector>
#include <string>
#include <map>
#define NUM 2
using namespace std;
typedef struct Node
{
    string add_fore;
    char ch;
    friend bool operator==(const Node &node1, const Node &node2)
    {
        return ((node1.add_fore == node2.add_fore) && (node1.ch == node2.ch));
    }
    friend bool operator!=(const Node &node1, const Node &node2)
    {
        return !((node1.add_fore == node2.add_fore) && (node1.ch == node2.ch));
    }
    friend bool operator<(const Node &n1, const Node &n2)
    {
        if (n1.add_fore < n2.add_fore)
            return true;
        if (n1.add_fore == n2.add_fore)
            if (n1.ch < n2.ch)
                return true;
        return false;
    }
}Node;
int main(void)
{
    map<string, char> value_fore;
    map<Node, string> value_back;
    string start[NUM];
    string startcopy[NUM];
    int letter_num;
    vector< vector<Node> > word;
    for (int i = 0; i < NUM; i++)
    {
        vector<Node> temp;
        temp.clear();
        word.push_back(temp);
    }
    cin >> start[0] >> start[1] >> letter_num;
    startcopy[0] = start[0];
    startcopy[1] = start[1];
    for (int i = 0; i < letter_num; i++)
    {
        string add_start, add_end, letter;
        cin >> add_start >> letter >> add_end;
        Node temp = {add_start, letter[0]};
        value_fore[add_start] = letter[0];
        value_back[temp] = add_end;
    }
    while (start[0] != "-1" || start[1] != "-1")
    {
        //cout << "pause" << endl;
        for (int i = 0; i < NUM; i++)
        {
            if (start[i] == "-1")
                continue;
            Node temp = {start[i], value_fore[start[i]]};
            word[i].push_back(temp);
            for (map<Node, string>::iterator it = value_back.begin(); it != value_back.end(); it++)
            {
                if (it->first == temp)
                {
                    start[i] = it->second;
                }
            }
            //cout << i << ":" << start[i] << endl;
        }
        //system("pause");
    }
    /*
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < word[i].size(); j++)
        {
            cout << word[i][j].ch;
        }
        cout << endl;
    }*/
    while (true)
    {
        for (int i = 0; i < NUM - 1; i++)
        {
            if (word[i].size() == 0)
            {
                cout << startcopy[i] << endl;
                return 0;
            }
            if (word[i + 1].size() == 0)
            {
                cout << startcopy[i + 1] << endl;
                return 0;
            }
            if (word[i][word[i].size() - 1] != word[i + 1][word[i + 1].size() - 1])
            {
                cout << value_back[word[i][word[i].size() - 1]] << endl;
                return 0;
            }
            word[i].pop_back();
        }
        word[NUM - 1].pop_back();
    }
}