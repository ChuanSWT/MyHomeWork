#include <iostream>
#include <vector>
#include<set>
using namespace std;

class meth {
public:
    vector<vector<int>> mark;
    vector<vector<int>> texts;
    vector<int> dx = { 1, 0, -1, 0 };
    vector<int> dy = { 0, 1, 0, -1 };
    //记忆化搜索 
    set<vector<vector<int>>> st;
    meth() {
        vector<vector<int>> temp(6, vector<int>(4, 0));
        temp[5][2] = 1; temp[5][3] = 1;
        mark = temp;
        vector<vector<int>> temp2 = {
            { 2, 1, 100, 200 },
            { 3, 4, 400, 300 },
            { 6, 5, 500, 600 },
            { 7, 8, 800, 700 },
            { 10, 9, 900, 1000 },
            { 11, 12, -1, -1 }
        };
        texts = temp2;
    }

    vector<vector<vector<int>>> ans;//存储路径集合，代表答案
    vector<vector<int>> path;//存储路径
    bool ret_now = false;//代表已经找到，要求立即返回

    void make(vector<vector<int>>& grid, int i, int j) {
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[0].size(); ++y) {
                if (texts[x][y] == i || texts[x][y] == j)
                    grid[x][y] = 1;
            }
        }
    }

    void dfs() {
        for (int i = 1; i <= 60; ++i) {
            int j = (i * 100 - 100) % 1000 + 100;
            int newI = (i - 1) % 12 + 1;
                st.clear();
                path.clear();
                ret_now = false;
                vector<vector<int>> grid = mark;
                make(grid, newI, j);
                /*for (auto a : grid)
                {
                    for (auto b : a)
                        cout << b << ' ';
                    cout << endl;
                }*/
                int pre = ans.size();
                dfs_helper(grid);
                if(pre+1==ans.size())
                cout << "found" << newI << " " << j << endl;
                else
                cout<< "###NOT FOUND###" << newI << " " << j << endl;
        }
        if (ans.size() != 60)
        {
            cout << "无法找到全部解法" << endl;
        }
    }
    long long count = 0;
    void dfs_helper(vector<vector<int>> &grid) {
        ++count;
        if (st.find(grid) != st.end())
            return;
        st.insert(grid);
        if (count % 1000000 == 0)
        {
            /*for (auto arr : grid)
            {
                for (int n : arr)
                    cout << n << " ";
                cout << endl;
            }*/
            cout <<"cur==" << count << endl;
            for (auto arr : path)
            {
                cout << arr[0] << " " << arr[1]<<" ";
            }
        }
        if (ret_now)
            return;
        bool found = true;
        for (auto &arr : grid)
            for (auto &n : arr)
                if (n == 0) {
                    found = false;
                }
        if (found) {
            ret_now = true;
            ans.push_back(path);
            count = 0;
            return;
        }
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[0].size(); ++y) {
                if (grid[x][y])
                    continue;
                //if (count % 1000000 == 0)
                //    cout << x << " " << y << endl;
                for (int i = 0; i < dx.size(); ++i) {
                    int newX = x + dx[i];
                    int newY = y + dy[i];
                    if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
                        if (grid[newX][newY])
                            continue;
                        vector<vector<int>> &temp = grid;
                        temp[newX][newY] = 1;
                        temp[x][y] = 1;
                        path.push_back({ x, y, i });
                        dfs_helper(temp);
                        path.pop_back();
                        temp[newX][newY] = 0;
                        temp[x][y] = 0;
                    }
                }
            }
        }
    }
};
int main() {
    meth test;
    test.dfs();
    //输出格式
    //arr[0],arr[1] 代表起始点
    //arr[2]代表放置方向
    //天干
    std::vector<std::string> tiangan = { "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸" };

    // 地支
    std::vector<std::string> dizhi = { "子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥" };
    vector<string> fwd = { "下","右","上","左" };
    for (int i = 0; i < test.ans.size();++i) 
    {
        cout << "solution for: " << tiangan[i%10]<<" "<< dizhi[i % 12] << endl;
        for (int j = 0; j < test.ans[i].size();++j) 
        {

            vector<int>& temp = test.ans[i][j];
            for (int i = 0; i < temp.size(); ++i)
            {
                if (i == 2)
                    cout << fwd[temp[i]] << " ";
                else
                cout << temp[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
