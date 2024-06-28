constexpr int N = 1e5 + 10;
namespace Link_Cut_Tree {
    #define fa(x) tr[x].fa
    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define notroot(x) lc(fa(x)) == x || rc(fa(x)) == x
    struct node { //splay����Ϣ
        int ch[2], fa, v, sum;
        int tag; //��ת�����
    }tr[N]; 

    void pushup(int x) { //�ϴ�
        tr[x].sum = tr[lc(x)].sum ^ tr[x].v ^ tr[rc(x)].sum;
    }
    void pushdown(int x) { //�´�
        if (tr[x].tag) {
            swap(lc(x), rc(x));
            tr[lc(x)].tag ^= 1;
            tr[rc(x)].tag ^= 1;
            tr[x].tag = 0;
        }
    }
    void pushall(int x) { //�ݹ��´�
        if (notroot(x)) pushall(fa(x));
        pushdown(x);
    }
    void rotate(int x) { //��תx
        int y = fa(x), z = fa(y), k = rc(y) == x; //y���Ҷ���x
        if (notroot(y)) tr[z].ch[rc(z) == y] = x; fa(x) = z; //z�Ķ���x,x�ĸ���z
        tr[y].ch[k] = tr[x].ch[k ^ 1]; fa(tr[x].ch[k ^ 1]) = y; //y�Ķ���x�����,x������ĸ���y
        tr[x].ch[k ^ 1] = y; fa(y) = x; //x�������y,y�ĸ���x
        pushup(y); pushup(x); //�Ե�����pushup
    }
    void splay(int x) { //x��չ����
        pushall(x); //�ݹ��´�
        while (notroot(x)) { //����תxx,ֱ��תyx
            int y = fa(x), z = fa(y);
            if (notroot(y)) (rc(y) == x) ^ (rc(z) == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }
    void access(int x) { //��ͨx��������·
        for (int y = 0; x;){
            splay(x); //xת����ǰsplay�ĸ�
            rc(x) = y;  //x���Ҷ�ָ������splay�ĸ�
            pushup(x); //����x��sum
            y = x, x = fa(x); //��x,x���������splay
        }
    }
    void makeroot(int x) { //����
        access(x); //ͨ·
        splay(x);  //��չ
        tr[x].tag ^= 1; //��ת�����
    }
    void split(int x, int y) { //����x��y��·��
        makeroot(x); //x����
        access(y); //yͨ·
        splay(y);  //y��չ
    }
    int query(int x, int y) { //���
        split(x, y); //����
        return tr[y].sum;
    }
    int findroot(int x) { //�Ҹ�
        access(x);
        splay(x);
        while (lc(x)) pushdown(x), x = lc(x);
        splay(x); //��ֹ����
        return x;
    }
    void link(int x, int y) { //����
        makeroot(x);
        if (findroot(y) != x) fa(x) = y;
    }
    void cut(int x, int y) { //�ϱ�
        makeroot(x);
        if (findroot(y) == x && fa(y) == x && !lc(y))
            fa(y) = 0, pushup(x);
    }
    void change(int x, int y) { //�޸�
        splay(x);
        tr[x].v = y;
        pushup(x);
    }
}
using namespace Link_Cut_Tree;
