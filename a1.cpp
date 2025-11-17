// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <set>
using namespace std;
/*
void mergesort(vector<int>& arr,int low,int high)
{

    if(low >= high)
    {
        return;
    }
    int mid = low + (high-low)/2;
    mergesort(arr,low,mid-1);
    mergesort(arr,mid,high);
    merge(arr,low,high,mid);
}

void merge(vector<int>& arr, int low,int high,int mid)
{
    int n1 = mid - low+1;
    int n2 = high - mid;

    vector<int> L(n1),M(n2);
    int k=0;
    for(int i=0;i<n1;i++)
    {
        L[k]=arr[low+i];
        k++;
    }
    for(int j=0;j<n2;j++)
    {
        M[k]=arr[high+j+1];
        k++;
    }
    int i=0;
    int j=0;

    k=left;

    while(i<n1 && j<n2)
    {
        if(L[i]<M[j])
        {
            arr[k]=L[i];
            i++;
        }
        else
        {
            arr[k]=M[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=M[j];
        k++;
        j++;
    }
}
*/

bool twosum(vector<int> &arr, int target)
{
    int n = arr.size();
    int i = 0;
    int j = n - 1;

    while (i < j)
    {
        int sum = arr[i] + arr[j];
        if (sum == target)
        {
            cout << arr[i] << endl;
            cout << arr[j] << endl;
            return true;
        }
        else if (sum < target)
        {
            i++;
        }
        else
            j--;
    }
    return false;
}

int maxSum(vector<int> &arr, int k)
{
    int n = arr.size();

    int max_sum = 0;

    for (int i = 0; i < k; i++)
    {
        max_sum = max_sum + arr[i];
    }
    int max = max_sum;
    for (int i = k; i < n; i++)
    {
        max = max + arr[i] - arr[i - k];

        if (max > max_sum)
        {
            max_sum = max;
        }
    }
    return max;
}

/*
void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}
*/

int fact(int n)
{
    if (n == 0)
        return 1;

    return n * fact(n - 1);
}

struct Node
{
    int data;
    Node *next;
    Node(int d)
    {
        this->data = d;
        this->next = nullptr;
    }
};

struct node
{
    int data;
    node *next;
    node *prev;

    node(int d)
    {
        this->data = d;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

int length_ll(Node *n)
{
    int count = 0;
    while (n != nullptr)
    {
        count++;
        n = n->next;
    }
    return count;
}

void deleteList(Node *curr)
{
    while (curr != nullptr)
    {
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }
}

string reverseWords(string s)
{
    vector<string> vt;
    int first = 0;
    int last = 0;
    int count = 0;
    cout << "string s ---> " << s.length() << endl;
    for (int i = 0; i < s.length(); i++)
    {
        if (s.at(i) != ' ' && count == 0)
        {
            cout << "starting index---> " << i << endl;
            first = i;
            count++;
        }
        if ((s.at(i) == ' ' && count != 0))
        {
            cout << "ending index---> " << (i - 1) << endl;
            last = i - 1;
            string s1 = s.substr(first, last - first + 1);
            vt.push_back(s1);
            count = 0;
        }
        if (i == s.length() - 1 && count > 0)
        {
            last = i - 1;
            string s1 = s.substr(first, last - first + 1);
            vt.push_back(s1);
            count = 0;
        }
    }
    cout << "size of vector is---> " << vt.size() << endl;
    string res = "";
    for (int i = vt.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            res = res + vt[i];
        }
        else
        {
            res = res + vt[i] + " ";
        }
    }
    return res;
}

void rotate(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n == 1)
    {
        return;
    }
    vector<int> res;
    if (n > k)
    {
        for (int i = n - k; i < n; i++)
        {
            res.push_back(nums[i]);
        }
        for (int i = 0; i < n - k; i++)
        {
            res.push_back(nums[i]);
        }
        nums = res;
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            int l = nums[n - 1];
            for (int j = n - 1; j >= 1; j--)
            {
                nums[j] = nums[j - 1];
            }
            nums[0] = l;
        }
    }
}

bool wordPattern(string pattern, string s)
{
    cout << "word pattern problem" << endl;

    vector<string> vec;
    int first = 0;
    int last = 0;
    int count = 0;
    for (int i = 1; i < s.length(); i++)
    {
        if (s.at(i) == ' ' && count == 0)
        {
            last = i;
            string res = s.substr(first, last - first);
            cout << res << endl;
            vec.push_back(res);
            first = i + 1;
        }
        if (i == s.length() - 1)
        {
            last = i;
            string res = s.substr(first, last - first + 1);
            cout << res << endl;
            vec.push_back(res);
        }
    }

    if (pattern.length() != vec.size())
    {
        cout << "there is length mismatch" << endl;
        return false;
    }

    map<char, string> mp;

    for (int i = 0; i < pattern.length(); i++)
    {
        char c = pattern.at(i);
        if (mp.find(c) != mp.end())
        {
            string s1 = mp[c];
            cout << " char-->" << c << " string-->" << s1 << " vector string -->" << vec[i] << endl;
            string s2 = vec[i];
            cout << "length of s1-->" << s1.length() << "length of s2-->" << s2.length() << endl;
            if (s1 != s2)
            {
                cout << " s1 is not equal to vec[i]" << endl;
                return false;
            }
        }
        else
        {
            mp.insert({c, vec[i]});
        }
    }
    return true;
}

int numSquareSum(int n)
{
    int num = 0;
    while (n != 0)
    {
        int digit = n % 10;
        num += digit * digit;
        n /= 10;
    }
    return num;
}

bool isHappyNumber(int n)
{
    set<int> st;
    while (1)
    {
        n = numSquareSum(n);
        if (n == 1)
            return true;
        if (st.find(n) != st.end())
            return false;
        st.insert(n);
    }
}

int longestConsecutive(vector<int> &nums)
{

    int max = INT_MIN;

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > max)
            max = nums[i];
    }
    vector<bool> res(max + 1, false);
    for (int i = 0; i < max + 1; i++)
    {
        res[nums[i]] = true;
    }
    int first = -1;
    int last = -1;
    int count_max = INT_MIN;
    for (int i = 0; i < max + 1; i++)
    {
        if (res[i] == true && first == -1)
        {
            first = i;
        }
        else if (res[i] == false && last == -1)
        {
            if (i - 1 >= 0)
            {
                if (res[i - 1] == true)
                {
                    last = i - 1;
                    if (last - first > count_max)
                    {
                        count_max = last - first;
                    }
                    first = -1;
                    last = -1;
                }
            }
        }
    }
    return count_max;
}

bool anagram(string s1, string s2)
{
    if (s1.length() != s2.length())
    {
        cout << s1 << " and " << s2 << " are not anagram" << endl;
        return false;
    }
    map<char, int> mp;

    for (int i = 0; i < s1.length(); i++)
    {
        if (mp.find(s1.at(i)) != mp.end())
        {
            int x = mp[s1.at(i)];
            mp[s1.at(i)] = x + 1;
        }
        else
        {
            mp.insert({s1.at(i), 1});
        }
    }

    for (int i = 0; i < s2.length(); i++)
    {
        if (mp.find(s2.at(i)) != mp.end())
        {
            int x = mp[s2.at(i)];
            if (x > 0)
            {
                mp[s2.at(i)] = x - 1;
            }
            else
            {
                cout << s1 << " and " << s2 << " are not anagram" << endl;
                return false;
            }
        }
        else
        {
            cout << s1 << " and " << s2 << " are not anagram" << endl;
            return false;
        }
    }

    for (auto &pair : mp)
    {
        if (pair.second != 0)
        {
            cout << s1 << " and " << s2 << " are not anagram" << endl;
            return false;
        }
    }
    cout << s1 << " and " << s2 << " are anagram" << endl;
    return true;
}
vector<vector<string>> groupAnagrams(vector<string> &strs)
{

    int n = strs.size();
    vector<bool> vec(n, false);

    vector<vector<string>> res;

    for (int i = 0; i < n; i++)
    {
        if (vec[i] == false)
        {
            vector<string> vec1;
            string s1 = strs[i];
            vec1.push_back(s1);
            vec[i] = true;
            for (int j = i + 1; j < n; j++)
            {
                if (vec[j] == false)
                {
                    string s2 = strs[j];
                    if (anagram(s1, s2))
                    {
                        vec1.push_back(s2);
                        vec[j] = true;
                    }
                }
            }
            res.push_back(vec1);
        }
    }
    return res;
}

string addBinary(string a, string b)
{

    int n = a.length();
    int m = b.length();
    cout << "length of n : " << n << endl;
    cout << "length of m : " << m << endl;

    string res = "";
    int carry = 0;
    while (n > 0 || m > 0)
    {
        int x = 0;
        int y = 0;
        if (n - 1 >= 0)
        {
            if (a.at(n - 1) == '1')
            {
                x = 1;
            }
        }

        if (m - 1 >= 0)
        {
            if (b.at(m - 1) == '1')
            {
                y = 1;
            }
        }

        int z = x + y + carry;
        carry = z / 2;
        res = to_string(z % 2) + res;
        cout << "value of z , carry and res is " << z << " " << carry << " " << res << endl;

        n--;
        m--;
    }
    if (carry == 1)
    {
        res = '1' + res;
    }
    return res;
}

int evalRPN(vector<string> tokens)
{
    cout << "entering ecalRPN function" << endl;
    stack<int> st;

    for (int i = 0; i < tokens.size(); i++)
    {
        string s1 = tokens[i];
        if (s1 == "+")
        {
            cout << "string s1---->" << s1 << endl;
            int x = st.top();
            st.pop();
            int y = st.top();
            st.pop();
            int z = x + y;
            cout << "value of x,y,z are-->" << x << " " << y << " " << z << endl;
            st.push(z);
        }
        else if (s1 == "-")
        {
            cout << "string s1---->" << s1 << endl;
            int x = st.top();
            st.pop();
            int y = st.top();
            st.pop();
            int z = x - y;
            cout << "value of x,y,z are-->" << x << " " << y << " " << z << endl;
            st.push(z);
        }
        else if (s1 == "*")
        {
            cout << "string s1---->" << s1 << endl;
            int x = st.top();
            st.pop();
            int y = st.top();
            st.pop();
            int z = x * y;
            cout << "value of x,y,z are-->" << x << " " << y << " " << z << endl;
            st.push(z);
        }
        else if (s1 == "/")
        {
            cout << "string s1---->" << s1 << endl;
            int x = st.top();
            st.pop();
            int y = st.top();
            st.pop();
            int z = y / x;
            cout << "value of x,y,z are-->" << x << " " << y << " " << z << endl;
            st.push(z);
        }
        else
        {
            cout << "string s1---->" << s1 << endl;
            st.push(stoi(s1));
        }
    }
    return st.top();
}

int main()
{
    /*   vector<int> arr = {1, 4, 2, 10, 2, 3, 1, 0, 20};
       int k = 4;
       cout << maxSum(arr, k);
       cout << endl;

       string str = "the sky is blue";
       cout << "Input is " << str << endl;

       cout << reverseWords(str) << endl;

       bool x = wordPattern("abba", "dog cat cat dog");
       if (x == true)
       {
           cout << "return is true" << endl;
       }
       else
           cout << "return is false" << endl;

       x = isHappyNumber(19);
       if (x == true)
       {
           cout << "return is true" << endl;
       }
       else
           cout << "return is false" << endl;

       vector<int> vec_l = {100, 4, 200, 1, 3, 2};
       cout << longestConsecutive(vec_l) << endl;

       x = anagram("ddddddddddg", "dgggggggggg");
       if (x == true)
       {
           cout << "return is true" << endl;
       }
       else
           cout << "return is false" << endl;

       // cout << addBinary("11", "1") << endl;

       */

    cout << evalRPN({"4", "13", "5", "/", "+"}) << endl;

    return 0;
}
