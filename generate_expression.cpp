#include <bits/stdc++.h>
using namespace std;

enum Operator {add, subtract, multiple, divide};
double CalculateSimple(double left_element, double right_element, Operator op)
{  
  double ans;
  switch (op) 
  {
    case add:
      return left_element + right_element;
    case subtract:
      return left_element - right_element;  
    case multiple:
      return left_element * right_element;
    case divide:
      return left_element / right_element;
  }
  return -1;
}

double CalculateDifficult(vector<double> num, vector<Operator> ops) 
{  
  stack<double> num_stack;
  stack<Operator> operator_stack;
  double left_element, right_element, res;
  Operator op;
  num_stack.push(num[0]);
  int size = num.size();
  for (int i = 0; i < size - 1; ++i) 
  {
    if (ops[i] == multiple || ops[i] == divide) // 若为乘除，直接计算
    {  
      left_element = num_stack.top();
      num_stack.pop();
      right_element = num[i + 1];
      res = CalculateSimple(left_element, right_element, ops[i]);
      num_stack.push(res);
    } 
    else // 若为加减，先入栈
    {  
      num_stack.push(num[i + 1]);
      operator_stack.push(ops[i]);
    }
  }
  while (!operator_stack.empty()) // 将符号栈的操作符一一弹出，进行计算
  {  
    op = operator_stack.top();
    operator_stack.pop();
    right_element = num_stack.top();
    num_stack.pop();
    left_element = num_stack.top();
    num_stack.pop();
    res = CalculateSimple(left_element, right_element, op);
    num_stack.push(res);
  }
  return num_stack.top();  // 得到表达式最终结果
}

template <typename T>
void dfs(vector<vector<T>>& res, vector<T> & sample, vector<T> & path, int depth, vector<int> & visited) // 回溯法 深度优先搜索
{  
  if (depth == sample.size()) 
  {
    res.push_back(path);
    return;
  } 
  
  for (int i = 0; i <= sample.size(); ++i) 
  {
    if(!visited[i])
    {
      path.push_back(sample[i]);
      visited[i] = 1;
      dfs(res, sample, path, depth+1, visited);
      path.pop_back();
      visited[i] = 0;  // 还原
    }
  }
  
}

void PrintExpression(vector<double> num, vector<Operator> ops, int n) // 输出表达式
{  
  int size = ops.size();
  for (int i = 0; i < size; i++) 
  {
    cout << " " << num[i] << " ";
    switch (ops[i]) {
      case add:
        cout << '+';
        break;
      case subtract:
        cout << '-';
        break;
      case multiple:
        cout << '*';
        break;
      case divide:
        cout << '/';
        break;
    }
  }
  cout << " " << num[size] << " = " << n << endl;
}

void GetExpression(vector<double> num, int n) 
{
  vector<vector<double>> possible_nums;
  vector<vector<Operator>> possible_ops;
  vector<Operator> ops = {add, subtract, multiple, divide};
  vector<double> path_nums;
  vector<Operator> path_operators;
  vector<int> visited_num(num.size());
  vector<int> visited_operator(ops.size());
  dfs(possible_nums, num, path_nums, 0, visited_num);  // 得到可能的数字排列集合
  dfs(possible_ops, ops, path_operators, 0, visited_operator);  // 得到可能的运算符排列集合
  bool find = false;
  for (int i = 0; i < possible_nums.size(); ++i) // 双重循环，计算所有可能的表达式
  {  
    for (int j = 0; j < possible_ops.size(); ++j) 
    {
      double res = CalculateDifficult(possible_nums[i], possible_ops[j]);
      if (res == n) // 若与目标值一致，输出表达式
      {  
        PrintExpression(possible_nums[i], possible_ops[j], n);
        find = true;
      }
    }
  }
  if (!find) // 未找到相应的表达式
  {  
    cout << "No suitable expression was found" << endl;
  }
}


int main() 
{
  GetExpression({1, 2, 3, 4, 5}, 10);
  cout << endl;
  GetExpression({1, 2, 3, 4, 5}, 15);
  cout << endl;
  GetExpression({1, 2, 3, 4, 5}, 20);
  return 0;
}