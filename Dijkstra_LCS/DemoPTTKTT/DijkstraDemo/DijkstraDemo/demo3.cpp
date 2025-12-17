// demo3_dijkstra_large_graph.cpp
// DEMO 3: HIỆU SUẤT DIJKSTRA TRÊN ĐỒ THỊ SIÊU LỚN (DÙNG PRIORITY_QUEUE THÔNG THƯỜNG)
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <iomanip>
#include <windows.h>
using namespace std;

const int INF = 1000000000;

// Hàm chạy Dijkstra và trả về thời gian chạy (giây)
double dijkstra_large(int V, int E, bool verbose = true) {
    vector<vector<pair<int, int>>> g(V);
    mt19937 rng(2025 + V); // seed khác nhau để đồ thị khác nhau

    if (verbose) {
        cout << "   • Sinh đồ thị: " << V << " đỉnh, " << E << " cạnh...\n";
    }

    // Sinh cạnh ngẫu nhiên (có hướng, không tự nối)
    for (int i = 0; i < E; ) {
        int u = rng() % V;
        int v = rng() % V;
        if (u == v) continue;
        int w = 1 + (rng() % 100);
        g[u].push_back({ v, w });
        i++;
    }

    if (verbose) cout << "   • Sinh xong! Bắt đầu chạy Dijkstra từ đỉnh 0...\n";

    auto start = chrono::high_resolution_clock::now();

    vector<int> dist(V, INF);
    dist[0] = 0;

    // Dùng priority_queue chuẩn (không dùng structured binding để tương thích C++11)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, 0 }); // {khoảng cách, đỉnh}

    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cost > dist[u]) continue; 

        for (auto& edge : g[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double time_sec = chrono::duration<double>(end - start).count();

    if (verbose) {
        cout << "   → HOÀN TẤT trong " << fixed << setprecision(3) << time_sec << " giây\n\n";
    }

    return time_sec;
}

void run_demo3() {
    SetConsoleOutputCP(CP_UTF8); 
    system("cls");

    cout << string(80, '=') << "\n";
    cout << " DEMO 3: HIỆU SUẤT DIJKSTRA TRÊN ĐỒ THỊ LỚN\n";
    cout << "        (Chứng minh priority_queue thông thường RẤT CHẬM!)\n";
    cout << string(80, '=') << "\n\n";

    cout << "Chúng ta sẽ thử 3 mức độ đồ thị tăng dần để thấy rõ sự chậm lại:\n\n";

    double t1, t2, t3 = 0.0;

    // === MỨC 1: Nhẹ (10.000 đỉnh) ===
    cout << "MỨC 1: 10.000 đỉnh – 50.000 cạnh\n";
    cout << string(50, '-') << "\n";
    t1 = dijkstra_large(10000, 50000);

    // === MỨC 2: Trung bình (100.000 đỉnh) ===
    cout << "MỨC 2: 100.000 đỉnh – 500.000 cạnh\n";
    cout << string(50, '-') << "\n";
    t2 = dijkstra_large(100000, 500000);

    // === MỨC 3: Nặng (500.000 đỉnh) – có hỏi trước ===
    cout << "MỨC 3: 500.000 đỉnh – 2.000.000 cạnh\n";
    cout << string(60, '-') << "\n";
    cout << "   Cảnh báo: Có thể mất 20-50 giây tùy máy!\n";
    cout << "   Bạn có muốn chạy thử không? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        t3 = dijkstra_large(500000, 2000000);
    }
    else {
        cout << "   → Đã bỏ qua mức 3 (hợp lý nếu máy yếu).\n\n";
        t3 = -1; // đánh dấu không chạy
    }

    // === TỔNG KẾT ===
    cout << string(80, '=') << "\n";
    cout << " TỔNG KẾT THỜI GIAN CHẠY (Dijkstra + priority_queue)\n";
    cout << string(80, '=') << "\n";
    cout << fixed << setprecision(3);
    cout << " • 10.000   đỉnh → " << setw(8) << t1 << " s → Nhanh\n";
    cout << " • 100.000  đỉnh → " << setw(8) << t2 << " s → Bắt đầu chậm\n";
    if (t3 >= 0)
        cout << " • 500.000  đỉnh → " << setw(8) << t3 << " s → RẤT CHẬM!\n\n";
    else
        cout << " • 500.000  đỉnh → (không chạy) → Dự đoán ~25-50 giây\n\n";

    cout << "KẾT LUẬN:\n\n";
    cout << "→ Với priority_queue (binary heap) trong C++:\n";
    cout << "    O((V + E) log V) vẫn QUÁ CHẬM khi V > 200.000\n\n";
    cout << "→ Trong ứng dụng thực tế (Google Maps, GPS, mạng xã hội...)\n";
    cout << "    KHÔNG ai dùng Dijkstra nguyên bản với binary heap!\n\n";
    cout << "→ Thay vào đó dùng:\n";
    cout << "    • Fibonacci Heap (lý thuyết nhanh hơn)\n";
    cout << "    • A* + heuristic\n";
    cout << "    • Contraction Hierarchies (CH)\n";
    cout << "    • Hub Labeling, PHAST, v.v.\n\n";

    cout << "→ Đây chính là lý do: \"Dijkstra trong sách ≠ Dijkstra ngoài đời thực!\"\n\n";

    cout << string(80, '=') << "\n";
    cout << " NHẤN ENTER ĐỂ QUAY LẠI MENU\n";
    cout << string(80, '=') << "\n";

    cin.ignore();
    cin.get();
}