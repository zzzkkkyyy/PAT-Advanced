#include <iostream>
#include <algorithm>
using namespace std;
class Sort
{
private:
    int num;
    int *array;
    int *part_sort;
public:
    void init()
    {
        cin >> num;
        array = new int[num];
        part_sort = new int[num];
        for (int i = 0; i < num; i++)
        {
            cin >> array[i];
        }
        for (int i = 0; i < num; i++)
        {
            cin >> part_sort[i];
        }
    }
    bool equalSeq(int *arr, int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            if (arr[i] != part_sort[i])
            {
                return false;
            }
        }
        return true;
    }
    int isInsertion()
    {
        int pos;
        int *copy = new int[num];
        for (int i = 0; i < num; i++)
        {
            copy[i] = array[i];
        }
        for (int i = 2; i < num; i++)
        {
            sort(copy, copy + i);
            if (equalSeq(copy, 0, num) == true)
            {
                sort(copy, copy + i + 1);
                cout << "Insertion Sort" << endl;
                for (int j = 0; j < num; j++)
                {
                    if (j)
                        cout << " ";
                    cout << copy[j];
                }
                delete []copy;
                return i;
            }
        }
        delete []copy;
        cout << "Merge Sort" << endl;
        return -1;
    }
    void continueSort()
    {
        int mode = isInsertion();
        int iteration = 2;
        if (mode == -1)
        {
            bool flag = false;
            while (true)
            {
                for (int i = 0; i < num / iteration; i++)
                {
                    sort(array + i * iteration, array + (i + 1) * iteration);
                }
                sort(array + num / iteration * iteration, array + num);
                if (equalSeq(array, 0, num) == true)
                {
                    flag = true;
                }
                else if (flag == true)
                {
                    for (int i = 0; i < num; i++)
                    {
                        if (i)
                            cout << " ";
                        cout << array[i];
                    }
                    break;
                }
                iteration *= 2;
            }
        }
        cout << endl;
    }
};
int main(void)
{
    Sort s;
    s.init();
    s.continueSort();
    return 0;
}