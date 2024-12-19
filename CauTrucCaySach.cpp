#include <iostream>
#include <cstring>

using namespace std;

// Cau truc de bieu dien mot node trong cay
struct Node {
    char title[100];     // Tieu de cua muc
    int pages;           // So trang cua muc
    Node* firstChild;    // Con dau tien
    Node* nextSibling;   // Anh chi em tiep theo

    Node(const char* t, int p) {
        strncpy(title, t, 100);
        pages = p;
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};

// Ham them mot node con vao node cha
void addChild(Node* parent, Node* child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node* sibling = parent->firstChild;
        while (sibling->nextSibling) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child;
    }
}

// Dem so chuong cua cuon sach (chi cac node o cap do 1)
int countChapters(Node* root) {
    int count = 0;
    Node* chapter = root->firstChild;
    while (chapter) {
        count++;
        chapter = chapter->nextSibling;
    }
    return count;
}

// Tim chuong dai nhat cua cuon sach (nhieu trang nhat)
Node* findLongestChapter(Node* root) {
    Node* longest = nullptr;
    int maxPages = 0;
    Node* chapter = root->firstChild;
    while (chapter) {
        if (chapter->pages > maxPages) {
            maxPages = chapter->pages;
            longest = chapter;
        }
        chapter = chapter->nextSibling;
    }
    return longest;
}

// Tim va xoa mot muc khoi cay
bool deleteNode(Node* parent, const char* title) {
    Node* prev = nullptr;
    Node* current = parent->firstChild;

    while (current) {
        if (strcmp(current->title, title) == 0) {
            if (prev) {
                prev->nextSibling = current->nextSibling;
            } else {
                parent->firstChild = current->nextSibling;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->nextSibling;
    }

    current = parent->firstChild;
    while (current) {
        if (deleteNode(current, title)) {
            return true;
        }
        current = current->nextSibling;
    }
    return false;
}

// Ham hien thi cay theo cau truc
void displayTree(Node* node, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }
    cout << "- " << node->title << " (" << node->pages << " trang)\n";
    Node* child = node->firstChild;
    while (child) {
        displayTree(child, depth + 1);
        child = child->nextSibling;
    }
}

int main() {
    // Tao root cua cuon sach
    Node* book = new Node("Tieu de sach", 0);

    // Them chuong va cac muc con
    Node* chapter1 = new Node("Chuong 1", 30);
    Node* chapter2 = new Node("Chuong 2", 50);
    addChild(book, chapter1);
    addChild(book, chapter2);

    Node* section1 = new Node("Muc 1.1", 15);
    Node* section2 = new Node("Muc 1.2", 15);
    addChild(chapter1, section1);
    addChild(chapter1, section2);

    // Hien thi cay
    cout << "Cau truc sach:\n";
    displayTree(book);

    // Dem so chuong
    cout << "\nSo chuong: " << countChapters(book) << "\n";

    // Tim chuong dai nhat
    Node* longest = findLongestChapter(book);
    if (longest) {
        cout << "Chuong dai nhat: " << longest->title << " voi " << longest->pages << " trang\n";
    }

    // Xoa mot muc
    cout << "\nXoa 'Muc 1.1'...\n";
    if (deleteNode(book, "Muc 1.1")) {
        cout << "Xoa thanh cong.\n";
    } else {
        cout << "Khong tim thay muc.\n";
    }

    // Hien thi cay sau khi xoa
    cout << "\nCau truc sach sau khi xoa:\n";
    displayTree(book);

    return 0;
}

