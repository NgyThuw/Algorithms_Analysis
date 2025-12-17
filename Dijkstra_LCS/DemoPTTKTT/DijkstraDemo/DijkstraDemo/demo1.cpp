// demo1_ULTIMATE_VIETNAM_TEXTBOOK.cpp
// BẢNG - CÓ TÊN ĐỈNH TRONG [] - DỄ ĐỐI CHIẾU
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <random>
#include <cctype>
#include <algorithm>
#include <windows.h>        // Thêm để hỗ trợ tiếng Việt có dấu
using namespace std;

const int INF = 1000000000;
mt19937 rng(2025);

// In hàng đợi đẹp
string format_pq(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q) {
    if (q.empty()) return "{ rỗng }";
    vector<string> items;
    while (!q.empty()) {
        items.push_back(string(1, 'A' + q.top().second) + ":" + to_string(q.top().first));
        q.pop();
    }
    string res = "{ ";
    for (int i = (int)items.size() - 1; i >= 0; i--) {
        res += items[i];
        if (i > 0) res += ", ";
    }
    res += " }";
    return res;
}

// In tên các đỉnh trong header: dist[A B C ...]
string get_vertex_header(int n) {
    string s = "[";
    for (int i = 0; i < n; i++) {
        s += 'A' + i;
        if (i < n - 1) s += " ";
    }
    s += "]";
    return s;
}

void dijkstra_perfect_table(const vector<vector<pair<int, int>>>& g, int start, int goal, int n) {
    vector<int> dist(n, INF), prev(n, -1);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });
    string header = get_vertex_header(n);

    cout << string(135, '=') << "\n";
    cout << " THỰC HIỆN THUẬT TOÁN DIJKSTRA TỪ " << (char)('A' + start)
        << " ĐẾN " << (char)('A' + goal) << " (" << n << " đỉnh)\n";
    cout << string(135, '=') << "\n\n";

    // Header bảng 
    cout << left
        << setw(6) << "Bước"
        << setw(10) << "Chọn"
        << setw(45) << ("dist" + header)
        << setw(35) << ("prev" + header)
        << "Hàng đợi ưu tiên\n";
    cout << string(135, '-') << "\n";

    int step = 0;
    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (cost > dist[u]) continue;

        // In dòng chính của bước
        cout << left
            << setw(6) << step++
            << setw(10) << (char)('A' + u) << " ";

        // In dist[]
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) cout << setw(5) << "∞";
            else cout << setw(5) << dist[i];
        }
        cout << " ";

        // In prev[]
        for (int i = 0; i < n; i++) {
            if (prev[i] == -1) cout << setw(3) << "-";
            else cout << setw(3) << (char)('A' + prev[i]);
        }
        cout << " " << format_pq(pq) << "\n";

        // Relax các cạnh
        for (auto& e : g[u]) {
            int v = e.first, w = e.second;
            if (dist[v] > dist[u] + w) {
                int old = dist[v];
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({ dist[v], v });

                cout << string(18, ' ')
                    << "→ Relax (" << (char)('A' + u) << " → " << (char)('A' + v)
                    << "): " << (old == INF ? "∞" : to_string(old))
                    << " → " << dist[v] << " (cập nhật)\n";
            }
        }
        cout << "\n";
    }

    // Kết quả cuối cùng
    cout << string(135, '=') << "\n";
    if (dist[goal] == INF) {
        cout << "KHÔNG TỒN TẠI ĐƯỜNG ĐI từ " << (char)('A' + start)
            << " đến " << (char)('A' + goal) << "\n\n";
    }
    else {
        vector<int> path;
        for (int v = goal; v != -1; v = prev[v]) path.push_back(v);
        reverse(path.begin(), path.end());

        cout << "ĐƯỜNG ĐI NGẮN NHẤT: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << (char)('A' + path[i]);
            if (i + 1 < path.size()) cout << " → ";
        }
        cout << " = " << dist[goal] << " đơn vị\n\n";
    }
    cout << string(135, '=') << "\n";
}

void run_demo1() {
    SetConsoleOutputCP(CP_UTF8);
    // Hoặc dùng: system("chcp 65001 >nul"); nếu thích

    system("cls");
    cout << "====================================================================\n";
    cout << " DEMO 1 - DIJKSTRA CHI TIẾT (BẢNG ĐẸP NHƯ SÁCH GIÁO KHOA VIỆT NAM)\n";
    cout << "====================================================================\n\n";

    int mode;
    cout << "Chọn chế độ:\n";
    cout << "1. Đồ thị cố định (6 đỉnh A → F - giống sách giáo khoa)\n";
    cout << "2. Đồ thị ngẫu nhiên (bạn nhập số đỉnh)\n";
    cout << "→ Nhập (1 hoặc 2): ";
    cin >> mode;

    vector<vector<pair<int, int>>> g;
    int n = 0, start = 0, goal = 0;

    if (mode == 1) {
        cout << "\n=== ĐỒ THỊ CỐ ĐỊNH (GIỐNG SÁCH GIÁO KHOA) ===\n";
        cout << "Các cạnh có hướng và trọng số:\n";
        cout << " A → B (5), A → D (9), A → E (2)\n";
        cout << " B → C (4)\n";
        cout << " C → F (2)\n";
        cout << " D → E (6)\n";
        cout << " E → B (1), E → C (7), E → F (3)\n\n";

        n = 6;
        g = {
            {{1,5},{3,9},{4,2}}, // A
            {{2,4}},             // B
            {{5,2}},             // C
            {{4,6}},             // D
            {{1,1},{2,7},{5,3}}, // E
            {}                   // F
        };
        start = 0; goal = 5;
    }
    else {
        cout << "\n→ Nhập số đỉnh (4 - 10): ";
        cin >> n;
        while (n < 4 || n > 10) {
            cout << "Chỉ nhập từ 4-10! Nhập lại: ";
            cin >> n;
        }
        g.assign(n, vector<pair<int, int>>());

        cout << "\n=== ĐỒ THỊ NGẪU NHIÊN ĐÃ SINH (" << n << " đỉnh) ===\n";
        cout << "Các cạnh (có hướng):\n";

        for (int u = 0; u < n; u++) {
            int deg = 2 + (rng() % 3);
            vector<int> used;
            for (int i = 0; i < deg; i++) {
                int v;
                do {
                    v = rng() % n;
                } while (v == u || find(used.begin(), used.end(), v) != used.end());
                used.push_back(v);
                int w = 1 + (rng() % 20);
                g[u].push_back({ v, w });
                cout << " " << (char)('A' + u) << " → " << (char)('A' + v) << " (" << w << ")\n";
            }
        }

        cout << "\n";
        char s, t;
        do {
            cout << "→ Đỉnh bắt đầu (A - " << (char)('A' + n - 1) << "): "; cin >> s;
            cout << "→ Đỉnh kết thúc (A - " << (char)('A' + n - 1) << "): "; cin >> t;
            s = toupper(s); t = toupper(t);
            start = s - 'A';
            goal = t - 'A';
        } while (start < 0 || start >= n || goal < 0 || goal >= n);
    }

    dijkstra_perfect_table(g, start, goal, n);

    cout << "\nNhấn Enter để quay lại menu chính...";
    cin.ignore();
    cin.get();
}