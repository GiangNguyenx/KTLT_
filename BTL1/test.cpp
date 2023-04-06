#include <iostream>
using namespace std;
// Khởi tạo dslk các số nguyên
// Thêm node p vào trước node q

struct node
{
    int data;
    node *pNext;
};
typedef struct node NODE;

struct list
{
    node *pHead;
    node *pTail;
};
typedef struct list LIST;

void KhoiTaoDSLK(LIST &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

NODE *KhoiTaoNode(int x)
{
    NODE *p = new NODE;
    p->data = x; 
    p->pNext = NULL;
    // if (p == NULL)
    //     return NULL;
    // else
    // {
    // }
    return p;
}
void ThemVaoDauDSLK(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
        l.pHead = l.pTail = p;
    else
    {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

void ThemVaoCuoiDSLK(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
        l.pHead = l.pTail = p;
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void ThemNode_pVaoSauNode_q(LIST &l, NODE *p)
{
    int y;
    cout << "\nNhap gia tri node q:";
    cin >> y;
    NODE *q = KhoiTaoNode(y);
    if (q->data == l.pHead->data && l.pHead->pNext == NULL)
    {
        ThemVaoCuoiDSLK(l, p);
    }
    else
    {
        for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        {
            if (q->data == k->data)
            {
                NODE *g = k->pNext;
                NODE *h = KhoiTaoNode(p->data);
                h->pNext = g;
                k->pNext = h;
            }
        }
    }
}

void ThemNode_qVaoTruocNode_q(LIST &l, NODE *p)
{
    int y;
    cout << "\nNhap gia tri node q:";
    cin >> y;
    NODE *q = KhoiTaoNode(y);
    if (q->data == l.pHead->data && l.pHead->pNext == NULL)
    {
        ThemVaoDauDSLK(l, p);
    }
    else
    {
        NODE *g;
        g->pNext = q;
        NODE *h = KhoiTaoNode(p->data);
        h->pNext = q;
        g->pNext = h;
    }
}

void XuatDSLK(LIST l)
{
    
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << k->data << " ";
    }
}
// cop thu sang cho nam chay dc k
// cùng trình dịch thì cũng thế thôi
void Menu(LIST &l)
{
    int select;
    while (69)
    {
        system("clear");
        cout << "\n\n\t\t=============MENU==============";
        cout << "\n1. Them node vao danh sach lien ket.";
        cout << "\n2. Them node p vao truoc node q trong danh sach lien ket.";
        cout << "\n3. Them node p vao sau node q trong danh sach lien ket.";
        cout << "\n4. Xuat danh sach lien ket.";
        cout << "\n0. Thoat chuong trinh.";
        cout << "\n\n\t\t=============END==============";
        cout << "\nNhap lua chon : ";
        cin >> select;
        if (select < 0 || select > 4)
            cout << "\nGia tri lua chon nhap vao khong hop le. Vui long nhap lai!";
        else if (select == 1)
        {
            int x;
            cout << "\nNhap gia tri cua node p: ";
            cin >> x;
            NODE *p = KhoiTaoNode(x);
            ThemVaoCuoiDSLK(l, p);
        }
        else if (select == 2)
        {
            int x;
            cout << "\nNhap gia tri cua node p duoc them vao: ";
            cin >> x;
            NODE *p = KhoiTaoNode(x);
            ThemNode_qVaoTruocNode_q(l, p);
        }
        else if (select == 3)
        {
            int x;
            cout << "\nNhap gia tri cua node p duoc them vao: ";
            cin >> x;
            NODE *p = KhoiTaoNode(x);
            ThemNode_pVaoSauNode_q(l, p);
        }
        else if (select == 4)
        {
            cout << "\nDanh sach lien ket da nhap la: ";
            XuatDSLK(l);
        }
        else if (select == 0)
            break;
    }
}
int main()
{
    LIST l;
    KhoiTaoDSLK(l);
    Menu(l);
    return 0;
}
// biet bij sao roi. tat ca tai cho nam