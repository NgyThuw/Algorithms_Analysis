// main.cpp 
#include <iostream>
#include <windows.h>   
using namespace std;

void run_demo1();
void run_demo2();
void run_demo3();
void run_demo4();

int main() {
    SetConsoleOutputCP(CP_UTF8);  

    while (true) {
        system("cls");
        cout << string(70, '=') << "\n";
        cout << "        CHƯƠNG TRÌNH DEMO DIJKSTRA & CÁC THUẬT TOÁN TÌM ĐƯỜNG NGẮN NHẤT\n";
        cout << "                     (Phiên bản đẹp như sách giáo khoa Tin học)\n";
        cout << string(70, '=') << "\n\n";

        cout << "                          MENU CHÍNH\n";
        cout << string(70, '-') << "\n";
        cout << "    1 → Dijkstra cơ bản – Bảng chi tiết từng bước như SGK\n";
        cout << "    2 → Dijkstra thất bại 100% khi có cạnh âm & chu trình âm\n";
        cout << "    3 → Hiệu suất Dijkstra trên đồ thị cực lớn (500K đỉnh)\n";
        cout << "    4 → A* (A-Star) nhanh hơn Dijkstra gấp 20-30 lần trên lưới\n";
        cout << "    5 → Thoát chương trình\n";
        cout << string(70, '-') << "\n";
        cout << "    Nhập lựa chọn của bạn (1-5): ";

        int choice;
        cin >> choice;

        if (choice == 5) {
            system("cls");
            cout << string(70, '=') << "\n";
            cout << "       CẢM ƠN THẦY/CÔ ĐÃ XEM DEMO!\n";
            cout << "   Chúc Thầy/Cô một ngày thật vui vẻ và giảng dạy thành công!\n";
            cout << "          Được thực hiện với tất cả tình yêu dành cho Tin học\n";
            cout << string(70, '=') << "\n\n";
            break;
        }

        bool valid = true;
        switch (choice) {
        case 1: run_demo1(); break;
        case 2: run_demo2(); break;
        case 3: run_demo3(); break;
        case 4: run_demo4(); break;
        default:
            valid = false;
            cout << "\n    Lựa chọn không hợp lệ! Vui lòng chọn từ 1 đến 5.\n";
            cout << "    Nhấn Enter để thử lại...\n";
            cin.ignore(); cin.get();
        }

        if (valid) {
            cout << "\n\n    Nhấn Enter để quay lại menu chính...\n";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}