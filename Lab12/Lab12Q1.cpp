#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


//用來儲存每項商品的基本資訊
struct Product {
    string name;      //商品名稱
    int expiry;       //有效期限(天數)
    int popularity;   //熱銷程度(1~10)
};

//從文字檔讀取商品資料
vector<Product> readFromFile(const string& filename) {
    vector<Product> products;
    ifstream file(filename);

    //檢查檔案是否成功開啟
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return products;
    }

    int n;
    file >> n;        //讀取商品數量
    file.ignore();    //忽略第一行結尾的換行字元

    //逐筆讀取商品資料
    for (int i = 0; i < n; i++) {
        string line;
        getline(file, line);

        //因商品名稱可能包含空白
        //所以利用rfind()從字串尾端尋找空格位置
        size_t lastSpace = line.rfind(' ');
        size_t secondLastSpace = line.rfind(' ', lastSpace - 1);

        try {
            //擷取商品名稱
            string name = line.substr(0, secondLastSpace);

            //擷取有效期限
            int expiry = stoi(
                line.substr(secondLastSpace + 1,
                lastSpace - secondLastSpace - 1));

            //擷取熱銷程度
            int popularity = stoi(line.substr(lastSpace + 1));

            //將商品資料存入vector
            products.push_back({ name, expiry, popularity });
        }
        catch (exception& e) {
            cerr << "Invalid data format at line "
                 << i + 2 << ": " << line << endl;
        }
    }

    file.close();
    return products;
}

//比較函式
//回傳true代表a商品應該排在b商品前面
bool compare(const Product& a, const Product& b) {

    //第一優先條件：
    //有效期限越短，越需要優先處理
    if (a.expiry != b.expiry)
        return a.expiry < b.expiry;

    //第二優先條件：
    //若有效期限相同，則依照熱銷程度排序
    //熱銷程度越高排越前面
    return a.popularity > b.popularity;
}

//Quick Sort排序演算法
void quickSort(vector<Product>& products, int left, int right) {

    //當區間只剩一個元素或沒有元素時停止遞迴
    if (left >= right)
        return;

    //選擇中間元素作為 Pivot
    Product pivot = products[(left + right) / 2];

    int i = left;
    int j = right;

    //分割區間(Partition)
    while (i <= j) {

        //從左邊尋找不符合排序規則的元素
        while (compare(products[i], pivot))
            i++;

        //從右邊尋找不符合排序規則的元素
        while (compare(pivot, products[j]))
            j--;

        //若找到兩個位置需要交換
        if (i <= j) {
            swap(products[i], products[j]);
            i++;
            j--;
        }
    }

    //遞迴處理Pivot左側資料
    quickSort(products, left, j);

    //遞迴處理Pivot右側資料
    quickSort(products, i, right);
}

int main() {

    //指定輸入檔案路徑
    string filename = "C:/input/input3.txt";

    //讀取商品資料
    vector<Product> products = readFromFile(filename);

    //若沒有成功讀取資料則結束程式
    if (products.empty()) {
        cerr << "No valid data found in file." << endl;
        return -1;
    }

    //顯示原始資料
    cout << "Input Products:" << endl;
    for (const Product& p : products) {
        cout << p.name << " "
             << p.expiry << " "
             << p.popularity << endl;
    }

    cout << endl;

    //呼叫Quick Sort進行排序
    quickSort(products, 0, products.size() - 1);

    //顯示排序後結果
    cout << "商品排序:" << endl;
    for (const Product& p : products) {
        cout << p.name << endl;
    }

    system("pause");
    return 0;
}

