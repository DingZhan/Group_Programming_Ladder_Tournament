#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define MAX_N 1002
#define MAX_I 1002

using namespace std;
int main()
{
    std::ios::sync_with_stdio(false);
    //每种爱好包括的人的数组
    std::vector<short> Interest2People[MAX_I];
    //每个人包括的爱好的数组
    std::vector<short> People2Intereset[MAX_N];
    //深度优先遍历的人的种子集合
    std::vector<short> seeds;
    //人是否被访问过的标志位数组
    bool bVisited[MAX_N]={0};
    //每个兴趣部落的交集的人数
    std::vector<int> groupNums;
    //为了处理":"
    std::string str;
    int i, j, k, t, K, N, count=0;
    short h, seed;
    
    std::cin>>N;
    for(i=1; i<=N; ++i)
    {
        //得到字符串，为了处理":"
        std::cin>>str;
        K = atoi(str.c_str());
        for(j=0; j<K; ++j)
        {
            std::cin>>h;
            //把该人加入到对应的爱好组
            Interest2People[h].push_back(i);
            //把该兴趣爱好加入到当前人
            People2Intereset[i].push_back(h);
        }
    }
    //开始深度优先遍历，因为用的是显示栈
    for(i=1; i<=N; ++i)
    {
        //如果该人已经被访问过，则继续下次循环
        if(bVisited[i])
            continue;
        //开始计算该部落集合的人数
        count = 1;
        //设置访问标志位
        bVisited[i] = true;
        //添加该人到种子栈
        seeds.push_back(i);
        while(!seeds.empty())
        {
            //得到当前种子：人
            seed = seeds.back();
            //弹出
            seeds.pop_back();
            //获得该人所有的兴趣爱好
            for(j=0; j<People2Intereset[seed].size(); ++j)
            {
                h = People2Intereset[seed][j];
                //获得该兴趣爱好下所有的人
                for(k=0; k<Interest2People[h].size(); ++k)
                {
                    t = Interest2People[h][k];
                    //如果这个人已经被访问过，则继续
                    if(bVisited[t])
                        continue;
                    //标记访问标志位
                    bVisited[t] = true;
                    //把该人添加到当前部落集合
                    ++count;
                    //把该人加入到种子堆栈
                    seeds.push_back(t);
                }
            }
        }
        //把当前部落人数添加到一个数组
        groupNums.push_back(count);
    }
    //递减排序
    std::sort(groupNums.begin(), groupNums.end(), std::greater<int>() );
    //打印总部落数
    std::cout<<groupNums.size()<<std::endl;
    for(i=0; i<groupNums.size(); ++i)
    {
        if(i!=0)
            std::cout<<" ";
        std::cout<<groupNums[i];
    }
    std::cout<<endl;
    return 0;
}
