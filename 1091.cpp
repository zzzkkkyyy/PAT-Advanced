#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
typedef struct Point
{
    int x, y, z;
}Point;
class Stroke
{
private:
    int length, width, height, threshold;
    bool ***volumn;
    int sum;
    queue<Point> q;
public:
    void init()
    {
        sum = 0;
        cin >> width >> length >> height >> threshold;
        volumn = new bool **[height];
        for (int i = 0; i < height; i++)
        {
            volumn[i] = new bool *[width];
            for (int j = 0; j < width; j++)
            {
                volumn[i][j] = new bool[length];
                for (int k = 0; k < length; k++)
                {
                    bool temp;
                    cin >> temp;
                    volumn[i][j][k] = temp;
                }
            }
        }
    }
    void BFS()
    {
        int part_sum = 1;
        while(!q.empty())
        {
            int x = (q.front()).x;
            int y = (q.front()).y;
            int z = (q.front()).z;
            volumn[z][y][x] = false;
            //cout << x << " " << y << " " << z << endl;
            //getchar();
            if (x != 0)
            {
                if (volumn[z][y][x - 1] == true)
                {
                    Point temp = {x - 1, y, z};
                    volumn[z][y][x - 1] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            if (x != length - 1)
            {
                if (volumn[z][y][x + 1] == true)
                {
                    Point temp = {x + 1, y, z};
                    volumn[z][y][x + 1] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            if (y != 0)
            {
                if (volumn[z][y - 1][x] == true)
                {
                    Point temp = {x, y - 1, z};
                    volumn[z][y - 1][x] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            if (y != width - 1)
            {
                if (volumn[z][y + 1][x] == true)
                {
                    Point temp = {x, y + 1, z};
                    volumn[z][y + 1][x] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            if (z != 0)
            {
                if (volumn[z - 1][y][x] == true)
                {
                    Point temp = {x, y, z - 1};
                    volumn[z - 1][y][x] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            if (z != height - 1)
            {
                if (volumn[z + 1][y][x] == true)
                {
                    Point temp = {x, y, z + 1};
                    volumn[z + 1][y][x] = false;
                    q.push(temp);
                    part_sum++;
                }
            }
            q.pop();
        }
        //cout << part_sum << endl;
        if (part_sum >= threshold)
        {
            sum += part_sum;
        }
    }
    void process()
    {
        for (int k = 0; k < height; k++)
        {
            for (int j = 0; j < width; j++)
            {
                for (int i = 0; i < length; i++)
                {
                    if (volumn[k][j][i] == true)
                    {
                        Point temp = {i, j, k};
                        q.push(temp);
                        BFS();
                    }
                }
            }
        }
        cout << sum << endl;
    }
};
int main(void)
{
    Stroke stroke;
    stroke.init();
    stroke.process();
    //system("pause");
    return 0;
}