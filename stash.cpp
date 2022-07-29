#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <unordered_set>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>
#include <chrono>
#include <time.h>
#include <map>
#include <unordered_map>
struct Node {
    int position;
    char bucketSize;
    Node *next;
    char level;
    int *addr;
    char full;
    char fillPos;
    int start;
    int end;
};
int hit = 0;
int flag = 0;
int save = 0;
int ss = 0;
int countSpace = 0;
int **c;
void print(int numOfLevels, int *numberOfNodesPerLevel, int *bucketSize, Node **tree)
{
    for(int i = 0; i < numOfLevels; i++)
    {
        for(int j=0; j < numberOfNodesPerLevel[i]; j++)
        {
            for(int k=0; k < bucketSize[i]; k++)
            {
                std::cout << tree[i][j].addr[k] << " ";
            }
            std::cout << "\t\t";
        }
        std::cout << std::endl;
    }
}
void print2(int numOfLevels, int *numberOfNodesPerLevel, int *bucketSize, Node **tree)
{
    for(int i = 0; i < numOfLevels; i++)
    {
        for(int j=0; j < numberOfNodesPerLevel[i]; j++)
        {
            std::cout << tree[i][j].start << ":" << tree[i][j].end;
            std::cout << "\t\t";
        }
        std::cout << std::endl;
    }
}

void read(Node **a, int pos, int level, std::vector<std::pair<int,int>> &stash, int *posMap)
{   
    
    int levelc = level-1;
    int path = pos;
    for(int i = levelc; i >= 0; i--)
    {
        for(int j = 0; j < a[i][path].bucketSize; j++)
        {
            if(a[i][path].addr[j] != -1)
            {   
                
                stash.push_back(std::make_pair(posMap[a[i][path].addr[j]],a[i][path].addr[j]));
                a[i][path].addr[j] = -1;
            }
        }
        a[i][path].fillPos = 0;
        a[i][path].full = 0;
        path/=2;

    }
}
void initialize2(Node **a, int level, int *pos, int *numOfNodesPerLevel, int *bucketSize, int data, std::vector<std::pair<int,int>> &stash)
{   
    //std::cout << "hola" << std::endl; 
    int k = 0;
    for (int i = 0; i < level; i++)
    {   
        //std::cout << numberOfNodesPerLevel[i] << std::endl;
        a[i] = new Node[numOfNodesPerLevel[i]];
        int somethingElse = pow(2, level-1)/pow(2, i);
        int start = 0;
        int end = somethingElse-1;
        
        for(int j = 0; j < numOfNodesPerLevel[i]; j++)
        {
            a[i][j].start = start;
            a[i][j].end = end;
            start = end+1;
            end += somethingElse;
            //std::cout << j;
            a[i][j].level = i;    
            a[i][j].fillPos = 0;
            a[i][j].bucketSize = bucketSize[i];
            a[i][j].position = j;
            a[i][j].addr = (int*)malloc(bucketSize[i]*sizeof(int));
            a[i][j].full = 0;
            c[i][j] = 0;
            for(int k=0; k < bucketSize[i]; k++)
            {
                a[i][j].addr[k] = -1; //INT_MIN;
            }
            //a[i][j].addr[0] = i+j;
            if(i>0)
            {
                a[i][j].next = &a[i-1][j/2];
            }
            else
            {
                a[i][j].next = NULL;
            }
            

        }

    }
    /*
    Node *aa = &a[level-1][7];
    while(aa != NULL)
    {
        std::cout << aa->data[0] << std::endl;
        aa = aa->next;
    }*/
    //std::cout << "hola" << std::endl;
    std::vector<std::tuple<int,int,int>> vp;
    //std::cout << vp.size();
    //vp.resize(0);
    for (int i = 0; i < data; i++) {
        vp.push_back(std::make_tuple(pos[i], i, 0));
    }
    //std::cout << "yolo1\n";
    sort(vp.begin(), vp.end());
    //std::cout << "yolo2\n";
    //std::cout << vp.size();
    //std::cout << "Element\t"  << "index\t" << "flag" << std::endl;
    // if(vp.size() <= 100)
    // {
    //     for (int i = 0; i < vp.size(); i++) {
    //         //std::cout << std::get<0>(vp[i]) << '\t' << std::get<1>(vp[i]) <<  std::endl;
    //     }
    // }
    //std::cout << "yolo" << std::endl;
    int ct = 0;
    for(int i = 0; i < vp.size(); i++)
    {   

        //std::cout << "yolo" << std::endl;
        int lev = level-1;
        int curPath = std::get<0>(vp[i]);
        while(a[lev][curPath].full == 1)
        {
            // TRY TO MAKE IT USING NEXT
            lev--;
            curPath/=2;
            if(lev == -1)
                break;
        }
        if(lev < 0)
        {
            //std::cout << "yolo[";
            stash.push_back(std::make_pair(std::get<0>(vp[i]),std::get<1>(vp[i])));
            //std::cout << "yoloo";
        }
        else{
            a[lev][curPath].addr[a[lev][curPath].fillPos++] = std::get<1>(vp[i]);
            if(a[lev][curPath].fillPos == bucketSize[lev])
            {
                a[lev][curPath].full = 1;
            }
        }
    }
}

void evict2(Node **a, int pos, int level, std::vector<std::pair<int,int>> &stash, int *posMap, int *numberOfNodesPerLevel, int *bucketSize)
{
    int levelc = level-1;
    int path = pos;
    int start = pos;
    int end = pos;

    for(int i = levelc; i >= 0; i--)
    {
        
        int offset = pow(2, (levelc-i));
        int offset2 = offset/2;
        int bookKeep = 0;
        if(offset2 != 0)
        {
            bookKeep = pos / offset2;
        }
        for(int k = 0; k < stash.size(); k++)
        {
            //start and end are used to find which all paths can fit in this particular node
            //offset is used to determine the change i.e. each higher level doubles the offset as the parent can store twice the number of paths
            if(i != levelc)
            {
                if(bookKeep%2 == 0)
                {
                    if((posMap[stash[k].second] >= (start+offset2)) && (posMap[stash[k].second] <= end))
                    {
                        if(a[i+1][2*path+1].fillPos != a[i+1][2*path+1].bucketSize)
                        {
                            countSpace++;
                            //std::cout << "value " << stash[k].second << " with position " << stash[k].first << " could be written to child node with first value " << a[i+1][2*path+1].addr[0] << " and with level " << i+1 <<" and horizontal position "<< 2*path+1 << std::endl << std::endl;
                            a[i+1][2*path+1].addr[a[i+1][2*path+1].fillPos++] = stash[k].second;
                            stash.erase(stash.begin()+k);        
                            k--;                                            
                        }

                        //k--;
                        if(a[i+1][2*path+1].fillPos == a[i+1][2*path+1].bucketSize)
                        {
                            a[i+1][2*path+1].full = 1;
                            if((a[i+1][2*path+1].fillPos == a[i+1][2*path+1].bucketSize) && (a[i][path].fillPos == a[i][path].bucketSize))
                            {
                                break;
                            }  
                        }
                        if(k < 0)
                        {
                            continue;
                        }
                        
                    }  
                }
                else
                {
                    if((posMap[stash[k].second] >= start) && (posMap[stash[k].second] <= (end-offset2)))
                    {
                        if(a[i+1][2*path].fillPos != a[i+1][2*path].bucketSize)
                        {
                            countSpace++;
                            //std::cout << "value " << stash[k].second << " with position " << stash[k].first << " could be written to child node with first value" << a[i+1][2*path].addr[0] << " and with level " << i+1 <<" and horizontal position "<< 2*path << std::endl << std::endl;
                            a[i+1][2*path].addr[a[i+1][2*path].fillPos++] = stash[k].second;
                            stash.erase(stash.begin()+k);
                            k--;
                        }
                        //k--;
                        
                        if(a[i+1][2*path].fillPos == a[i+1][2*path].bucketSize)
                        {
                            a[i+1][2*path].full = 1;
                            if((a[i+1][2*path].fillPos == a[i+1][2*path].bucketSize) && (a[i][path].fillPos == a[i][path].bucketSize))
                            {
                                break;
                            }
                        }
                        if(k < 0)
                        {
                            continue;
                        }
                        
                    }  
                }
            }
            if((posMap[stash[k].second] >= start) && (posMap[stash[k].second] <= end) && (stash.size() > 0))
            {
                if(a[i][path].fillPos != a[i][path].bucketSize)
                {
                    a[i][path].addr[a[i][path].fillPos++] = stash[k].second;
                    stash.erase(stash.begin()+k);
                    k--;
                }

                if(a[i][path].fillPos == a[i][path].bucketSize)
                {
                    a[i][path].full = 1;
                    //break;
                }
            }
        }
        if(path%2 == 0)
        {
            end+=offset;
        }
        else
        {
            start-=offset;
        }
        path/=2;
    }
}
void evict4(Node **a, int pos, int level, std::vector<std::pair<int,int>> &stash, int *posMap, int *numberOfNodesPerLevel, int *bucketSize)
{
    int group = 4;
    //int loop = level/4;
    int levelc = level-1;
    int path = pos;
    for(int i = levelc; i >= 0; i-=group)
    {    
        int ct = group-1;
        if(i >= (group-1))
        {    
            for(int j = i; j > (i-group); j--)
            {
                int nodesPerLevel = pow(2, ct);
                int mod = path%nodesPerLevel;
                int start = path-mod;
                int end = start+nodesPerLevel-1;
                //std::cout << start << ":" << end << std::endl;
                ct--;
                for(int k = start; k <= end; k++)
                {
                    //std::cout << "current path" << path << "-" << j << ":" << k << std::endl;
                    for(int l = 0; l < stash.size(); l++)
                    {
                        if((posMap[stash[l].second] >= a[j][k].start) && (posMap[stash[l].second] <= a[j][k].end))
                        {
                            if(a[j][k].fillPos != a[j][k].bucketSize)
                            {
                                if(k != path)
                                    countSpace++;
                                //std::cout << "value " << stash[l].second << " with position " << posMap[stash[l].second] << " could be written to child node with first value " << a[j][k].addr[0] << " and with level " << j <<" and horizontal position "<< k << std::endl ;
                                a[j][k].addr[a[j][k].fillPos++] = stash[l].second;
                                stash.erase(stash.begin()+l);
                                l--;
                            }
                            if(a[j][k].fillPos == a[j][k].bucketSize)
                            {
                                a[j][k].full = 1;
                                break;
                            }
                        }                    
                    }
                }
                path/=2;
            }
        }
        else
        {
            ct = i;
            for(int j = i; j >= 0; j--)
            {
                int nodesPerLevel = pow(2, ct);
                int mod = path%nodesPerLevel;
                int start = path-mod;
                int end = start+nodesPerLevel-1;
                //std::cout << start << ":" << end << std::endl;
                ct--;
                for(int k = start; k <= end; k++)
                {
                    //std::cout << "current path" << path << "-" << j << ":" << k << std::endl;
                    for(int l = 0; l < stash.size(); l++)
                    {
                        if((posMap[stash[l].second] >= a[j][k].start) && (posMap[stash[l].second] <= a[j][k].end))
                        {
                            if(a[j][k].fillPos != a[j][k].bucketSize)
                            {
                                if(k != path)
                                    countSpace++;
                                //std::cout << "value " << stash[l].second << " with position " << posMap[stash[l].second] << " could be written to child node with first value " << a[j][k].addr[0] << " and with level " << j <<" and horizontal position "<< k << std::endl ;
                                a[j][k].addr[a[j][k].fillPos++] = stash[l].second;
                                stash.erase(stash.begin()+l);
                                l--;
                            }
                            if(a[j][k].fillPos == a[j][k].bucketSize)
                            {
                                a[j][k].full = 1;
                                break;
                            }
                        }                    
                    }
                }
                path/=2;
            }            
        }
    }
}
void evict3(Node **a, int pos, int level, std::vector<std::pair<int,int>> &stash, int *posMap, int *numberOfNodesPerLevel, int *bucketSize)
{
    int group = 3;
    int levelc = level-1;
    int path = pos;
    for(int i = levelc; i >= 0; i-=group)
    {    
        int ct = group-1;
        if(i >= (group-1))
        {    
            for(int j = i; j > (i-group); j--)
            {
                int nodesPerLevel = pow(2, ct);
                int mod = path%nodesPerLevel;
                int start = path-mod;
                int end = start+nodesPerLevel-1;
                //std::cout << start << ":" << end << std::endl;
                ct--;
                for(int k = start; k <= end; k++)
                {
                    //std::cout << "current path" << path << "-" << j << ":" << k << std::endl;
                    for(int l = 0; l < stash.size(); l++)
                    {
                        if((posMap[stash[l].second] >= a[j][k].start) && (posMap[stash[l].second] <= a[j][k].end))
                        {
                            if(a[j][k].fillPos != a[j][k].bucketSize)
                            {
                                if(k != path)
                                    countSpace++;
                                //std::cout << "value " << stash[l].second << " with position " << posMap[stash[l].second] << " could be written to child node with first value " << a[j][k].addr[0] << " and with level " << j <<" and horizontal position "<< k << std::endl ;
                                a[j][k].addr[a[j][k].fillPos++] = stash[l].second;
                                stash.erase(stash.begin()+l);
                                l--;
                            }
                            if(a[j][k].fillPos == a[j][k].bucketSize)
                            {
                                a[j][k].full = 1;
                                break;
                            }
                        }                    
                    }
                }
                path/=2;
            }
        }
        else
        {
            ct = i;
            for(int j = i; j >= 0; j--)
            {
                int nodesPerLevel = pow(2, ct);
                int mod = path%nodesPerLevel;
                int start = path-mod;
                int end = start+nodesPerLevel-1;
                //std::cout << start << ":" << end << std::endl;
                ct--;
                for(int k = start; k <= end; k++)
                {
                    //std::cout << "current path" << path << "-" << j << ":" << k << std::endl;
                    for(int l = 0; l < stash.size(); l++)
                    {
                        if((posMap[stash[l].second] >= a[j][k].start) && (posMap[stash[l].second] <= a[j][k].end))
                        {
                            if(a[j][k].fillPos != a[j][k].bucketSize)
                            {
                                if(k != path)
                                    countSpace++;
                                //std::cout << "value " << stash[l].second << " with position " << posMap[stash[l].second] << " could be written to child node with first value " << a[j][k].addr[0] << " and with level " << j <<" and horizontal position "<< k << std::endl ;
                                a[j][k].addr[a[j][k].fillPos++] = stash[l].second;
                                stash.erase(stash.begin()+l);
                                l--;
                            }
                            if(a[j][k].fillPos == a[j][k].bucketSize)
                            {
                                a[j][k].full = 1;
                                break;
                            }
                        }                    
                    }
                }
                path/=2;
            }            
        }
    }
}
void evict(Node **a, int pos, int level, std::vector<std::pair<int,int>> &stash, int *posMap, int *numberOfNodesPerLevel, int *bucketSize)
{
    int levelc = level-1;
    int path = pos;
    int start = pos;
    int end = pos;

    for(int i = levelc; i >= 0; i--)
    {        
        int offset = pow(2, (levelc-i));
        int offset2 = offset/2;
        int bookKeep = 0;
        if(offset2 != 0)
        {
            bookKeep = pos / offset2;
        }
        for(int k = 0; k < stash.size(); k++)
        {

            if((posMap[stash[k].second] >= start) && (posMap[stash[k].second] <= end))
            {
                if(a[i][path].fillPos != a[i][path].bucketSize)
                {
                    c[i][path]++;
                    a[i][path].addr[a[i][path].fillPos++] = stash[k].second;
                    stash.erase(stash.begin()+k);
                    k--;
                }

                if(a[i][path].fillPos == a[i][path].bucketSize)
                {
                    a[i][path].full = 1;
                    break;
                }
            }
        }
        if(path%2 == 0)
        {
            end+=offset;
        }
        else
        {
            start-=offset;
        }
        path/=2;

    }
}
void check(Node**a, int *numberOfNodesPerLevel, int *bucketSize, int level)
{
    int check1 = 0;
    int maxcheck1 = 0;
    int check2 = 0;
    for(int i = 0; i < level; i++)
    {
        for(int j = 0; j < numberOfNodesPerLevel[i]; j++)
        {
            if(a[i][j].fillPos > check1)
            {
                check1 = a[i][j].fillPos;
            }
            if(check1 > maxcheck1)
                maxcheck1 = check1;
            for(int k = 0; k < bucketSize[i]; k++)
            {
                if(a[i][j].addr[k] != -1)
                {
                    check2++;
                }
            }
        }
    }
    std::cout << " max num of element in a bucket: " <<  check1 << " number of element in tree: " << check2 << std::endl;
}
void pageRead(Node **a, int level, std::vector<std::pair<int,int>> &stash, int *pos, int value, int *numberOfNodesPerLevel, int *bucketSize)
{   
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //     {
    //         hit++;
    //         flag = 1;
    //         return;
    //     }
    // }
    read(a, pos[value], level, stash, pos);
    int temp = pos[value];
    //int index;
    //std::cout << "Old path for address value " << value << " is: " << pos[value] << std::endl;
    pos[value] = rand() % ((int)pow(2,level-1));    
    //pos[value] = (pos[value] + 1) % ((int)pow(2,level-1)); 
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //         stash[i].first = pos[value];
    // }
    //std::cout << "New path for address value " << value << " is: " << pos[value] << std::endl;
    //PRINT CURRENT STASH
    // std::cout << "The current stash is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << pos[stash[i].second] << " " ;
    // }
    // std::cout << std::endl;

    //is sorting even necessary?
    //sort(stash.begin(), stash.end());

    /*for(int i = 0; i < stash.size(); i++)
    {
        if(stash[i].first == temp)
        {
            index = i;
            break;
        }
    }*/
    evict2(a, temp, level, stash, pos, numberOfNodesPerLevel, bucketSize);
    //PRINT STASH AFTER EVICTION
    // std::cout << "Stash after eviction is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << pos[stash[i].second] << " " ;
    // }
    // std::cout << std::endl;

    //std::cout << index << "yolo" << std::endl;
}
void mainRead(Node **a, int level, std::vector<std::pair<int,int>> &stash, int *pos, int value, int *numberOfNodesPerLevel, int *bucketSize)
{   
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //     {
    //         hit++;
    //         flag = 1;
    //         return;
    //     }
    // }
    read(a, pos[value], level, stash, pos);
    int temp = pos[value];
    //int index;
    //std::cout << "Old path for address value " << value << " is: " << pos[value] << std::endl;
    pos[value] = rand() % ((int)pow(2,level-1));    
    //pos[value] = (pos[value] + 1) % ((int)pow(2,level-1)); 
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //         stash[i].first = pos[value];
    // }
    //std::cout << "New path for address value " << value << " is: " << pos[value] << std::endl;
    //PRINT CURRENT STASH
    // std::cout << "The current stash is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << pos[stash[i].second] << " " ;
    // }
    // std::cout << std::endl;

    //is sorting even necessary?
    //sort(stash.begin(), stash.end());

    /*for(int i = 0; i < stash.size(); i++)
    {
        if(stash[i].first == temp)
        {
            index = i;
            break;
        }
    }*/
    evict(a, temp, level, stash, pos, numberOfNodesPerLevel, bucketSize);
    //PRINT STASH AFTER EVICTION
    // std::cout << "Stash after eviction is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << pos[stash[i].second] << " " ;
    // }
    // std::cout << std::endl;

    //std::cout << index << "yolo" << std::endl;
}


void dummyRead(Node **a, int level, std::vector<std::pair<int,int>> &stash, int *pos, int value, int *numberOfNodesPerLevel, int *bucketSize)
{   
    
    read(a, pos[value], level, stash, pos);
    int temp = pos[value];
    int index;
    //std::cout << "Old path for address value " << value << " is: " << pos[value] << std::endl;
    //pos[value] = rand() % ((int)pow(2,level-1));    
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //         stash[i].first = pos[value];
    // }
    //std::cout << "New path for address value " << value << " is: " << pos[value] << std::endl;
    //PRINT CURRENT STASH
    // std::cout << "The current stash is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << stash[i].first << " ";
    // }
    // std::cout << std::endl;

    //is sorting even necessary?
    //sort(stash.begin(), stash.end());

    /*for(int i = 0; i < stash.size(); i++)
    {
        if(stash[i].first == temp)
        {
            index = i;
            break;
        }
    }*/
    evict(a, temp, level, stash, pos, numberOfNodesPerLevel, bucketSize);
    //PRINT STASH AFTER EVICTION
    // std::cout << "Stash after eviction is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << stash[i].first << " ";
    // }
    // std::cout << std::endl;
    // std::cout << index << "yolo" << std::endl;
}
void pageDummyRead(Node **a, int level, std::vector<std::pair<int,int>> &stash, int *pos, int value, int *numberOfNodesPerLevel, int *bucketSize)
{   
    
    read(a, pos[value], level, stash, pos);
    int temp = pos[value];
    int index;
    //std::cout << "Old path for address value " << value << " is: " << pos[value] << std::endl;
    //pos[value] = rand() % ((int)pow(2,level-1));    
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     if(stash[i].second == value)
    //         stash[i].first = pos[value];
    // }
    //std::cout << "New path for address value " << value << " is: " << pos[value] << std::endl;
    //PRINT CURRENT STASH
    // std::cout << "The current stash is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << stash[i].first << " ";
    // }
    // std::cout << std::endl;

    //is sorting even necessary?
    //sort(stash.begin(), stash.end());

    /*for(int i = 0; i < stash.size(); i++)
    {
        if(stash[i].first == temp)
        {
            index = i;
            break;
        }
    }*/
    evict2(a, temp, level, stash, pos, numberOfNodesPerLevel, bucketSize);
    //PRINT STASH AFTER EVICTION
    // std::cout << "Stash after eviction is: ";
    // for(int i = 0; i < stash.size(); i++)
    // {
    //     std::cout << stash[i].second << ":" << stash[i].first << " ";
    // }
    // std::cout << std::endl;
    // std::cout << index << "yolo" << std::endl;
}


int main()
{   
    
    int data;
    std::cout << "Enter the number of real data blocks (134217728 for 8GB, 268435456 for 16GB and 536870912 for 32GB): ";
    std::cin >> data;
    std::cout << std::endl;
    std::ifstream fin;
    std::string a;
    std::string fileName;
    //input threshold for dummy reads 
    int upperThreshold = 40000;
    int lowerThreshold = 10000;
    std::cout << "Please enter benchmark: ";
    std::cin >> fileName;
    std::cout << std::endl;
    fin.open(fileName);
    //std::getline(fin, a);
    //data = 268435456;//536870912; //134217728; // // // //
    //std::cout << data << std::endl;
    //data = 100;
    int numOfLevels = log(data) / log(2);

    std::cout << "Number of levels: " << numOfLevels << std::endl;
    std::cout << "Enter the configuration (0 for PageORAM, 1 for PathORAM): ";
    int baseline;
    std::cin >> baseline;
    std::cout << std::endl;
    if(baseline == 0)
        std::cout << "The configuration chosen is PageORAM" << std::endl;

    if(baseline == 1)
        std::cout << "The configuration chosen is PathORAM" << std::endl;


    //std::cout<<"yolo" << std::endl;
    int *pos = (int*)malloc(sizeof(int)*data);
    //std::cout << "Enter the size of stash:";
    //int stashSize;
    
    //std::cin >> stashSize;

    std::vector<std::pair<int,int>> stash;
    //std::unordered_map <int, std::vector<int> > newStash;   
    std::vector<std::vector<int>> newStash(data);
    /*for(int i = 0; i < stashSize; i++)
    {
        stash[i] = INT_MIN;
    }*/
    srand(time(0));
    for(int i = 0; i < data; i++)
    {
        pos[i] = rand() % ((int)pow(2,numOfLevels-1));
        //pos[i] = i % ((int)pow(2,numOfLevels-1));
        //std::cout << i << " " << pos[i] << std::endl;
    }
    //std::cout<<"yolo" << std::endl;
    int *bucketSize = (int*)malloc(sizeof(int)*numOfLevels);
    int *numberOfNodesPerLevel = (int*)malloc(sizeof(int)*numOfLevels);
    for (int i = 0; i < numOfLevels; i++)
    {
        numberOfNodesPerLevel[i] = pow(2,i);
        
            bucketSize[i] = 3; //numOfLevels-i;

    }
    std::cout  << "The bucket size is: " << bucketSize[0] << std::endl;
    //std::cout<<"yolo" << std::endl;
    Node **tree = (Node**)malloc(sizeof(Node*)*numOfLevels);
    std::vector<std::vector<int>> count;
    c = (int**)malloc(sizeof(int*)*numOfLevels);
    for(int i= 0; i<numOfLevels;i++)
    {
        tree[i] = (Node*)malloc(sizeof(Node)*numberOfNodesPerLevel[i]);
        c[i] = (int*)malloc(sizeof(int)*numberOfNodesPerLevel[i]);
    }
    std::cout << "Tree initialization starting" << std::endl;
    initialize2(tree, numOfLevels, pos, numberOfNodesPerLevel, bucketSize, data, stash);
    std::cout << "Tree initialization finished" << std::endl;
    //initialize2(tree, numOfLevels, pos, numberOfNodesPerLevel, bucketSize, data, stash);
    //std::cout << "yolo" << std::endl ;
    //testig 

    //print(numOfLevels, numberOfNodesPerLevel, bucketSize, tree);

    int size = 0;

    std::cout << "stash size after initialization: " << stash.size() << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    int maxSize = 0;
    int dummy = 0;
    int ct = 0;
    int max = 0;
    int pre = 0;
    int current = 0;
    //std::cout << "stash size before start is: " << stash.size() << std::endl;
    while(fin)
    {
        ct++;

        if((ct) % 100000 == 0)
        {
            //std::cout << "currently on " << ct <<  " access with stash size " << stash.size() << " with dummy reads " << dummy << " with overall accesses " << (ct+dummy) << " ";
            //std::cout << "currently on " << ct <<  " access with stash size " << stash.size() << " with countspace " << countSpace << " with time ";
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> total = end - start;
            std::cout << "Currently on " << ct << " current stash size: " << stash.size()  << " access with time being: " << total.count() <<  std::endl;
            //std::cout << "currently on " << ct << " access with time being: " << total.count() << "  with stash size " << stash.size() <<" with max increase " << max << " with dummy reads " << dummy << " with overall accesses " << (ct+dummy) << " " <<  std::endl;     
        }
        std::getline(fin, a);
        //std::cout << ct++ << std::endl;
        if(a == ""){
            break;
        }
        //print(numOfLevels, numberOfNodesPerLevel, bucketSize, tree);
        pre = stash.size();
        if(baseline == 1)
            mainRead(tree, numOfLevels, stash, pos, stoi(a), numberOfNodesPerLevel, bucketSize);
        if(baseline == 0)
            pageRead(tree, numOfLevels, stash, pos, stoi(a), numberOfNodesPerLevel, bucketSize);
        
        //mainRead(tree, numOfLevels, stash, pos, stoi(a), numberOfNodesPerLevel, bucketSize);
        //newMainReadOptimized(tree, numOfLevels, newStash, pos, stoi(a), numberOfNodesPerLevel, bucketSize);
        current = stash.size();
        if((current- pre) > max)
        {
            max = current - pre;
        }
        //std::cout << "max increase in stash is: " << max << std::endl;

        if(stash.size() > upperThreshold)
        {
            while(stash.size() > lowerThreshold){
                int ad = rand() % data;
                //std::cout << "tree before dummy read is: " << std::endl;
                //print(numOfLevels, numberOfNodesPerLevel, bucketSize, tree);
                //std::cout << "dummy read of path: " << pos[ad] << std::endl;
                //dummyRead(tree, numOfLevels, stash, pos, ad, numberOfNodesPerLevel,  bucketSize);
                if(baseline == 1)
                    dummyRead(tree, numOfLevels, stash, pos, ad, numberOfNodesPerLevel,  bucketSize);
                if(baseline == 0)
                    pageDummyRead(tree, numOfLevels, stash, pos, ad, numberOfNodesPerLevel,  bucketSize);
                //std::cout << "tree after dummy read is: " << std::endl;
                //print(numOfLevels, numberOfNodesPerLevel, bucketSize, tree);
                dummy++;
            }

        }
        
        //int size = 0;
        // for (std::unordered_map<int,std::vector<int>>::iterator it = newStash.begin(); it != newStash.end(); ++it)
        //     size = it->second.size();        
        // if(maxSize < stash.size())
        // {
        //     maxSize = stash.size();
        //     //std::cout << "Stash size is: " << stash.size() << std::endl;
        // }
        // if (ct == 1000000)
        //     break;
        
            

    }
    size = 0;
    double avg[numOfLevels];
    for(int i = 0; i < numOfLevels; i++)
    {
        avg[i] = 0;
        for(int j = 0; j < numberOfNodesPerLevel[i]; j++)
        {
            avg[i] += c[i][j];
        }
        avg[i] = avg[i] / (1.0*numberOfNodesPerLevel[i]);
    }
    //std::cout << "Max stash size is: " << maxSize << " number of dummy reads is" << dummy << std::endl;
    check(tree, numberOfNodesPerLevel, bucketSize, numOfLevels);
    std::cout << "stash size at end is: " << stash.size() << " bucket size " << bucketSize[0] << std::endl;
    fin.close();   
    //print2(numOfLevels, numberOfNodesPerLevel, bucketSize, tree);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end - start;
    std::cout << total.count() <<  std::endl;     

}
