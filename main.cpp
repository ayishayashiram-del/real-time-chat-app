#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <set>
#include <ctime>
using namespace std;

struct Message {
    string sender;
    string receiver;
    string content;
    string timestamp;
};

class ChatApp {
private:
    unordered_map<string, vector<Message>> chatHistory;
    queue<Message> messageQueue;
    set<string> activeUsers;

public:
    void login(string username) {
        activeUsers.insert(username);
        cout << username << " is now online.\n";
    }

    void sendMessage(string sender, string receiver, string content) {
        if (activeUsers.find(receiver) == activeUsers.end()) {
            cout << "User not online!\n";
            return;
        }

        Message msg;
        msg.sender = sender;
        msg.receiver = receiver;
        msg.content = content;

        time_t now = time(0);
        msg.timestamp = ctime(&now);

        messageQueue.push(msg);
        cout << "Message queued!\n";
    }

    void processMessages() {
        while (!messageQueue.empty()) {
            Message msg = messageQueue.front();
            messageQueue.pop();

            chatHistory[msg.receiver].push_back(msg);

            cout << "Delivered: " << msg.sender
                 << " -> " << msg.receiver << endl;
        }
    }

    void showChat(string user) {
        cout << "\nChat History for " << user << ":\n";
        for (auto &msg : chatHistory[user]) {
            cout << msg.timestamp
                 << msg.sender << ": "
                 << msg.content << endl;
        }
    }
};

int main() {
    ChatApp app;

    app.login("Alice");
    app.login("Bob");

    app.sendMessage("Alice", "Bob", "Hello!");
    app.sendMessage("Bob", "Alice", "Hi!");

    app.processMessages();

    app.showChat("Bob");
    app.showChat("Alice");

    return 0;
}
