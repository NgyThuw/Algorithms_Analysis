// demo_lcs_optimize.cpp
// DEMO 3: TỐI ƯU BỘ NHỚ LCS – CHỈ DÙNG 2 DÒNG 
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

void run_lcs_optimize() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    cout << string(100, '=') << "\n";
    cout << "       DEMO 3: TỐI ƯU BỘ NHỚ CHO BÀI TOÁN LCS\n";
    cout << "               Chỉ dùng 2 mảng 1 chiều – Tiết kiệm cực lớn!\n";
    cout << string(100, '=') << "\n\n";

    string X = "NGUYỄN VĂN AN";
    string Y = "NGUYỄN THỊ BÍCH";

    int n = X.length();  // 13
    int m = Y.length();  // 16

    cout << " Xâu thứ nhất (X) : " << X << " (độ dài = " << n << ")\n";
    cout << " Xâu thứ hai  (Y) : " << Y << " (độ dài = " << m << ")\n\n";

    cout << " Nếu dùng cách thông thường → cần bảng DP: " << (n + 1) << " × " << (m + 1)
        << " = " << (n + 1) * (m + 1) << " ô\n";
    cout << " → Tốn " << (n + 1) * (m + 1) * 4 << " byte ≈ "
        << fixed << setprecision(1) << (n + 1) * (m + 1) * 4 / 1024.0 << " KB bộ nhớ!\n\n";

    cout << " Nhưng ta chỉ cần biết độ dài LCS → KHÔNG cần lưu cả bảng!\n";
    cout << " → Chỉ cần 2 dòng là đủ!\n\n";
    cout << " Nhấn Enter để xem thuật toán tối ưu hoạt động...\n";
    cin.ignore(); cin.get();

    // === TỐI ƯU BỘ NHỚ: CHỈ DÙNG 2 MẢNG ===
    vector<int> prev(m + 1, 0);   // Dòng trước đó
    vector<int> curr(m + 1, 0);   // Dòng hiện tại

    cout << string(100, '-') << "\n";
    cout << "                 QUÁ TRÌNH TÍNH TOÁN VỚI 2 DÒNG\n";
    cout << string(100, '-') << "\n\n";

    for (int i = 1; i <= n; ++i) {
        cout << "Đang xử lý ký tự X[" << i << "] = '" << X[i - 1] << "' (dòng " << i << ")\n";

        for (int j = 1; j <= m; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                curr[j] = prev[j - 1] + 1;
                cout << "   → '" << X[i - 1] << "' == '" << Y[j - 1] << "' → curr[" << j << "] = prev[" << j - 1 << "] + 1 = " << curr[j] << "\n";
            }
            else {
                curr[j] = max(prev[j], curr[j - 1]);
                cout << "   → '" << X[i - 1] << "' ≠ '" << Y[j - 1] << "' → curr[" << j << "] = max(" << prev[j] << ", " << curr[j - 1] << ") = " << curr[j] << "\n";
            }
        }

        // In 2 dòng hiện tại để học sinh thấy rõ
        cout << "   Dòng trước (prev): ";
        for (int j = 0; j <= m; ++j) cout << setw(3) << prev[j];
        cout << "\n   Dòng hiện tại (curr): ";
        for (int j = 0; j <= m; ++j) cout << setw(3) << curr[j];
        cout << "\n\n";

        prev = curr;  // Chuyển dòng hiện tại thành dòng trước cho vòng sau
        system("pause");
    }

    int lcs_length = prev[m];

    cout << string(100, '=') << "\n";
    cout << "                           HOÀN THÀNH!\n";
    cout << string(100, '=') << "\n\n";

    cout << " Độ dài LCS = " << lcs_length << "\n";
    cout << " → Chuỗi con chung dài nhất: \"NGUYỄN \" (7 ký tự)\n\n";

    cout << string(100, '-') << "\n";
    cout << "                     SO SÁNH BỘ NHỚ\n";
    cout << string(100, '-') << "\n";
    cout << " • Cách thông thường: " << (n + 1) * (m + 1) << " ô × 4 byte = " << (n + 1) * (m + 1) * 4 << " byte\n";
    cout << " • Cách tối ưu     : chỉ 2 dòng × " << (m + 1) << " ô = " << 2 * (m + 1) * 4 << " byte\n";
    cout << " → Tiết kiệm: " << fixed << setprecision(1)
        << 100.0 * (1.0 - 2.0 * (m + 1) / (n + 1) / (m + 1)) << "% bộ nhớ!\n\n";

    cout << string(100, '=') << "\n";
    cout << "                           KẾT LUẬN KHOA HỌC\n";
    cout << string(100, '=') << "\n\n";

    cout << " • Khi chỉ cần độ dài LCS (không cần in chuỗi) → ta có thể loại bỏ toàn bộ bảng DP!\n";
    cout << " • Chỉ cần 2 mảng 1 chiều: prev (dòng trước) và curr (dòng hiện tại)\n";
    cout << " • Độ phức tạp bộ nhớ: từ O(n × m) → O(m) (hoặc O(min(n,m)))\n\n";

    cout << " Đây là kỹ thuật tối ưu bộ nhớ kinh điển trong Quy hoạch động:\n";
    cout << "     → Dùng trong các bài xâu dài hàng nghìn ký tự (DNA, log file...)\n";
    cout << "     → Áp dụng được cho LIS, Edit Distance, Knapsack 1D, v.v.\n\n";

    cout << " → Chỉ thay đổi 1 chút → tiết kiệm hàng chục nghìn lần bộ nhớ!\n";
    cout << " → Đây chính là sức mạnh của tư duy tối ưu trong Tin học!\n\n";

    cout << " Nhấn Enter để quay lại menu chính...\n";
    cin.ignore(); cin.get();
}