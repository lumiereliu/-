#include <bits/stdc++.h>
using namespace std;
const int kInf = 1 << 20;  // 无穷大

int GetMinValue(vector<int> v) {  // 求序列最小值
  int min_val = *min_element(v.begin(), v.end());
  return min_val;
}
/*本题与最长公共子序列思路大致相同 max改为min, 边界情况对调*/
vector<vector<int>> GetStateMatrix(string s1, string s2) 
{  
  int size1 = s1.size();
  int size2 = s2.size();
  int max_size = max(size1, size2) + 1;
  vector<vector<int>> dp(max_size, vector<int>(max_size, kInf)); 
  for (int i = 0; i < max_size; i++) 
  {                            
    dp[i][0] = dp[0][i] = i;
  }
  for (int i = 1; i < size1; i++) 
  {
    for (int j = 1; j < size2; j++)
    {
      if (s1[i] == s2[j]) 
      {  
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
      dp[i][j] = GetMinValue({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i][j]});
    }
  }
  return dp;
}

string GetCommonSequence(string s1, string s2, vector<vector<int>> dp, int start1, int start2) 
{  
  string ans;
  int i = start1;
  int j = start2;
  while (i > 0 && j > 0) 
  {
    if (dp[i][j] == dp[i - 1][j - 1] + 1 && s1[i] == s2[j]) 
    {
      ans.push_back(s1[i]);
      i--;
      j--;
    } 
    else if (dp[i][j] == dp[i - 1][j] + 1)  
    {
      ans.push_back(s1[i]);
      i--;
    } 
    else if (dp[i][j] == dp[i][j - 1] + 1) 
    {
      ans.push_back(s2[j]);
      j--;
    }
  }
  while (i > 0)  
  {
    ans.push_back(s1[i]);
    i--;
  }
  while (j > 0)
  {  
    ans.push_back(s2[j]);
    j--;
  }
  return ans;
}

string CommonSequenceForThree(string s1, string s2, string s3) // 求三个的最短超序列 思路同求两个字符串的超序列
{  
  int size1 = s1.size();
  int size2 = s2.size();
  int size3 = s3.size();
  // 在字符串前填充一个字符，使索引对齐
  s1 = '0' + s1; 
  s2 = '0' + s2; 
  s3 = '0' + s3;
  auto dp12 = GetStateMatrix(s1, s2);
  auto dp13 = GetStateMatrix(s1, s3);
  auto dp23 = GetStateMatrix(s2, s3);
  int max_size = max(max(size1, size2), size3) + 1;
  int dp[max_size][max_size][max_size];
  for (int i = 0; i <= size1; i++) // 将dp数组设置为正无穷，而后以两个序列的最短超序列初始化dp数组
  {  
    for (int j = 0; j <= size2; j++) {
      for (int k = 0; k <= size3; k++) 
      {
        dp[i][j][k] = kInf;
        if (i == 0) 
        {
          dp[i][j][k] = dp23[j][k];
        } else if (j == 0) 
        {
          dp[i][j][k] = dp13[i][k];
        } else if (k == 0) 
        {
          dp[i][j][k] = dp12[i][j];
        }
      }
    }
  }
  for (int i = 1; i <= size1; i++) // 关键代码：状态转移，总共有7种状态转移可能
  {  
    for (int j = 1; j <= size2; j++) {
      for (int k = 1; k <= size3; k++) 
      {
        if (s1[i] == s2[j] && s1[i] == s3[k]) // 三个字母均相等
        {  
          dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
        }
        if (s1[i] == s2[j]) // 两个字母相等
        {  
          dp[i][j][k] = min(dp[i - 1][j - 1][k] + 1, dp[i][j][k]);
        }
        if (s1[i] == s3[k]) // 两个字母相等
        {  
          dp[i][j][k] = min(dp[i - 1][j][k - 1] + 1, dp[i][j][k]);
        }
        if (s2[j] == s3[k]) // 两个字母相等
        {  
          dp[i][j][k] = min(dp[i][j - 1][k - 1] + 1, dp[i][j][k]);
        }
        dp[i][j][k] = GetMinValue({dp[i - 1][j][k] + 1, dp[i][j - 1][k] + 1, dp[i][j][k - 1] + 1, dp[i][j][k]});  // 选取状态转移后最小值
      }
    }
  }
  int i = size1;
  int j = size2;
  int k = size3;

  string ans;
  while (i > 0 && j > 0 && k > 0) 
  {  
    if (dp[i][j][k] == dp[i - 1][j - 1][k - 1] + 1 && (s1[i] == s2[j] && s1[i] == s3[k])) 
    {
      ans.push_back(s1[i]);
      i--;
      j--;
      k--;
    } 
    else if (dp[i][j][k] == dp[i - 1][j - 1][k] + 1 && s1[i] == s2[j]) 
    {
      ans.push_back(s1[i]);
      i--;
      j--;

    } 
    else if (dp[i][j][k] == dp[i - 1][j][k - 1] + 1 && s1[i] == s3[k]) 
    {
      ans.push_back(s1[i]);
      i--;
      k--;
    } 
    else if (dp[i][j][k] == dp[i][j - 1][k - 1] + 1 && s2[j] == s3[k]) 
    {
      ans.push_back(s2[j]);
      j--;
      k--;
    } 
    else 
    {
      int min_val = GetMinValue({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
      if (dp[i - 1][j][k] == min_val) 
      {
        ans.push_back(s1[i]);
        i--;
      } 
      else if (dp[i][j - 1][k] == min_val)
      {
        ans.push_back(s2[j]);
        j--;
      } 
      else 
      {
        ans.push_back(s3[k]);
        k--;
      }
    }
  }
  if (i == 0) // 一个序列为空，使用两序列方法重构超序列
  {  
    ans.append(GetCommonSequence(s2, s3, dp23, j, k));
  } 
  else if (j == 0) 
  {
    ans.append(GetCommonSequence(s1, s3, dp13, i, k));
  } 
  else if (k == 0) 
  {
    ans.append(GetCommonSequence(s1, s2, dp12, i, j));
  }
  reverse(ans.begin(), ans.end());  // 将结果翻转，得到最终超序列
  return ans;
}


string RandString() 
{
  int len = 3;
  std::string str;
  char c;
  for (int i = 0; i < len; i++) 
  {
    c = 'a' + rand() % 6; 
    str.push_back(c);
  }
  return str;
}

void TestFunc() 
{
  int times = 10;
  for (int i = 0; i < times; i++) 
  {
    string s1 = RandString();
    string s2 = RandString();
    string s3 = RandString();
    cout << endl << "test data:" << s1 << " " << s2 << " " << s3 << endl;
    string my_ans = CommonSequenceForThree(s1, s2, s3); 
    cout << "my answer: " << my_ans << endl;
  }
}
int main() 
{
  TestFunc();
  return 0;
}
