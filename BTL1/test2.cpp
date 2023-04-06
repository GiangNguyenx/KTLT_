#include <iostream>
using namespace std;
// Nhập danh sách liên kết đơn các số nguyên
//  thêm một node p vào sau node q

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
    if (p == NULL)
        return NULL;
    else
    {
        p->data = x;
        p->pNext = NULL;
    }
    return p;
}
void ThemVaoDau(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
        l.pHead = l.pTail = p;
    else
    {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

void ThemVaoCuoi(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
        l.pHead = l.pTail = p;
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Hàm thêm node p vào sau node q
void ThemNode_pVaoSauNode_q(LIST &l, NODE *p)
{
    int y;
    cout << "\nNhap gia tri node q: ";
    cin >> y;
    NODE *q = KhoiTaoNode(y);
    // Nếu dslk chỉ có 1 node q thì bài toán-> thêm vào cuối
    if (q->data == l.pHead->data && l.pHead->pNext == NULL)
    {
        ThemVaoCuoi(l, p);
    }
    // nếu q có tồn tại
    else
    { // đầu tiên - kiểm tra node q có tồn tại không
        for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        { // duyệt từ đầu đến cuối dslk

            if (q->data == k->data)
            {                                   // phải tạo mối liên kết từ node p đến node g kế node q trc rồi mới liên kết tiếp từ node q đến node p
                NODE *h = KhoiTaoNode(p->data); // khởi tạo node h mang data của node p để mỗi vòng lặp tạo mới 1 node mới-> giải quyết được
                NODE *g = k->pNext;             // cho node g trỏ vào node kế tiếp node q
                h->pNext = g;                   // tạo mối liên kết từ node p đến node g -> cũng là mối liên kết của node p đến node sau node q - node g
                k->pNext = h;                   // tạo mối liên kết từ node q đến node p -> cũng là mối liên kết của node p đến node k
                // khi chỉ có 1 node (2) như ds gồm các node 1 2 3 4 5 thì node thêm vào sau node 2 như bth: 1 2 69 3 4 5
                // khi có 2 node (2) trở lên thì từ các node (2) thứ 2 các node đều bị xóa cho đến node 2 cuối cùng trong dslk.
                // khắc phục?
                // vì node p ban đầu được khởi tạo ở 1 địa chỉ cố định, khi liên kết đến node g đầu tiên vẫn diễn ra thêm node 69 như bth
                // nhưng khi đến node q thứ 2 trong ds, node p ban đầu sẽ liên kết đến node g tiếp theo - sau node q thứ 2
                // vị trí của node p vẫn nằm vị trí phía sau node node q thứ nhất, dẫn đến việc các liên kết ở giữa node 1 đầu và node q kế bị mất đi
                // tương tự với các node q kế tiếp cứ lặp liên tục đến node q cuối -> xóa toàn bộ các node ở giữa 2 node này
                // vậy nên mỗi lần cho node p liên kết đến node g phải tạo 1 node p mới
            }
        }
    }
}

void XuatDS(LIST l)
{
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << k->data << " ";
    }
}

// hàm xử lí số lương và dữ liệu các node - nhập đến khi ấn 1 phím nào đó đẻ dừng
void Menu(LIST &l)
{

    int select;
    while (69)
    { // 69 tuong duong voi gia tri true, gia tri khac 0
        system("clear");
        cout << "\n\n\t\t=========== Menu ===========";
        cout << "\n\t1. Them node vao danh sach";
        cout << "\n\t2. Xuat danh sach lien ket";
        cout << "\n\t3. Them node p vao sau node q trong ds";
        cout << "\n\t0. Thoat";
        cout << "\n\n\t\t=========== End ===========";
        cout << "\nNhap lua chon: ";
        cin >> select;
        if (select < 0 || select > 3)
        {
            cout << "\nLua chon khong hop le. Xin kiem tra lai";
        }
        if (select == 1)
        {
            cout << "\nNhap gia tri so nguyen: ";
            int x;
            cin >> x;
            NODE *p = KhoiTaoNode(x);
            ThemVaoCuoi(l, p);
        }
        else if (select == 2)
        {
            cout << "\nDanh sach lien ket da nhap la: ";
            XuatDS(l);
        }
        else if (select == 3)
        {
            int x;
            cout << "\nNhap gia tri node p: ";
            cin >> x;
            NODE *p = KhoiTaoNode(x);
            ThemNode_pVaoSauNode_q(l, p);
        }
        else if (select == 0)
            break; // thoát khỏi vòng lăp hiện tại
    }
}

int main()
{
    LIST l;
    KhoiTaoDSLK(l); // luôn luôn phải goị hàm khởi tạo dslk đơn trc khi thao tác
    Menu(l);
    return 0;
}