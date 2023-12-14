int main() {
    int i    = 2;
    int loop = 0;
    int a[10][10];
    int x;
    while (loop == 0 && i <= 10) {
        int j = 1;
        while (loop == 0 && j < i)
            if (a[i][j] == x)
                loop = 1;
            else
                j = j + 1;
        if (loop == 0)
            i = i + 1;
    }
}