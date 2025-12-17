// demo_lcs_tu_dong_giu_ket_luan_khoa_hoc.cpp
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

void run_lcs_basic() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    cout << string(95, '=') << "\n";
    cout << "       CHUỖI CON CHUNG DÀI NHẤT (LCS) – QUY HOẠCH ĐỘNG\n";
    cout << "       Thuật toán tự động – Hoạt động với mọi xâu!\n";
    cout << string(95, '=') << "\n\n";

    // CHỈ CẦN ĐỔI 2 DÒNG NÀY!
    string X = "ABCD";
    string Y = "ACGHBD";

    cout << " Xâu thứ nhất (X) : " << X << "\n";
    cout << " Xâu thứ hai  (Y) : " << Y << "\n\n";

    int n = X.length();
    int m = Y.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    cout << " Máy tính tự động tạo bảng " << (n + 1) << " × " << (m + 1)
        << " và điền từng ô theo quy hoạch động...\n\n";
    cout << " Nhấn Enter để bắt đầu xem quá trình...\n";
    cin.ignore(); cin.get();

    // Hàm in bảng động – tự điều chỉnh theo độ dài xâu
    auto print = [&]() {
        cout << "     ∅ ";
        for (char c : Y) cout << (c == ' ' ? "  " : string(" ") + c);
        cout << "\n   +";
        for (int j = 0; j <= m; j++) cout << "---+";
        cout << "\n";

        for (int i = 0; i <= n; i++) {
            if (i == 0) cout << " ∅ |";
            else        cout << " " << X[i - 1] << "|";

            for (int j = 0; j <= m; j++) {
                cout << " " << setw(2) << dp[i][j];
            }
            cout << " |\n";
        }
        cout << "   +";
        for (int j = 0; j <= m; j++) cout << "---+";
        cout << "\n\n";
        };

    // Thuật toán thật – chạy tự động với mọi xâu
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                cout << "Ô [" << X[i - 1] << "][" << Y[j - 1] << "]: giống nhau → "
                    << dp[i - 1][j - 1] << " + 1 = " << dp[i][j] << "\n";
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                cout << "Ô [" << X[i - 1] << "][" << Y[j - 1] << "]: khác nhau → max("
                    << dp[i - 1][j] << ", " << dp[i][j - 1] << ") = " << dp[i][j] << "\n";
            }
            print();
            system("pause");
            cout << string(60, '-') << "\n";
        }
    }

    cout << string(95, '=') << "\n";
    cout << "                           KẾT LUẬN KHOA HỌC\n";
    cout << string(95, '=') << "\n\n";

    cout << " Thuật toán quy hoạch động đã hoàn thành bảng dp[" << n + 1 << "][" << m + 1 << "]\n";
    cout << " Giá trị tại ô dp[" << n << "][" << m << "] = " << dp[n][m] << "\n\n";

    cout << " Theo định lý quy hoạch động cho bài toán LCS:\n";
    cout << "     dp[i][j] = độ dài chuỗi con chung dài nhất của\n";
    cout << "                X[0..i-1] và Y[0..j-1]\n\n";

    cout << " Do đó:\n";
    cout << "     dp[" << n << "][" << m << "] = độ dài chuỗi con chung dài nhất của toàn bộ X và Y\n";
    cout << "     → Độ dài LCS(X, Y) = " << dp[n][m] << "\n\n";

    cout << " Kết quả đúng với ví dụ hiện tại:\n";
    cout << "     X = \"" << X << "\"\n";
    cout << "     Y = \"" << Y << "\"\n";
    cout << "     → Độ dài LCS = " << dp[n][m] << " (ví dụ: \"TRƯỜNG THPT CHUYÊN HÀ NỘI\")\n\n";

    cout << string(95, '-') << "\n";
    cout << " TÓM TẮT THUẬT TOÁN LCS (CHUẨN SGK TIN HỌC 12):\n";
    cout << string(95, '-') << "\n";
    cout << " 1. Tạo bảng dp[n+1][m+1], khởi tạo toàn bộ = 0\n";
    cout << " 2. Với mỗi i từ 1 đến n, mỗi j từ 1 đến m:\n";
    cout << "        nếu X[i-1] == Y[j-1] → dp[i][j] = dp[i-1][j-1] + 1\n";
    cout << "        ngược lại           → dp[i][j] = max(dp[i-1][j], dp[i][j-1])\n";
    cout << " 3. Kết quả: dp[n][m]\n\n";

    cout << " Đây là một trong những bài toán kinh điển của kỹ thuật Quy hoạch động,\n";
    cout << " được sử dụng rộng rãi trong so sánh văn bản, sinh học tin học, và công cụ diff.\n\n";

    cout << string(95, '=') << "\n";
    cout << "                   HOÀN THÀNH DEMO – CHÍNH XÁC 100%\n";
    cout << string(95, '=') << "\n\n";

    cout << " Nhấn Enter để quay lại menu chính...\n";
    cin.ignore(); cin.get();
}