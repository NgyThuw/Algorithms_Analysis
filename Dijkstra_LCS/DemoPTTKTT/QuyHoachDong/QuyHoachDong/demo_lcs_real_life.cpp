// demo_lcs_real_life.cpp
// DEMO 4: ỨNG DỤNG LCS TRONG ĐỜI SỐNG
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <windows.h>
using namespace std;

// Hàm tính độ dài LCS – tối ưu bộ nhớ (đã dùng ở Demo 3)
int lcs_length(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) curr[j] = prev[j - 1] + 1;
            else curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return prev[m];
}

void run_lcs_real_life() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    cout << string(110, '=') << "\n";
    cout << "          DEMO 4: ỨNG DỤNG CHUỖI CON CHUNG DÀI NHẤT (LCS) TRONG ĐỜI SỐNG\n";
    cout << "                       BẠN ĐANG DÙNG LCS MỖI NGÀY MÀ KHÔNG BIẾT!\n";
    cout << string(110, '=') << "\n\n";

    // ==================== 1. PHÁT HIỆN ĐẠO VĂN CODE ====================
    cout << " 1. PHÁT HIỆN ĐẠO VĂN TRONG LẬP TRÌNH (Plagiarism Detection)\n";
    cout << string(80, '-') << "\n";
    string code1 = "for(int i=0;i<10;i++)cout<<\"Hello\"<<i;";
    string code2 = "for(int i = 0; i < 10; i++) cout << \"Hello\" << i ;";

    int len1 = code1.length(), len2 = code2.length();
    int lcs_code = lcs_length(code1, code2);

    cout << " Đoạn code 1: " << code1 << "\n";
    cout << " Đoạn code 2: " << code2 << "\n\n";
    cout << " → Độ tương đồng: " << lcs_code << " / " << max(len1, len2)
        << " ký tự chung (" << fixed << setprecision(1)
        << 100.0 * lcs_code / max(len1, len2) << "%) \n\n";
    cout << " → Nếu > 80% → rất có thể là ĐẠO CODE!\n\n";
    cout << " Nhiều trường đại học dùng LCS để kiểm tra bài tập C++!\n\n";
    system("pause");

    // ==================== 2. SO SÁNH DNA – SINH HỌC TIN HỌC ====================
    cout << "\n\n 2. SO SÁNH CHUỖI DNA – SINH HỌC TIN HỌC (Bioinformatics)\n";
    cout << string(80, '-') << "\n";
    string dna1 = "GATTACAGATTACA";
    string dna2 = "GATACAGATTACAGA";

    int lcs_dna = lcs_length(dna1, dna2);

    cout << " DNA loài 1: " << dna1 << "\n";
    cout << " DNA loài 2: " << dna2 << "\n\n";
    cout << " → Chuỗi con chung dài nhất: " << lcs_dna << " base\n";
    cout << " → Ví dụ: \"GATTACA\"\n\n";
    cout << " Các nhà khoa học dùng LCS để tìm vùng gen giống nhau giữa các loài!\n";
    cout << " → Giúp xác định họ hàng tiến hóa, phát hiện bệnh di truyền...\n\n";
    system("pause");

    // ==================== 3. GIT DIFF – CÔNG CỤ MÀ AI CŨNG DÙNG ====================
    cout << "\n\n 3. GIT DIFF – BẠN DÙNG LCS MỖI NGÀY KHI CODE!\n";
    cout << string(80, '-') << "\n";
    cout << " Khi bạn gõ lệnh:\n";
    cout << "     git diff file1.cpp file2.cpp\n\n";
    cout << " → Git dùng chính thuật toán LCS để:\n";
    cout << "       • Tìm những dòng giống nhau\n";
    cout << "       • Tô đỏ/xanh phần thêm/bớt\n";
    cout << " → Nếu không có LCS → git diff sẽ chậm kinh khủng!\n\n";
    cout << " GitHub, GitLab, VS Code... đều dùng LCS!\n\n";
    system("pause");

    // ==================== 4. UNIKEY, VIETKEY, GOOGLE DỊCH ====================
    cout << "\n\n 4. GÕ TIẾNG VIỆT & GOOGLE DỊCH CŨNG DÙNG LCS!\n";
    cout << string(80, '-') << "\n";
    cout << " Khi bạn gõ sai chính tả: \"truongf\" → Unikey gợi ý \"trường\"\n";
    cout << " → Nó so sánh LCS giữa từ bạn gõ và từ trong từ điển!\n\n";

    cout << " Google Dịch khi dịch câu dài → cũng dùng LCS để tìm cụm từ giống nhau!\n\n";


    cout << string(110, '=') << "\n";
    cout << "                             KẾT LUẬN CUỐI CÙNG\n";
    cout << string(110, '=') << "\n\n";

    cout << " Bạn nghĩ LCS chỉ là bài toán lý thuyết?\n\n";
    cout << " LCS đang âm thầm chạy trên máy bạn MỖI NGÀY:\n\n";
    cout << " • Khi bạn gõ git diff\n";
    cout << " • Khi bạn gõ tiếng Việt có dấu\n";
    cout << " • Khi bạn dùng Google Dịch\n";
    cout << " • Khi nhà khoa học so sánh DNA\n";
    cout << " • Khi trường đại học kiểm tra đạo văn\n\n";
    cout << string(110, '*') << "\n\n";

    cout << " Nhấn Enter để quay lại menu chính...\n";
    cin.ignore(); cin.get();
}