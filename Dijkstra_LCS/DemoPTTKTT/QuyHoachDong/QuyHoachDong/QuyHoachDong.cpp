// main.cpp - MENU CHÍNH LCS
#include <iostream>
#include <windows.h>
using namespace std;

void run_lcs_basic();
void run_lcs_visual();
void run_lcs_optimize();
void run_lcs_real_life();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        system("cls");
        cout << string(80, '=') << "\n";
        cout << "       DEMO CHUỖI CON CHUNG DÀI NHẤT (LCS) - QUY HOẠCH ĐỘNG\n";
        cout << string(80, '=') << "\n\n";

        cout << "                           MENU CHÍNH\n";
        cout << string(80, '-') << "\n";
        cout << "  1 → LCS cơ bản – In bảng quy hoạch động chi tiết\n";
        cout << "  2 → Trực quan hóa từng bước xây bảng DP (có mũi tên)\n";
        cout << "  3 → Tối ưu bộ nhớ: chỉ dùng 2 mảng 1 chiều\n";
        cout << "  4 → Ứng dụng thực tế (so code, DNA, git diff...)\n";
        cout << "  5 → Thoát chương trình\n";
        cout << string(80, '-') << "\n";
        cout << "  Nhập lựa chọn (1-5): ";

        int choice;
        cin >> choice;

        if (choice == 5) {
            system("cls");
            cout << string(80, '=') << "\n";
            cout << "       CẢM ƠN THẦY/CÔ ĐÃ XEM DEMO LCS!\n";
            cout << "   Chúc Thầy/Cô giảng bài thật thành công và học sinh mê mẩn!\n";
            cout << "            Made with love for Tin học Việt Nam \n";
            cout << string(80, '=') << "\n";
            break;
        }

        switch (choice) {
        case 1: run_lcs_basic(); break;
        case 2: run_lcs_visual(); break;
        case 3: run_lcs_optimize(); break;
        case 4: run_lcs_real_life(); break;
        default:
            cout << "\n  Lựa chọn không hợp lệ! Nhấn Enter để tiếp tục...\n";
            cin.ignore(); cin.get();
            continue;
        }

        cout << "\n\n  Nhấn Enter để quay lại menu chính...\n";
        cin.ignore();
        cin.get();
    }
    return 0;
}