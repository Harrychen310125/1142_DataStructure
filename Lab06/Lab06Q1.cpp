#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct Player { // 玩家結構體，包含名稱和分數
    string name;// 玩家名稱
    int score;// 玩家分數
};

class Card { //建立一個Card類別，用來表示單張撲克牌
public:
    string suit; // 花色
    string rank; // 點數
    Card() {}
    Card(string s, string r) : suit(s), rank(r) {}
    void display() const {
        cout << rank << " of " << suit << endl;
    }
};

class Deck { // 一整副牌（負責建立＋洗牌）
private:
    Card cards[52];// 52 張牌
    int index;// 目前發牌索引
public:
    Deck() : index(0) { // 初始化牌組
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };// 四種花色

        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };// 13 張牌
        int k = 0;
        for (int i = 0; i < 4; i++) {// 4 種花色
            for (int j = 0; j < 13; j++) {// 13 種點數
                cards[k] = Card(suits[i], ranks[j]);
                k++;
            }
        }
    }

    void shuffleDeck() { // 簡單洗牌（隨機交換）
        for (int i = 51; i > 0; i--) {// 從最後一張牌開始，向前遍歷
            int j = rand() % (i + 1);//生成隨機索引 j

            swap(cards[i], cards[j]);// 交換牌組中的兩張牌
        }
    }
    // 取得指定位置的牌
    Card getCard(int i) const {
        return cards[i];
    }
};
// Queue 類別
class Queue { // 用來當牌堆（先進先出）
private:
    vector<Card> deck; // 用來存放卡牌的容器
    int Front;         // 指向牌堆的前端
    int Rear;          // 指向牌堆的尾端
    int capacity;      // 容器最大容量
public:
    Queue(int size) : Front(-1), Rear(-1), capacity(size) {}
    //看有沒有滿
    bool isFull() const { 
        return Rear >= capacity - 1;
    }
    // 看有沒有空
    bool isEmpty() const { 
        return (Front == -1 && Rear == -1) || Front > Rear;
    }
    //放一張牌到尾端
    void enqueue(Card card) {
        if (isFull()) {
            cout << "牌堆已滿，無法插入！" << endl;
            return;
        }
        if (Front == -1) Front = 0;
        deck.push_back(card);
        Rear++;
    }
    //從前面抽掉一張牌
    void dequeue() { 
        if (isEmpty()) {
            cout << "牌堆為空，無法取出牌！" << endl;
            return;
        }
        Front++;

        //如果整個佇列用完就重置
        if (Front > Rear) {
            Front = -1;
            Rear = -1;
            deck.clear();
        }
    }
    //看最前面那張（不移除）
    Card front() const { 
        if (isEmpty()) {
            return Card("", "");
        }
        return deck[Front];
    }
};
//建立＋洗牌＋塞進牌堆
void initializeDeck(Queue& cardDeck) { 
    Deck deck;
    cout << "初始牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display();
    }

    deck.shuffleDeck();

    cout << "\n洗牌後的牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display();
    }

    //把洗好的牌全部丟進 queue
    for (int i = 0; i < 52; i++) {
        cardDeck.enqueue(deck.getCard(i));
    }
}
//發初始兩張牌
void initializePlayer(Player* player, string name, Queue& cardDeck) { 
    player->name = name;
    player->score = 0;
    cout << player->name << " 抽到的牌: ";

    for (int i = 0; i < 2; i++) {
        Card drawnCard = cardDeck.front();
        cardDeck.dequeue();

        cout << drawnCard.rank << " of " << drawnCard.suit << "  ";

        // 計算點數
        if (drawnCard.rank == "A") player->score += 1;
        else if (drawnCard.rank == "J" || drawnCard.rank == "Q" || drawnCard.rank == "K") player->score += 10;
        else player->score += stoi(drawnCard.rank);
    }
    cout << "\n";
    cout << player->name << " 玩家目前分數: " << player->score << endl;
}
//玩家操作
void playerTurn(Player* player, Queue& cardDeck) { 
    char choice;
    while (player->score < 21 && !cardDeck.isEmpty()) {
        cout << player->name << " 現在分數: " << player->score << " 要抽嗎？(h= 抽 , s = 不抽) ";
        cin >> choice;

        if (choice == 'h') {
            Card newCard = cardDeck.front();
            cardDeck.dequeue();

            if (newCard.rank == "A") player->score += 1;
            else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K") player->score += 10;
            else player->score += stoi(newCard.rank);

            cout << player->name << " 抽到: " << newCard.rank << " of " << newCard.suit 
                 << " 總分: " << player->score << endl;

            if (player->score > 21) {
                cout << player->name << " 爆掉了！\n";
                return;
            }
        }
        else if (choice == 's') {
            cout << player->name << " 停牌，最終分數: " << player->score << endl;
            break;
        }
        else {
            cout << "輸入錯誤，請重新輸入\n";
        }
    }
}
//莊家邏輯（小於17就抽）
void dealerTurn(Player* dealer, Queue& cardDeck) { 
    while (dealer->score < 17 && !cardDeck.isEmpty()) {
        Card newCard = cardDeck.front();
        cardDeck.dequeue();

        if (newCard.rank == "A") dealer->score += 1;
        else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K") dealer->score += 10;
        else dealer->score += stoi(newCard.rank);

        cout << "莊家抽到: " << newCard.rank << " of " << newCard.suit 
             << " 總分: " << dealer->score << endl;

        if (dealer->score > 21) {
            cout << "莊家爆了！玩家贏\n";
            return;
        }
    }
}
//比大小
void determineWinner(Player* player, Player* dealer) { 
    if (player->score > 21) cout << player->name << " 爆了，莊家贏\n";
    else if (dealer->score > 21 || player->score > dealer->score)
        cout << player->name << " 贏了\n";
    else if (player->score == dealer->score) cout << "平手\n";
    else cout << "莊家贏\n";
}

int main() {
    srand(time(0));
    Queue cardDeck(52);//宣告牌堆
    initializeDeck(cardDeck);//初始化牌堆

    Player player, dealer;//宣告並初始化莊家以及玩家
    initializePlayer(&player, "玩家", cardDeck);
    initializePlayer(&dealer, "莊家", cardDeck);

    playerTurn(&player, cardDeck);
    if (player.score <= 21) {
        cout << "\n莊家回合...\n";
        dealerTurn(&dealer, cardDeck);
        determineWinner(&player, &dealer);
    }

    return 0;
}
