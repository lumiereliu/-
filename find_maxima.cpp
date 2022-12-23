#include <bits/stdc++.h>
using namespace std;

class Point {
 public:
  int x_;
  int y_;
  Point(int x, int y) : x_(x), y_(y) {}
  bool IsDominated(const Point& p) const 
  {                                      
    if (x_ < p.x_ && y_ < p.y_) return true;
    return false;
  }
  bool operator>(const Point& p) const 
  {           
    if (x_ > p.x_ || (x_ == p.x_ && y_ < p.y_)) 
    {  
      return true;
    }
    return false;
  }
  bool operator!=(const Point& p) const { return !(x_ == p.x_ && y_ == p.y_); }  
};

vector<Point> GreedFindAnswer(vector<Point> points) // 使用贪心算法找到所有maxima
{  
  vector<Point> accepted_answer;
  sort(points.begin(), points.end(), greater<Point>());
  int maxY = points[0].y_;
  accepted_answer.push_back(points[0]);                              
  for (int i = 1; i < points.size(); ++i) 
  {
    if (points[i].y_ >= maxY) 
    { 
      accepted_answer.push_back(points[i]);
      maxY = points[i].y_;
    }
  }
  return accepted_answer;
}

vector<Point> TraversalFindAnswer(vector<Point> points) 
{
  vector<Point> accepted_answer;
  bool is_maxima;
  for (int i = 0; i < points.size(); ++i) 
  {  
    is_maxima = true;
    for (int j = 0; j < points.size(); ++j) 
    {
      if (points[i].IsDominated(points[j])) 
      {  
        is_maxima = false;
        break;
      }
    }
    if (is_maxima) 
    {
      accepted_answer.push_back(points[i]);
    }
  }
  return accepted_answer;
}

// 生成测试数据，groups为测试数据组数
vector<vector<Point>> GenerateTestData(int groups) 
{
  vector<vector<Point>> res;
  int data_size;
  int rand_data;
  int x, y;
  for (int i = 0; i < groups; i++) 
  {
    data_size = rand() % 10 + 1; 
    vector<Point> tmp;
    for (int j = 0; j < data_size; j++) 
    {
      x = rand() % 100; 
      y = rand() % 100; 
      tmp.push_back(Point{x, y});
    }
    res.push_back(tmp);
  }
  return res;
}

// 输出提示信息与测试数据
void PrintInformation(const vector<Point>& points, string information) 
{
  cout << information << endl;
  for (int i = 0; i < points.size(); ++i) 
  {
    cout << '(' << points[i].x_ << ',' << points[i].y_ << ')';
  }
  cout << endl;
}
// 测试函数
void TestFunction() 
{
  int groups = 10;
  auto datas = GenerateTestData(groups);  // 获取测试数据
  for (int i = 0; i < groups; ++i) 
  {
    auto accepted_answer = TraversalFindAnswer(datas[i]);     // 获取正确结果
    auto algorithm_res = GreedFindAnswer(datas[i]);  // 获取算法结果
    cout << endl << "data size:" << datas[i].size() << endl;
    sort(datas[i].begin(), datas[i].end(), greater<Point>());
    sort(accepted_answer.begin(), accepted_answer.end(), greater<Point>());
    sort(algorithm_res.begin(), algorithm_res.end(), greater<Point>());
    PrintInformation(datas[i], "test data");
    PrintInformation(accepted_answer, "accepted answer");
    PrintInformation(algorithm_res, "my accepted accepted answer");
  }
}

int main() 
{
  srand(time(0));  // 随机种子
  TestFunction();
}
