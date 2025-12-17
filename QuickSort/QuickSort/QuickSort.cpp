#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int partition(float arr[], int low, int high, int pivotIndex) {
    swap(&arr[pivotIndex], &arr[high]);

    float pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(float arr[], int low, int high, int pivotChoice) {
    if (low < high) {
        int pivotIndex;

        switch (pivotChoice) {
        case 1: 
            pivotIndex = low;
            break;
        case 2: 
            pivotIndex = high;
            break;
        case 3: 
            pivotIndex = low + (high - low) / 2;
            break;
        case 4: 
            pivotIndex = low + rand() % (high - low + 1);
            break;
        default:
            pivotIndex = low + (high - low) / 2;
        }

        int pi = partition(arr, low, high, pivotIndex);

        quickSort(arr, low, pi - 1, pivotChoice);
        quickSort(arr, pi + 1, high, pivotChoice);
    }
}

void generateLargeDataset(float arr[], int n) {
    printf("Dang tao du lieu lon de do hieu năng...\n");
    for (int i = 0; i < n; i++) {
        arr[i] = (rand() % 10000) / 100.0f; 
    }
}

void printSamples(float arr[], int n, int sampleSize) {
    printf("\nMau du lieu (in %d phan tu dau va cuoi):\n", sampleSize);

    printf("Dau mang: ");
    for (int i = 0; i < sampleSize && i < n; i++) {
        printf("%.2f ", arr[i]);
    }

    printf("\nCuoi mang: ");
    for (int i = n - sampleSize; i < n && i >= 0; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int pivotMenu() {
    int choice;

    printf("\n====================================================\n");
    printf("CHON PHUONG THUC CHON PIVOT\n");
    printf("======================================================\n");
    printf("1. Phan tu dau tien\n");
    printf("2. Phan tu cuoi cung\n");
    printf("3. Phan tu o giua\n");
    printf("4. Phan tu ngau nhien\n");
    printf("======================================================\n");
    printf("Lua chon cua ban (1-4): ");
    scanf_s("%d", &choice);

    while (choice < 1 || choice > 4) {
        printf("Lua chon khong hop le. Chon lai (1-4): ");
        scanf_s("%d", &choice);
    }

    return choice;
}

int isSorted(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0; 
        }
    }
    return 1; 
}
int main() {

    float predefinedScores[] = {
        8.5, 7.2, 9.0, 6.8, 8.9, 7.5, 5.5, 6.2, 9.5, 8.1,
        4.5, 7.8, 6.5, 8.3, 7.0, 9.2, 5.8, 6.9, 8.7, 7.3,
        6.0, 8.0, 5.2, 9.8, 7.9, 6.7, 8.4, 5.9, 7.1, 6.3,
        8.6, 7.4, 6.1, 9.1, 5.7, 8.2, 6.4, 7.6, 9.3, 5.6,
        8.8, 6.6, 7.7, 9.4, 5.4, 6.8, 8.5, 7.8, 9.7, 5.3
    };

    int small_n = sizeof(predefinedScores) / sizeof(predefinedScores[0]);
    int large_n = 10000; 
    int pivotChoice;
    float* scores_small;
    float* scores_large;
    LARGE_INTEGER frequency, start, end;
    double time_taken_ms, time_taken_ns;
    srand((unsigned int)time(NULL));

    printf("|===================================================|\n");
    printf("|     CHUONG TRINH SAP XEP DIEM TRUNG BINH          |\n");
    printf("|      (Do thoi gian thuc hien chinh xac)           |\n");
    printf("|===================================================|\n");

    printf("\n====================================================\n");
    printf("PHAN 1: DU LIEU NHO (%d phan tu)\n", small_n);
    printf("======================================================\n");

    scores_small = (float*)malloc(small_n * sizeof(float));
    if (scores_small == NULL) {
        printf("Khong the cap phat bo nho!\n");
        return 1;
    }


    for (int i = 0; i < small_n; i++) {
        scores_small[i] = predefinedScores[i];
    }

    printSamples(scores_small, small_n, 5);

    pivotChoice = pivotMenu();

    printf("\n--- Do thoi gian voi ham clock() ---\n");
    clock_t start_clock = clock();

    quickSort(scores_small, 0, small_n - 1, pivotChoice);

    clock_t end_clock = clock();
    double time_clock = ((double)(end_clock - start_clock)) / CLOCKS_PER_SEC * 1000.0;
    printf("Thoi gian (clock): %.6f ms\n", time_clock);
    printf("Thoi gian (clock): %.3f micro giay\n", time_clock * 1000.0);

    printf("Kiem tra sap xep: %s\n", isSorted(scores_small, small_n) ? "THANH CONG" : "THAT BAI");

    printf("\n=====================================================\n");
    printf("PHAN 2: DU LIEU LON (%d phan tu) - Do chinh xac hon\n", large_n);
    printf("=======================================================\n");

    scores_large = (float*)malloc(large_n * sizeof(float));
    if (scores_large == NULL) {
        printf("Khong the cap phat bo nho!\n");
        free(scores_small);
        return 1;
    }

    generateLargeDataset(scores_large, large_n);
    printSamples(scores_large, large_n, 3);


    float* scores_copy = (float*)malloc(large_n * sizeof(float));

    printf("\n=====================================================\n");
    printf("SO SANH THOI GIAN CAC PHUONG PHAP CHON PIVOT\n");
    printf("=======================================================\n");

    const char* method_names[] = { "Dau tien", "Cuoi cung", "Giua", "Ngau nhien" };

    QueryPerformanceFrequency(&frequency);

    for (int method = 1; method <= 4; method++) {
        for (int i = 0; i < large_n; i++) {
            scores_copy[i] = scores_large[i];
        }

        QueryPerformanceCounter(&start);

        // Sắp xếp
        quickSort(scores_copy, 0, large_n - 1, method);

        QueryPerformanceCounter(&end);

        // Tính thời gian
        time_taken_ms = ((double)(end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
        time_taken_ns = time_taken_ms * 1000000.0; // Chuyển sang nanosecond

        printf("Phuong phap %d (%s):\n", method, method_names[method - 1]);
        printf("  - Thoi gian: %12.6f ms\n", time_taken_ms);
        printf("  - Thoi gian: %12.3f micro giay\n", time_taken_ms * 1000.0);
        printf("  - Thoi gian: %12.0f nanosecond\n", time_taken_ns);
        printf("  - Ket qua: %s\n\n", isSorted(scores_copy, large_n) ? "Dung" : "Sai");
    }

    // ===== PHẦN 3: Lặp lại nhiều lần để đo chính xác hơn =====
    printf("\n=====================================================\n");
    printf("PHAN 3: DO THOI GIAN LAP LAI 1000 LAN (DU LIEU NHO)\n");
    printf("=======================================================\n");

    int repetitions = 1000;
    double total_time = 0;
    float* temp_scores = (float*)malloc(small_n * sizeof(float));

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int rep = 0; rep < repetitions; rep++) {
        // Sao chép dữ liệu gốc
        for (int i = 0; i < small_n; i++) {
            temp_scores[i] = predefinedScores[i];
        }

        // Sắp xếp
        quickSort(temp_scores, 0, small_n - 1, pivotChoice);
    }

    QueryPerformanceCounter(&end);

    // Tính thời gian trung bình
    total_time = ((double)(end.QuadPart - start.QuadPart) * 1000000.0) / frequency.QuadPart; // micro giây
    double avg_time = total_time / repetitions;

    printf("Da sap xep %d lan voi %d phan tu\n", repetitions, small_n);
    printf("Tong thoi gian: %.3f micro giay\n", total_time);
    printf("Thoi gian trung binh moi lan: %.3f micro giay\n", avg_time);
    printf("Thoi gian trung binh: %.3f nanosecond\n", avg_time * 1000.0);

    // Giải phóng bộ nhớ
    free(scores_small);
    free(scores_large);
    free(scores_copy);
    free(temp_scores);

    // Hiển thị thông tin về độ chính xác
    printf("\n=================================================\n");
    printf("THONG TIN DO CHINH XAC THOI GIAN:\n");
    printf("===================================================\n");
    printf("1. Ham clock(): do chinh xac ~ 1 ms\n");
    printf("2. QueryPerformanceCounter: do chinh xac ~ 100 ns\n");
    printf("3. Voi du lieu nho (<100), can lap lai nhieu lan\n");
    printf("4. Ket qua co the khac nhau giua cac lan chay\n");

    // Dừng chương trình để xem kết quả
    printf("\n=================================================\n");
    printf("Nhan phim bat ky de thoat...");
    getchar(); // Đọc ký tự newline còn lại
    getchar(); // Chờ nhấn phím

    return 0;
}