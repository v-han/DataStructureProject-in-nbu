#ifndef SORT_H
#define SORT_H

#include "qtextbrowser.h"
#include <QSpinBox>
#include <QTextBrowser>
#include <QElapsedTimer>
#include <QRandomGenerator>

#include <vector>

class Sort
{
private:
    std::vector<int> vec;

    void BubbleSort();
    void QuickSort();
    void ShellSort();
    void HeapSort();
    void RadixSort();
    void generateRandom(QSpinBox *SpinBox);

public:
    Sort();
    void StartSort(QTextBrowser *TextBrowser, QSpinBox *SpinBox);

};

#endif // SORT_H
