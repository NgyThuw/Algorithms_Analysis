// demo_lcs_visual.cpp
// DEMO 2: TRỰC QUAN HÓA BẢNG DP VỚI MŨI TÊN – CHUẨN SÁCH GIÁO KHOA TIN HỌC 12
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

void run_lcs_visual() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    cout << string(100, '=') << "\n";
    cout << "       DEMO 2: TRỰC QUAN HÓA BẢNG DP VỚI MŨI TÊN CHỈ HƯỚNG\n";
    cout << "            Tìm đường đi tạo chuỗi con chung dài nhất (LCS)\n";
    cout << string(100, '=') << "\n\n";

    // Ví dụ
    string X = "ABCBDAB";   // Xâu dọc
    string Y = "BDCAB";     // Xâu ngang

    int n = X.length();
    int m = Y.length();

    cout << " Xâu thứ nhất (X - dọc) : " << X << " (độ dài = " << n << ")\n";
    cout << " Xâu thứ hai  (Y - ngang): " << Y << " (độ dài = " << m << ")\n\n";

    cout << " Ta sẽ xây dựng bảng DP và lưu lại hướng lấy giá trị cho mỗi ô.\n";
    cout << " Mũi tên sẽ giúp ta lần ngược từ cuối về đầu để tìm chuỗi LCS!\n\n";
    cout << " Nhấn Enter để xem bảng hoàn chỉnh với mũi tên...\n";
    cin.ignore(); cin.get();

    // Bảng DP và bảng lưu hướng
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<string>> arrow(n + 1, vector<string>(m + 1, " "));

    // Xây dựng bảng DP và lưu hướng
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                arrow[i][j] = "↖";  // giống nhau → lấy từ góc chéo
            }
            else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                arrow[i][j] = "↑";  // lấy từ trên
            }
            else {
                dp[i][j] = dp[i][j - 1];
                arrow[i][j] = "←";  // lấy từ trái
            }
        }
    }

    // In bảng đẹp với ký hiệu mũi tên
    cout << string(100, '=') << "\n";
    cout << "                   BẢNG QUY HOẠCH ĐỘNG VỚI MŨI TÊN CHỈ HƯỚNG\n";
    cout << string(100, '=') << "\n\n";

    // Dòng đầu: ký tự của Y (ngang)
    cout << "     ∅   ";
    for (char c : Y) cout << c << "   ";
    cout << "\n";

    cout << "   +";
    for (int j = 0; j <= m; ++j) cout << "----+";
    cout << "\n";

    // Các dòng: ký tự X ở bên trái
    for (int i = 0; i <= n; ++i) {
        if (i == 0) cout << " ∅ ";
        else        cout << " " << X[i - 1] << " ";

        cout << "|";

        for (int j = 0; j <= m; ++j) {
            cout << " " << setw(2) << dp[i][j] << arrow[i][j] << " ";
        }
        cout << "|\n";
    }

    cout << "   +";
    for (int j = 0; j <= m; ++j) cout << "----+";
    cout << "\n\n";

    // Kết quả độ dài LCS
    cout << " → Độ dài chuỗi con chung dài nhất = dp[" << n << "][" << m << "] = " << dp[n][m] << "\n\n";

    // Hướng dẫn lần ngược tìm LCS
    cout << string(100, '-') << "\n";
    cout << "               CÁCH LẦN NGƯỢC TỪ GÓC DƯỚI PHẢI ĐỂ TÌM LCS\n";
    cout << string(100, '-') << "\n\n";

    cout << " Bắt đầu từ ô cuối cùng dp[" << n << "][" << m << "]:\n";
    cout << " • Nếu mũi tên ↖ → ký tự X[i-1] và Y[j-1] giống nhau → thêm ký tự này vào LCS\n";
    cout << " • Nếu mũi tên ↑ → đi lên (i--)\n";
    cout << " • Nếu mũi tên ← → đi sang trái (j--)\n\n";

    cout << " Áp dụng với ví dụ này → ta có thể tìm được các LCS sau:\n\n";
    cout << "     • B C A B\n";
    cout << "     • B C B B\n";
    cout << "     • B D A B\n";
    cout << "     • B D B B\n\n";

    cout << " Tất cả đều có độ dài = 4\n\n";

    // Kết luận
    cout << string(100, '=') << "\n";
    cout << "                           KẾT LUẬN KHOA HỌC\n";
    cout << string(100, '=') << "\n\n";

    cout << " • Việc lưu hướng (↖, ↑, ←) trong quá trình xây bảng DP giúp ta:\n";
    cout << "       → Không chỉ biết độ dài LCS\n";
    cout << "       → Mà còn tái tạo lại chính xác chuỗi con chung dài nhất\n\n";

    cout << " • Đây là kỹ thuật \"backtracking trong DP\" rất phổ biến trong:\n";
    cout << "       → Bài toán in đường đi ngắn nhất (Dijkstra, Floyd)\n";
    cout << "       → In dãy con tăng dài nhất (LIS)\n";
    cout << "       → In lời giải bài toán Quy hoạch động nói chung\n\n";

    cout << " → Chỉ cần thêm một bảng arrow → từ \"tính độ dài\" thành \"tìm chính xác lời giải\"!\n\n";

    cout << " Nhấn Enter để quay lại menu chính...\n";
    cin.ignore(); cin.get();
}