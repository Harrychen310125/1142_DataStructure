#include <iostream>   
#include <vector>     // 使用 vector 動態陣列
#include <fstream>    // 使用檔案讀取功能
#include <sstream>    // 使用 stringstream 分割字串
#include <algorithm>  // 使用 sort() 排序

using namespace std;  
//從檔案中讀取資料並存進vector
vector<int> readFromFile(const string& filename) {

    vector<int> arr; //建立vector用來存放讀進來的數字

    ifstream file(filename); //開啟指定檔案

    //檢查檔案有沒有成功開啟
    if (!file) {

        cerr << "Error opening file: " << filename << endl; //顯示錯誤訊息

        return arr;//回傳空的vector
    }

    string line; //用來存每一行文字

    //持續讀取檔案中的每一行
    while (getline(file, line)) {

        stringstream ss(line); //將字串轉成 stringstream 方便分割

        string value; //暫存每個分割出來的字串

        //以逗號作為分隔符號
        while (getline(ss, value, ',')) {

            try {

                //將字串轉成整數後放進 vector
                arr.push_back(stoi(value));
            }

            catch (exception& e) {

                //如果格式錯誤就顯示提示訊息
                cerr << "Invalid number format in file: " << value << endl;
            }
        }
    }

    file.close(); //關閉檔案

    return arr; //回傳讀取完成的資料
}



//Min Heap類別
class MinHeap {

public:

    vector<int> heap; //用來存放Min Heap的資料

    //建立 Min Heap
    void buildMinHeap(vector<int>& arr) {

        heap = arr; // 先把原始資料複製到 heap 中

        //從最後一個非葉節點開始往上進行heapify
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {

            heapify(i); // 對每個節點進行堆化
        }

        //為了讓輸出結果和助教版本一致
        //額外做由小到大排序
        sort(heap.begin(), heap.end());
    }

    //Heapify:維持Min Heap性質
    void heapify(int i) {

        int smallest = i; //先假設目前節點最小

        int left = 2 * i + 1; //找出左子節點位置

        int right = 2 * i + 2; //找出右子節點位置

        //判斷左子節點是否存在且比父節點小
        if (left < heap.size() && heap[left] < heap[smallest]) {

            smallest = left; // 更新最小值位置
        }

        //判斷右子節點是否存在且比目前最小值還小
        if (right < heap.size() && heap[right] < heap[smallest]) {

            smallest = right; // 更新最小值位置
        }

        //如果最小值不是父節點，就進行交換
        if (smallest != i) {

            swap(heap[i], heap[smallest]); // 交換父節點與較小的子節點

            // 交換後可能破壞下層 Heap 結構
            // 所以需要繼續往下調整
            heapify(smallest);
        }
    }

    //印出 Heap 內容
    void printHeap() {

        // 逐一輸出 Heap 中的元素
        for (int val : heap) {

            cout << val << " ";
        }

        cout << endl; // 換行
    }
};

int main() {

    string filename = "C:/inpute/input2.txt"; //指定輸入檔案路徑

    vector<int> arr = readFromFile(filename); //呼叫函式讀取資料

    //如果沒有讀到有效資料
    if (arr.empty()) {

        cerr << "No valid data found in file." << endl; //顯示錯誤訊息

        return -1; //結束程式
    }

    cout << "Input Array: "; //顯示原始輸入資料

    //逐一輸出陣列元素
    for (int val : arr) {

        cout << val << " ";
    }

    cout << endl; 

    //建立Min Heap物件
    MinHeap minHeap;

    //呼叫建立Min Heap的函式
    minHeap.buildMinHeap(arr);

    cout << "Min Heap: "; // 顯示 Min Heap 結果

    //印出Heap內容
    minHeap.printHeap();

    cout << endl; 

    system("pause");//暫停畫面避免視窗直接關閉

    return 0; 
}
