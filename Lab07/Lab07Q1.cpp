#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Stack節點結構用 inked list做）
struct Node {
    char data;   //存字（運算子或括號）
    Node* next;  //指到下一個節點
};

// 用linked list實作 Stack
class Stack {
private:
    Node* top; //指向最上面那個
public:
    Stack() { top = nullptr; } //一開始是空的

    // push：把東西放進去
    void push(char ch) {
        Node* newNode = new Node; //建新節點
        newNode->data = ch;       //存資料
        newNode->next = top;      //接到原本的 top
        top = newNode;            //更新 top
    }

    //pop:把最上面的拿掉並回傳
    char pop() {
        if (isEmpty()) return '\0'; //空的就回傳空字元
        char ch = top->data;        //先存要回傳的值
        Node* temp = top;           //暫存目前top
        top = top->next;            //top往下移
        delete temp;                //釋放記憶體
        return ch;
    }

    //peek:只看最上面的值，不拿掉
    char peek() {
        return (top ? top->data : '\0');
    }

    //判斷是不是空stack
    bool isEmpty() {
        return top == nullptr;
    }
};

//判斷運算子的優先順序
int precedence(char op) {
    //乘除優先
    if (op == '*' || op == '/') {
        return 2;
    }
    //加減比較低
    if (op == '+' || op == '-') {
        return 1;
    }
    //其他（像括號）就當最低
    return 0;
}

//中序轉後序
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;
    int j = 0; //postfix的位置

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        //如果是數字或字母，直接輸出
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        //左括號直接丟進 stack
        else if (ch == '(') {
            s.push(ch);
        }
        //右括號就一直pop到遇到左括號
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix[j++] = s.pop();
            }
            s.pop(); //把'(' 丟（不用輸出）
        }
        //運算子處理
        else {
            //如果 stack 裡面有比較高或一樣優先的，就先拿出來
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix[j++] = s.pop();
            }
            s.push(ch);//最後再把自己放進去
        }
    }

    //剩下的全部拿出來
    while (!s.isEmpty()) {
        postfix[j++] = s.pop();
    }

    postfix[j] = '\0'; //字串結尾
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; //輸入中序式

    InfixToPostfix(infix, postfix);//轉換
    cout << "Postfix expression: " << postfix << endl; //印結果

    return 0;
}
