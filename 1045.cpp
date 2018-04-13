#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int find_str(vector<int> like, vector<int> current)
{
    vector<int>::iterator it;
    int max_length = 0;
    bool is_find = false;
    for (int i = 0; i < like.size(); i++)
    {
        it = find(current.begin(), current.end(), like[i]);
        if (it != current.end())
        {
            is_find = true;
            vector<int> current_copy = current;
            vector<int> like_copy = like;
            current.erase(current.begin(), it + 1);
            like.erase(like.begin(), like.begin() + i);
            int temp = 1 + find_str(like, current);
            like = like_copy;
            current = current_copy;
            if (temp > max_length)
                max_length = temp;
        }
        else
            continue;
    }
    if (is_find == false)
        return 0;
    else
        return max_length;
}
int main(void)
{
    int total_color_num, like_color_num, current_color_num;
    vector<int> like_color;
    vector<int> current_color;
    cin >> total_color_num >> like_color_num;
    int *like_color_sort = new int[200];
    for (int i = 0; i < like_color_num; i++)
    {
        int temp;
        cin >> temp;
        like_color.push_back(temp);
        like_color_sort[temp] = i + 1;
    }
    cin >> current_color_num;
    for (int i = 0; i < current_color_num; i++)
    {
        int temp;
        cin >> temp;
        if (find(like_color.begin(), like_color.end(), temp) != like_color.end())
            current_color.push_back(temp);
    }
    int *dp = new int[current_color.size()];
    int max = 0;
    for (int i = 0; i < current_color.size(); i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (like_color_sort[current_color[j]] <= like_color_sort[current_color[i]])
            {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max)
            max = dp[i];
    }
    cout << max << endl;
    //cout << find_str(like_color, current_color) << endl;
    return 0;
}