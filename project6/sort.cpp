#include "sort.h"

Sort::Sort() {}

void Sort::generateRandom(QSpinBox *SpinBox)
{
    int totalNum = SpinBox->value();
    vec.clear();
    vec.reserve(totalNum);
    for (int i = 0;i < totalNum;i++)
        vec.push_back(QRandomGenerator::global()->bounded(100000));
}

void Sort::BubbleSort()
{
    std::vector<int> Bubblevec = vec;
    int n = Bubblevec.size();
    for(int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for(int j = 0; j < n - 1 - i; j++)
        {
            if(Bubblevec[j] > Bubblevec[j + 1])
            {
                qSwap(Bubblevec[j], Bubblevec[j + 1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

int partition(std::vector<int> &a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(a[j] < pivot)
        {
            i++;
            qSwap(a[i], a[j]);
        }
    }
    qSwap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(std::vector<int> &a, int low, int high)
{
    if(low < high)
    {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void Sort::QuickSort()
{
    std::vector<int> Quickvec = vec;
    int length = Quickvec.size();
    quickSort(Quickvec, 0, length - 1);
}

void Sort::ShellSort()
{
    std::vector<int> Shellvec = vec;
    int n = Shellvec.size();
    for(int gap = n / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            int temp = Shellvec[i];
            int j = i;
            while(j >= gap && Shellvec[j - gap] > temp)
            {
                Shellvec[j] = Shellvec[j - gap];
                j -= gap;
            }
            Shellvec[j] = temp;
        }
    }
}

void heapify(std::vector<int> &a, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        qSwap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void Sort::HeapSort()
{
    std::vector<int> Heapvec = vec;
    int n = Heapvec.size();

    // build max heap
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(Heapvec, n, i);

    // extract elements
    for(int i = n - 1; i > 0; i--)
    {
        qSwap(Heapvec[0], Heapvec[i]);
        heapify(Heapvec, i, 0);
    }
}

int getMax(const std::vector<int> &a)
{
    int mx = a[0];
    for(int x : a)
        if(x > mx) mx = x;
    return mx;
}

void countingSortRadix(std::vector<int> &a, int exp)
{
    int n = a.size();
    QVector<int> output(n);
    int count[10] = {0};

    for(int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; i--)
    {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for(int i = 0; i < n; i++)
        a[i] = output[i];
}

void Sort::RadixSort()
{
    std::vector<int> Radixvec = vec;
    int m = getMax(Radixvec);

    for(int exp = 1; m / exp > 0; exp *= 10)
        countingSortRadix(Radixvec, exp);
}

void Sort::StartSort(QTextBrowser *TextBrowser, QSpinBox *SpinBox)
{
    generateRandom(SpinBox);
    qint64 ms[5];
    QElapsedTimer timer;
    timer.start();
    BubbleSort();
    ms[0] = timer.elapsed();

    timer.start();
    QuickSort();
    ms[1] = timer.elapsed();

    timer.start();
    ShellSort();
    ms[2] = timer.elapsed();

    timer.start();
    HeapSort();
    ms[3] = timer.elapsed();

    timer.start();
    RadixSort();
    ms[4] = timer.elapsed();

    TextBrowser->setHtml(QString("<p style = 'font-size:30px'>冒泡排序：%1 ms<br>"
                                 "快速排序：%2 ms<br>"
                                 "希尔排序：%3 ms<br>"
                                 "堆排序：%4 ms<br>"
                                 "基数排序：%5 ms</p>").arg(ms[0]).arg(ms[1]).arg(ms[2]).arg(ms[3]).arg(ms[4]));
}
