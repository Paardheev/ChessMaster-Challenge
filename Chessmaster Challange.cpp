#include <vector>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Comparator class used for custom sorting order (ascending or descending)
class Comparator
{
public:
    Comparator()
    {
        n = 1; // Default to ascending
    }
    Comparator(long long order)
    {
        n = order;
    }

    // Overloaded operator() to perform comparison based on sort order
    bool operator()(long long q1, long long q2)
    {
        if (n == 1)
        { // ascending
            return q1 <= q2;
        }
        else
        { // descending
            return q1 > q2;
        }
    }

    long long n; // Sorting mode: 1 for ascending, 0 for descending
};

// Quantum Chess Board (QCB) class
class QCB
{
public:
    QCB()
    {
    }

    // Create board of given size and initialize values
    void createboard(long long size)
    {
        n = size;
        board.resize(n, std::vector<long long>(n));
        v.resize(1, std::vector<long long>(n * n));
        maxele.resize(n);
        max = 0;
        psm = 0;
        issorted = false;
        ncount = -1;
        acount = -1;
        dcount = -1;

        // Read board elements from input
        for (long long i = 0; i < n; i++)
            for (long long j = 0; j < n; j++)
                cin >> board[i][j];

        // Precompute max elements per row
        maxelefinder();
        return;
    }

    // Sort each row of the board using custom comparator
    void sortRows(Comparator &comparator)
    {
        c = comparator;
        for (long long i = 0; i < n; i++)
            mergeSort(board[i], 0, n - 1);
        return;
    }

    // Merge function used in merge sort with inversion count
    void merge(vector<long long> &arr, long long left, long long mid, long long right)
    {
        long long n1 = mid - left + 1;
        long long n2 = right - mid;

        // Temporary arrays
        vector<long long> L(n1), R(n2);
        for (long long i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (long long j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        long long i = 0, j = 0, k = left;

        // Merge while counting inversions
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
                count += (n1 - i); // Count inversions
            }
            k++;
        }

        // Copy remaining elements
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // Recursive merge sort with inversion counting
    void mergeSort(vector<long long> &arr, long long left, long long right)
    {
        if (left >= right)
            return;
        long long mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    // Finds the maximum element from each row
    void maxelefinder()
    {
        for (long long i = 0; i < n; i++)
        {
            long long maxi = 0;
            for (long long j = 0; j < n; j++)
                if (board[i][j] > maxi)
                    maxi = board[i][j];
            maxele[i] = maxi + 1;
            if (max < maxele[i])
                max = maxele[i];
        }
    }

    // Counts inversions based on current board and previous sort mode (psm)
    long long countinversions()
    {
        if (psm == 0 && ncount != -1)
            return ncount;
        else if (psm == 0)
        {
            // Flatten the board row-wise
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++)
                    v[0][(i * n) + j] = board[i][j];

            count = 0;
            mergeSort(v[0], 0, (n * n) - 1);
            ncount = count;
            return ncount;
        }
        else if (psm == -1 && dcount != -1)
            return dcount;
        else if (psm == -1)
        {
            // Flatten in row-wise reverse order
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++)
                    v[0][(i * n) + j] = board[i][n - 1 - j];

            count = 0;
            mergeSort(v[0], 0, (n * n) - 1);
            dcount = count;
            return dcount;
        }
        else if (psm == 1 && acount != -1)
            return acount;
        else if (psm == 1)
        {
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++)
                    v[0][(i * n) + j] = board[i][j];

            count = 0;
            mergeSort(v[0], 0, (n * n) - 1);
            acount = count;
            return acount;
        }
        return 0;
    }

    // Display the board depending on previous sort mode
    void display()
    {
        if (psm != -1)
        {
            for (long long i = 0; i < n; i++)
            {
                for (long long j = 0; j < n; j++)
                    cout << board[i][j] << " ";
                cout << endl;
            }
        }
        else
        {
            for (long long i = 0; i < n; i++)
            {
                for (long long j = n - 1; j >= 0; j--)
                    cout << board[i][j] << " ";
                cout << endl;
            }
        }
        return;
    }

    long long psm;    // previous sort mode: 0 = none, -1 = descending, 1 = ascending
    bool issorted;    // has board been sorted
    long long count;  // used during inversion counting

private:
    long long n; // board size
    std::vector<std::vector<long long>> board; // board matrix
    std::vector<std::vector<long long>> v;     // flattened board for inversion
    std::vector<long long> maxele;             // max element per row
    Comparator c;
    long long max;
    long long ncount, acount, dcount; // inversion counts for different modes
};

// Comparator for sorting pairs based on second value, then first
struct comp
{
    bool operator()(std::pair<long long, long long> &p1, std::pair<long long, long long> &p2)
    {
        if (p1.second != p2.second)
            return p1.second < p2.second;
        else
            return p1.first < p2.first;
    }
};

// SpaceStation class to find the closest pair of players
class spacestation
{
public:
    spacestation(std::vector<std::pair<long long, long long>> p)
    {
        size = p.size();
        players.resize(size, std::pair<long long, long long>({0, 0}));
        players = p;
    }

    // Recursively finds the closest pair in range
    std::pair<long long, long long> closestpair(long long low, long long high)
    {
        if (high - low == 1)
            return std::pair<long long, long long>{low, high};
        if (high - low == 2)
            return basecase(low, high);

        long long p1, p2;
        std::pair<long long, long long> ans;
        long long mid = (low + high) / 2;

        // Recursive calls
        std::pair<long long, long long> firsthalf = closestpair(low, mid);
        std::pair<long long, long long> secondhalf = closestpair(mid + 1, high);

        // Get minimum distance
        long long d = std::min(distance(firsthalf.first, firsthalf.second), distance(secondhalf.first, secondhalf.second));

        // Choose best among both halves
        if (d == distance(firsthalf) && d == distance(secondhalf))
            ans = minpair(firsthalf, secondhalf), p1 = ans.first, p2 = ans.second;
        else if (d == distance(firsthalf))
            p1 = firsthalf.first, p2 = firsthalf.second, ans = firsthalf;
        else
            p1 = secondhalf.first, p2 = secondhalf.second, ans = secondhalf;

        // Collect candidates near dividing line
        std::vector<std::pair<std::pair<long long, long long>, long long>> nearx;
        long long i = low;
        while (i <= mid)
        {
            if ((players[mid].first - players[i].first) * (players[mid].first - players[i].first) < d)
                nearx.push_back({players[i], i});
            i++;
        }
        while (i <= high)
        {
            if ((players[i].first - players[mid + 1].first) * (players[i].first - players[mid + 1].first) < d)
                nearx.push_back({players[i], i});
            else
                break;
            i++;
        }

        // Compare candidates pairwise
        long long nearxsize = nearx.size();
        for (i = 0; i < nearxsize; i++)
        {
            for (long long j = i + 1; j < nearxsize; j++)
            {
                if ((nearx[j].first.second - nearx[i].first.second) * (nearx[j].first.second - nearx[i].first.second) < d)
                {
                    if (distance(nearx[j].second, nearx[i].second) < d || (distance(nearx[j].second, nearx[i].second) == d && players[ans.first].first > nearx[i].first.first) || ((distance(nearx[j].second, nearx[i].second) == d && players[ans.second].first > nearx[j].first.first) || ((distance(nearx[j].second, nearx[i].second) == d && players[ans.first].second > nearx[i].first.second))))
                    {
                        d = distance(nearx[j].second, nearx[i].second);
                        ans = {nearx[i].second, nearx[j].second};
                    }
                }
            }
        }

        return ans;
    }

    // Handles base case of 2–3 players
    std::pair<long long, long long> basecase(long long low, long long high)
    {
        std::pair<long long, long long> p;
        if (distance(high, low) < distance(high, low + 1))
            p = {low, high};
        else if (distance(high, low) == distance(high, low + 1))
            p = minpair({high, low}, {high, low + 1});
        else
            p = {high, low + 1};

        if (distance(low + 1, low) < distance(p))
            p = {low + 1, low};
        else if (distance(low + 1, low) == distance(p))
            p = minpair({low + 1, low}, p);
        return p;
    }

    // Returns lexicographically smaller pair
    std::pair<long long, long long> minpair(std::pair<long long, long long> p1, std::pair<long long, long long> p2)
    {
        if (players[p1.first] < players[p2.first])
            return p1;
        else if (players[p1.first] == players[p2.first])
        {
            if (players[p1.second] < players[p2.second])
                return p1;
            else
                return p2;
        }
        else
            return p2;
    }

    // Euclidean distance squared between players i and j
    long long distance(long long i, long long j)
    {
        return (((players[i].first - players[j].first) * (players[i].first - players[j].first)) + ((players[i].second - players[j].second) * (players[i].second - players[j].second)));
    }

    // Overloaded distance for pair
    long long distance(std::pair<long long, long long> &p)
    {
        return distance(p.first, p.second);
    }

    // Get coordinates of player at index i
    std::pair<long long, long long> &getcoordinates(long long i)
    {
        return players[i];
    }

private:
    std::vector<std::pair<long long, long long>> players;
    long long size;
};

// Main program handling command-based simulation
int main()
{
    string s = "start";
    long long size;
    QCB matrix;

    while (s != "END")
    {
        cin >> s;

        // Create board
        if (s == "CREATE_2D")
        {
            cin >> size;
            matrix.createboard(size);
        }

        // Sort board rows
        else if (s == "SORT_2D")
        {
            string t;
            cin >> t;
            long long n;
            if (t == "ascending")
                n = 1, matrix.psm = 1;
            else
                n = 0, matrix.psm = -1;
            Comparator c(n);
            if (!matrix.issorted)
                matrix.sortRows(c), matrix.issorted = true;
        }

        // Inversion count
        else if (s == "INVERSION_2D")
        {
            cout << matrix.countinversions() << endl;
        }

        // Display board
        else if (s == "DISPLAY_2D")
        {
            matrix.display();
        }

        // Find closest pair
        else if (s == "CLOSEST_2D")
        {
            long long playersize;
            cin >> playersize;
            std::vector<std::pair<long long, long long>> players;
            long long first, second;
            for (long long i = 0; i < playersize; i++)
            {
                cin >> first >> second;
                std::pair<long long, long long> p({first, second});
                players.push_back(p);
            }

            std::vector<std::pair<long long, long long>> pass = players;
            std::sort(players.begin(), players.end());
            spacestation plane(players);
            std::pair<long long, long long> p = plane.closestpair(0, playersize - 1);

            // Identify original order
            long long f = -1;
            for (long long i = 0; i < playersize; i++)
            {
                if (pass[i] == players[p.first])
                {
                    f = 0;
                    break;
                }
                if (pass[i] == players[p.second])
                {
                    f = 1;
                    break;
                }
            }

            // Output coordinates in original input order
            if (f == 0)
                cout << plane.getcoordinates(p.first).first << " " << plane.getcoordinates(p.first).second << " " << plane.getcoordinates(p.second).first << " " << plane.getcoordinates(p.second).second << endl;
            else if (f == 1)
                cout << plane.getcoordinates(p.second).first << " " << plane.getcoordinates(p.second).second << " " << plane.getcoordinates(p.first).first << " " << plane.getcoordinates(p.first).second << endl;
        }
    }
}