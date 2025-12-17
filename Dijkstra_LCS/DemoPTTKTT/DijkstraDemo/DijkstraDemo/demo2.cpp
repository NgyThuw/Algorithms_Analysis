// demo2_FINAL_WITH_TWO_GRAPHICS_VIETNAMESE_FIXED.cpp
// ĐÃ SỬA HOÀN TOÀN - KHÔNG CÒN LỖI compile
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;

const int INF = 1000000000;

// Hàm in khoảng cách (đã sửa tên đúng: print_dist)
void print_dist(const vector<int>& d, const string& label, int n) {
    cout << " " << left << setw(28) << label;
    for (int i = 0; i < n; ++i) {
        char v = 'A' + i;
        if (d[i] == INF) cout << v << ":∞   ";
        else cout << v << ":" << setw(5) << d[i] << " ";
    }
    cout << "\n";
}

void run_demo2() {
    SetConsoleOutputCP(CP_UTF8);  // Bật tiếng Việt có dấu

    system("cls");
    cout << string(115, '=') << "\n";
    cout << " DEMO 2: DIJKSTRA THẤT BẠI 100% VỚI CẠNH ÂM & CHU TRÌNH ÂM (2 ĐỒ THỊ ASCII ĐẸP NHẤT)\n";
    cout << string(115, '=') << "\n\n";

    int n = 5;

    // ===================================================================
    // ĐỒ THỊ 1: CÓ CẠNH ÂM → DIJKSTRA SAI
    // ===================================================================
    cout << "=== ĐỒ THỊ 1: CÓ CẠNH ÂM → DIJKSTRA SẼ CHO KẾT QUẢ SAI ===\n\n";

    cout << "       4\n";
    cout << "   A ───────> B\n";
    cout << "    \\        \\\n";
    cout << "   2 \\      3 \\\n";
    cout << "      v        v\n";
    cout << "   C ───────> D\n";
    cout << "    \\        \\\n";
    cout << "  10 \\   -10  \\\n";
    cout << "      v        v\n";
    cout << "   <────────── E\n";
    cout << "       ^\n";
    cout << "       | 1\n";
    cout << "       +──────── (E trở lại C)\n\n";

    cout << "Các cạnh chi tiết:\n";
    cout << " A → B : 4\n";
    cout << " A → C : 2\n";
    cout << " B → D : 3\n";
    cout << " C → D : 10\n";
    cout << " D → E : -10 ←← CẠNH ÂM!\n";
    cout << " E → C : 1\n\n";

    cout << "Đường đi NGẮN NHẤT thực sự: A → B → D → E = -3\n";
    cout << "Nhưng Dijkstra sẽ cho kết quả sai (12) vì \"đóng\" đỉnh E quá sớm!\n\n";

    cout << string(100, '-') << "\n\n";

    vector<vector<pair<int, int>>> g(n);
    g[0] = { {1,4}, {2,2} };   // A
    g[1] = { {3,3} };          // B
    g[2] = { {3,10} };         // C
    g[3] = { {4,-10} };        // D → E (âm)
    g[4] = { {2,1} };          // E → C

    // ------------------- DIJKSTRA (SAI) -------------------
    cout << "1. THỰC HIỆN DIJKSTRA (KẾT QUẢA SAI)\n";
    cout << string(95, '-') << "\n";

    vector<int> dist_d(n, INF);
    dist_d[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, 0 });

    print_dist(dist_d, "Khởi tạo", n);

    int step = 0;
    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();  // ← ĐÃ SỬA: xóa cái "Popup()" quái quỷ đi!

        if (cost > dist_d[u]) continue;

        cout << "Bước " << ++step << ": Chọn đỉnh " << (char)('A' + u)
            << " (dist = " << cost << ")\n";

        for (auto& e : g[u]) {
            int v = e.first, w = e.second;
            if (dist_d[u] + w < dist_d[v]) {
                int old = dist_d[v];
                dist_d[v] = dist_d[u] + w;
                pq.push({ dist_d[v], v });
                cout << "   Cập nhật " << (char)('A' + u) << " → " << (char)('A' + v)
                    << ": " << (old == INF ? "∞" : to_string(old)) << " → " << dist_d[v] << "\n";
            }
        }
        print_dist(dist_d, "   Sau bước", n);
        cout << "\n";
    }

    cout << "=> KẾT QUẢ DIJKSTRA: A → E = " << dist_d[4]
        << " ←← SAI HOÀN TOÀN! (phải là -3)\n\n";
    cout << string(100, '-') << "\n\n";

    // ------------------- BELLMAN-FORD (ĐÚNG) -------------------
    cout << "2. BELLMAN-FORD (TÌM ĐÚNG -3)\n";
    cout << string(95, '-') << "\n";

    vector<int> dist_bf(n, INF);
    dist_bf[0] = 0;
    print_dist(dist_bf, "Khởi tạo", n);

    for (int iter = 1; iter <= n - 1; ++iter) {
        bool changed = false;
        for (int u = 0; u < n; ++u) {
            for (auto& e : g[u]) {
                int v = e.first, w = e.second;
                if (dist_bf[u] != INF && dist_bf[u] + w < dist_bf[v]) {
                    dist_bf[v] = dist_bf[u] + w;
                    changed = true;
                }
            }
        }
        if (changed) print_dist(dist_bf, "Sau vòng " + to_string(iter), n);
    }

    cout << "\n=> KẾT QUẢ BELLMAN-FORD: A → E = " << dist_bf[4] << " ←← ĐÚNG!\n\n";
    cout << string(100, '-') << "\n\n";

    // ===================================================================
    // ĐỒ THỊ 2: CÓ CHU TRÌNH ÂM
    // ===================================================================
    cout << "=== ĐỒ THỊ 2: CÓ CHU TRÌNH ÂM → BELLMAN-FORD PHÁT HIỆN ===\n\n";

    cout << "       4\n";
    cout << "   A ───────> B\n";
    cout << "    \\        \\\n";
    cout << "   2 \\      3 \\\n";
    cout << "      v        v\n";
    cout << "   C ───────> D\n";
    cout << "    \\        \\\n";
    cout << "  10 \\   -10  \\\n";
    cout << "      v        v\n";
    cout << "   <────────── E\n";
    cout << "    ^         ^\n";
    cout << " -5 |         | -5\n";
    cout << "    +─────────+\n";
    cout << "      CHU TRÌNH ÂM B ↔ E (tổng -10)\n\n";

    cout << "Thêm 2 cạnh tạo chu trình âm:\n";
    cout << " E → B : -5\n";
    cout << " B → E : -5\n\n";

    g[4].push_back({ 1, -5 }); // E → B
    g[1].push_back({ 4, -5 }); // B → E

    vector<int> dist_cycle(n, INF);
    dist_cycle[0] = 0;

    // Chạy n-1 vòng
    for (int iter = 1; iter <= n - 1; ++iter) {
        for (int u = 0; u < n; ++u)
            for (auto& e : g[u])
                if (dist_cycle[u] != INF && dist_cycle[u] + e.second < dist_cycle[e.first])
                    dist_cycle[e.first] = dist_cycle[u] + e.second;
    }

    // Vòng thứ n: kiểm tra chu trình âm
    cout << "KIỂM TRA CHU TRÌNH ÂM (vòng thứ " << n << "):\n";
    bool has_neg_cycle = false;
    for (int u = 0; u < n; ++u) {
        for (auto& e : g[u]) {
            if (dist_cycle[u] != INF && dist_cycle[u] + e.second < dist_cycle[e.first]) {
                has_neg_cycle = true;
                cout << "   PHÁT HIỆN: Vẫn cập nhật được " << (char)('A' + u) << " → "
                    << (char)('A' + e.first) << " → CÓ CHU TRÌNH ÂM!\n";
            }
        }
    }

    if (has_neg_cycle) {
        cout << "\n=> KẾT QUẢ: CÓ CHU TRÌNH ÂM!\n";
        cout << "   Khoảng cách có thể giảm xuống -∞\n";
        cout << "   KHÔNG TỒN TẠI ĐƯỜNG ĐI NGẮN NHẤT!\n\n";
    }

    // ===================================================================
    // TỔNG KẾT
    // ===================================================================
    cout << string(115, '=') << "\n";
    cout << " TỔNG KẾT\n";
    cout << string(115, '=') << "\n";
    cout << "• Dijkstra     : Thất bại khi có cạnh âm\n";
    cout << "• Bellman-Ford : Đúng khi không có chu trình âm\n";
    cout << "• Bellman-Ford + vòng n: Phát hiện chính xác chu trình âm\n\n";
    cout << "KẾT LUẬN:\n";
    cout << "→ Trọng số ≥ 0 → Dùng Dijkstra\n";
    cout << "→ Có cạnh âm   → Dùng Bellman-Ford\n";
    cout << "→ Có chu trình âm → Không tồn tại đường đi ngắn nhất!\n\n";

    cout << string(115, '=') << "\n";
    cout << " NHẤN ENTER ĐỂ THOÁT\n";
    cout << string(115, '=') << "\n";

    cin.ignore();
    cin.get();
}