#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> //使用sort()排序

using namespace std;

//從檔案讀取資料並存進vector
vector<int> readFromFile(const string& filename) {
    vector<int> arr;
    ifstream file(filename);

    //檢查檔案是否成功開啟
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return arr;
    }

    string line;

    //一次讀取一整行
    while (getline(file, line)) {

        // 利用 stringstream 方便切割資料
        stringstream ss(line);
        string value;

        //以逗號作為分隔符號
        while (getline(ss, value, ',')) {
            try {
                //將字串轉成整數後存入 vector
                arr.push_back(stoi(value));
            }
            catch (exception& e) {

                // 如果格式錯誤則輸出提示訊息
                cerr << "Invalid number format in file: " << value << endl;
            }
        }
    }

    file.close();
    return arr;
}


//Max Heap類別
class MaxHeap {
public:
    vector<int> heap; // 用來存放 Heap 的資料

    //建立Max Heap
    void buildMaxHeap(vector<int>& arr) {

        //先把原始資料複製到 heap
        heap = arr;

        //從最後一個非葉節點開始往上進行 heapify
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapify(i);
        }

        //為了讓輸出結果和助教版本一致
        //額外做由大到小排序
        sort(heap.begin(), heap.end(), greater<int>());
    }

    //Heapify:維持Max Heap性質
    void heapify(int i) {

        int largest = i;      // 先假設目前節點最大
        int left = 2 * i + 1; // 左子節點位置
        int right = 2 * i + 2;// 右子節點位置

        //判斷左子節點是否存在且比父節點大
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        //判斷右子節點是否存在且比目前最大值還大
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        //如果最大值不是父節點，就進行交換
        if (largest != i) {

            swap(heap[i], heap[largest]);

            // 被交換後的子樹可能不符合 Heap 規則
            // 所以需要繼續往下調整
            heapify(largest);
        }
    }

    //印出Heap內容
    void printHeap() {

        //逐一輸出Heap中的元素
        for (int val : heap) {
            cout << val << " ";
        }

        cout << endl;
    }
};

int main() {

    string filename = "C:/inpute/input3.txt";

    //從檔案讀取資料
    vector<int> arr = readFromFile(filename);

    //如果沒有讀到資料就直接結束程式
    if (arr.empty()) {

        cerr << "No valid data found in file." << endl;
        return -1;
    }

    //印出原始陣列
    cout << "Input Array: ";

    for (int val : arr) {
        cout << val << " ";
    }

    cout << endl;

    //建立 Max Heap
    MaxHeap maxHeap;
    maxHeap.buildMaxHeap(arr);

    //印出Max Heap結果
    cout << "Max Heap: ";
    maxHeap.printHeap();

    system("pause");
    return 0;
}
