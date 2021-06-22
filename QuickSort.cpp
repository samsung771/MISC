#include <iostream>
#include <vector>

void sorted(std::vector<int*>& a, int start, std::vector<int>& out)
{
    std::vector<int*> lhs;
    std::vector<int*> rhs;

    int pivot = *a[a.size() >> 1];

    a.erase(a.begin() + (a.size() >> 1));

    for (int i = 0; i < a.size(); i++)
    {
        if (*a[i] <= pivot)
        {
            lhs.push_back(a[i]);
        }
        else
        {
            rhs.push_back(a[i]);
        }
    }

    out[lhs.size() + start] = pivot;

    if (lhs.size() == 1)
    {
        out[start] = *lhs[0];
    }
    if (rhs.size() == 1)
    {
        out[start + lhs.size() + 1] = *rhs[0];
    }
    if (lhs.size() > 1)
    {
        sorted(lhs, start, out);
    }
    if (rhs.size() > 1)
    {
        sorted(rhs, start + lhs.size()+2, out);
    }
}

void quickSort(std::vector<int>& a)
{
    std::vector<int*> b;
    std::vector<int> out;
    for (int i = 0; i < a.size(); i++)
    {
        b.push_back(&a[i]);
        out.push_back(0);
    }  

    sorted(b, 0, out);

    a = out;
}

int main()
{
    std::vector<int> test = { 1,4,2,6,8,4,2,1,7,9,67,4,1,3,6,31,2 };
    std::vector<int> test2 = { 1,6,3,7,9,125,32,563,12,74,217,34,63,25,1,2,1256,732,64,21 };
    quickSort(test);
    quickSort(test2);

    for (int i : test)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";
    for (int i : test2)
    {
        std::cout << i << " ";
    }

    return 0;
}