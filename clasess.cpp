class ArrayGenerator {
    int N = 100000;
    vector<int> arr, sorted;

public:
    ArrayGenerator() {
        arr = vector<int>(N);
        for (int i = 0; i < N; i++)
            arr[i] = rnd() % 6001;
        sorted = arr;
        sort(sorted.begin(), sorted.end());
    }

    vector<int> get_arr(int n) {
        return {arr.begin(), arr.begin() + n};
    }

    vector<int> get_sort_rev(int n) {
        vector<int> res(sorted.begin(), sorted.begin() + n);
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> get_almost_sort(int n) {
        vector<int> res(sorted.begin(), sorted.begin() + n);
        for (int i = 0; i < 15; i++) {
            swap(res[rnd() % n], res[rnd() % n]);
        }
        return res;
    }
};

class SortTester {

    vector<vector<int>> test_merge_sort() {
        vector<vector<int>> res;

        for (int n = 500; n <= 100000; n += 100) {
            vector<int> phs;
            phs.emplace_back(n);

            // считаем для рандом массива
            vector<int> random = generator.get_arr(n);
            auto start = std::chrono::high_resolution_clock::now();
            merge_sort(random, 0, n);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            phs.emplace_back(msec);

            // считаем для почти отсортированного массива
            vector<int> almost_sorted = generator.get_almost_sort(n);
            start = std::chrono::high_resolution_clock::now();
            merge_sort(almost_sorted, 0, n);
            elapsed = std::chrono::high_resolution_clock::now() - start;
            msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            phs.emplace_back(msec);

            // считаем для отсортированного в обратном порядке массива
            vector<int> sorted_rev = generator.get_sort_rev(n);
            start = std::chrono::high_resolution_clock::now();
            merge_sort(sorted_rev, 0, n);
            elapsed = std::chrono::high_resolution_clock::now() - start;
            msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            phs.emplace_back(msec);

            res.emplace_back(phs);
        }

        return res;
    }

public:
    ArrayGenerator generator;

    SortTester() {
        generator = ArrayGenerator();
    }

    void test_standard() {
        isStandardMergesort = true;

        auto res = test_merge_sort();

        freopen("../data/standard_merge_sort.csv", "w", stdout);

        int i = 0;
        cout << "#\tn\trandom\talmost_sort\tsorted_rev\n";
        for (auto v : res) {
            for (auto e : v)
                cout << e << '\t';
            cout << '\n';
        }
    }

    void test_hybrid() {
        isStandardMergesort = false;

        auto res = test_merge_sort();

        freopen("../data/hybrid_merge_sort.csv", "w", stdout);

        int i = 0;
        cout << "#\tn\trandom\talmost_sort\tsorted_rev\t\n";
        for (auto v : res) {
            for (auto e : v)
                cout << e << '\t';
            cout << '\n';
        }
    }
};
