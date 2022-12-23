#include <bits/stdc++.h>
using namespace std;

int Partition(vector<double>& array, int low, int high, double x) //利用x将数组划分为2部分
{  
  
  int i = low;
  high--;
  while (array[i] != x) i++;
  swap(array[low], array[i]); 
  while (low < high) 
  {
    while (low < high && array[high] >= x) high--;
    array[low] = array[high];
    while (low < high && array[low] <= x) low++;
    array[high] = array[low];
  }
  array[low] = x;
  return low;
}

double Select(vector<double>& array, int low, int high, int k) 
{
  int n = high - low;  // n为数组a[low...high]元素个数,注意右边最多取到a[high-1]
  if (n < 5) //元素小于5时候单独处理
  {         
    sort(array.begin() + low, array.begin() + high);
    return array[low + k - 1];
  }
  for (int i = 0; i < n / 5; i++) 
  {
    sort(array.begin() + low + i * 5, array.begin() + low + i * 5 + 5);  //对每组数据排序
    swap(array[low + i], array[low + i * 5 + 2]);                        //中位数移到前面
  }
  double x = Select(array, low, low + n / 5, n / 10 + 1);  //寻找中位数的中位数、n/10+1非常重要，避免n<10时n/10==0此时会出现问题
  int j = Partition(array, low, high, x);                  //根据x将数组a划分为2部分，j为x所在数组下标
  int q = j - low + 1;                                 // q为小于或者等于x元素的个数
  if (q == k)
    return x;
  else if (q > k)
    return Select(array, low, j + 1, k);
  else
    return Select(array, j + 1, high, k - q);
}

double FindKthSmallest(vector<double> nums, int k) 
{  
  return Select(nums, 0, nums.size(), k + 1);
}


vector<double> AlgorithmImpl(vector<double> data) 
{
  int size = static_cast<int>(data.size());
  int result_size = size / 4;
  vector<double> result;
  result.reserve(size);
  vector<double> diff;
  diff.reserve(size);

  double median = (FindKthSmallest(data, size / 2) + FindKthSmallest(data, (size - 1) / 2)) / 2;  // 计算中位数
  for (int num : data) 
  {                                                                          
    diff.emplace_back(abs(num - median));// 计算各数与中位数中间差值的绝对值
  }
  double k_smallest_diff = FindKthSmallest(diff, result_size);  // 找到差值中第k小的数
  vector<double> k_smallest;
  for (int i = 0; i < size; i++) 
  {
    if (diff[i] < k_smallest_diff) // 差值更小的数，加入结果集
    {  
      result.emplace_back(data[i]);
    }
    if (diff[i] == k_smallest_diff) // 记录差值刚好为第k小的数
    {  
      k_smallest.emplace_back(data[i]);
    }
  }
  int cnt = result_size - result.size();
  result.insert(result.end(), k_smallest.begin(), k_smallest.begin() + cnt);  // 加入差值恰好为第k小的数
  return result;
}

// 生成测试数据，group为测试数据组数
vector<vector<double>> GenerateTestData(int groups) 
{
  vector<vector<double>> res;
  int data_size;
  int rand_data;
  for (int i = 0; i < groups; i++) 
  {
    data_size = rand() % 20+10;  // 测试数据规模为10-30
    vector<double> tmp;
    tmp.reserve(data_size);
    for (int j = 0; j < data_size; j++) 
    {
      rand_data = rand() % 100;  // 测试数据在0-100之间
      tmp.emplace_back(rand_data);
    }
    res.emplace_back(tmp);
  }
  return res;
}

// 输出提示信息与测试数据
void PrintInformation(const vector<double>& data, string information) 
{
  cout << information << endl;
  for (auto num : data) 
  {
    cout << num << " ";
  }
  cout << endl;
}

double GetMedian(vector<double> data)
{  
  int size = static_cast<int>(data.size());
  sort(data.begin(), data.end());

  double median = (data[size / 2] + data[(size - 1) / 2]) / 2;
  return median;
}

// 获取测试数据与中位数相近的n/4个数，不考虑时间复杂度
vector<double> GetTestAnswer(vector<double> test_data) 
{
  int size = static_cast<int>(test_data.size());

  double median = GetMedian(test_data);
  auto compare_fun = [&](double n1, double n2) 
  {  
    if (abs(n1 - median) < abs(n2 - median)) 
    {
      return true;
    }
    return false;
  };
  sort(test_data.begin(), test_data.end(), compare_fun);  // 将数组按比较函数排定
  vector<double> res(test_data.begin(), test_data.begin() + size / 4);  // 选取前size / 4个数
  return res;
}

// 测试函数
void TestFunc() 
{
  int groups = 10;
  auto datas = GenerateTestData(groups);  // 获取测试数据
  for (int i = 0; i < groups; ++i) 
  {
    auto accepted_answer = GetTestAnswer(datas[i]);         // 获取正确结果
    auto algorithm_res = AlgorithmImpl(datas[i]);  // 获取算法结果
    double median = GetMedian(datas[i]);
    cout  << endl << "data size:" << datas[i].size() << endl;
    sort(datas[i].begin(), datas[i].end());
    PrintInformation(datas[i], "test data");
    cout << "median:" << median << endl;
    sort(accepted_answer.begin(), accepted_answer.end());
    sort(algorithm_res.begin(), algorithm_res.end());
    PrintInformation(accepted_answer, "accepted answer");
    PrintInformation(algorithm_res, "my answer");  
  }
}

int main() 
{
  srand(time(0));  // 随机种子
  TestFunc();
}
