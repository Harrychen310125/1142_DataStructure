class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        //用來記錄每一列是否出現過某個數字
        bool rows[9][9] = {};

        //用來記錄每一行是否出現過某個數字
        bool cols[9][9] = {};

        //用來記錄每個3x3宮格是否出現過某個數字
        bool boxes[9][9] = {};

        //逐格檢查整個數獨
        for (int i = 0; i < 9; i++) {

            for (int j = 0; j < 9; j++) {

                //如果目前位置是空格，直接跳過
                if (board[i][j] == '.')
                    continue;

                //將字元數字轉成陣列索引
                //例如 '1' -> 0、'9' -> 8
                int num = board[i][j] - '1';

                //計算目前數字位於哪個 3x3 宮格
                //宮格編號範圍為 0 ~ 8
                int boxIndex = (i / 3) * 3 + (j / 3);

                //如果該數字已經在同一列、同一行
                //或同一個宮格出現過
                //代表不符合數獨規則
                if (rows[i][num] ||
                    cols[j][num] ||
                    boxes[boxIndex][num]) {

                    return false;
                }

                //紀錄這個數字已經出現過
                rows[i][num] = true;
                cols[j][num] = true;
                boxes[boxIndex][num] = true;
            }
        }

        //全部檢查完都沒有重複
        //代表這個數獨盤面有效
        return true;
    }
};
