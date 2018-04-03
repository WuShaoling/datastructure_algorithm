#include<iostream>
#include<time.h>
using namespace std;

#define MAX_KEY 5	//B+���Ľ�,����Ϊ����3����

//B+���ڵ�����ݽṹ
typedef struct {
    int	key[MAX_KEY] ;		//�ؼ�����
    long	Pointer[MAX_KEY+1] ;	//ָ����
    int		nkey ;				//�ؼ�����
    bool	isleaf ;				//�Ƿ�ΪҶ�ڵ� Ҷ�ڵ�:true ����Ϊfalse

} BPlusNode;


//����ؼ��ֵ����ݽṹ
typedef struct {
    int	key;			  //�ü�¼�Ĺؼ���
    long	Raddress;		  //�ùؼ��ֶ�Ӧ��¼�ĵ�ַ
} TRecord;


//�����ѯ��������ݽṹ
typedef struct {
    bool	exist;
    long	Baddress;	//��������ü�¼��B+���ڵ��ַ
    long	Raddress;	//�ùؼ��ֵ���ָ��ļ�¼��ַ
} SearchResult;

class BPlusTree {
    long ROOT;		//�������ļ��ڵ�ƫ�Ƶ�ַ
    FILE	*Bfile;		//B+���ļ���ָ��
    FILE	*Rfile;		//��¼�ļ���ָ��
public:
    long	GetBPlusNode() const;
    void	ReadBPlusNode(const long ,BPlusNode& ) const;
    void	WriteBPlusNode(const long ,const BPlusNode& );
    void	Build_BPlus_Tree();
    void	Insert_BPlus_Tree(TRecord& );
    void	insert_bplus_tree(long ,TRecord& );
    void	Split_BPlus_Node(BPlusNode& ,BPlusNode& ,const int );
    void	Search_BPlus_Tree(TRecord& ,SearchResult& ) const;
    void	Delete_BPlus_Tree(TRecord& );
    void	delete_BPlus_tree(long ,TRecord& );
    void  EnumLeafKey();
    BPlusTree();
    ~BPlusTree();
};

BPlusTree :: BPlusTree() {
    Bfile = fopen("Bfile" ,"rb+" );	  //��B+���ļ�

}

BPlusTree :: ~BPlusTree() {
    fclose(Bfile );
}



void	BPlusTree :: Build_BPlus_Tree() {  //����һ�ÿ�B+��
    ROOT = GetBPlusNode();
    BPlusNode r;
    r.Pointer[MAX_KEY] = 0 ;
    r.nkey = 0;
    r.isleaf = true ;
    WriteBPlusNode(ROOT ,r );
}



void	BPlusTree :: Insert_BPlus_Tree(TRecord &record ) {	//��B+������ؼ���
    BPlusNode r;
    ReadBPlusNode(ROOT ,r );

    if( r.nkey == MAX_KEY ) {
        BPlusNode newroot ;
        newroot.nkey = 0;
        newroot.isleaf = false;
        newroot.Pointer[0] = ROOT ;

        Split_BPlus_Node(newroot ,r ,0 );
        WriteBPlusNode(ROOT ,r );

        ROOT = GetBPlusNode();

        WriteBPlusNode(ROOT ,newroot );

        //���Ѹ��ڵ�
    }
    insert_bplus_tree(ROOT ,record );
}



void	BPlusTree :: insert_bplus_tree(long current ,TRecord &record ) {
    BPlusNode x ;
    ReadBPlusNode(current ,x );

    int	i;
    for(i = 0 ; i < x.nkey && x.key[i] < record.key ; i ++);

    if(i < x.nkey && x.isleaf && x.key[i] == record.key ) {	//��B+��Ҷ�ڵ��ҵ�����ͬ�ؼ���
        //�ؼ��ֲ����ظ�
        return ;
    }

    if(!x.isleaf ) {	//�������Ҷ�ڵ�
        BPlusNode y;
        ReadBPlusNode(x.Pointer[i] ,y );

        if( y.nkey == MAX_KEY ) {	//���x���ӽڵ�������������ӽڵ����
            Split_BPlus_Node(x ,y ,i );
            WriteBPlusNode(current ,x );
            WriteBPlusNode(x.Pointer[i] ,y );
        }
        if( record.key <= x.key[i] || i == x.nkey ) {
            insert_bplus_tree(x.Pointer[i] ,record );
        } else {
            insert_bplus_tree(x.Pointer[i+1] ,record );
        }

    } else {		//�����Ҷ�ڵ�,��ֱ�ӽ��ؼ��ֲ���key������

        for(int j = x.nkey ; j > i ; j--) {
            x.key[j] = x.key[j-1] ;
            x.Pointer[j] = x.Pointer[j-1] ;
        }
        x.key[i] = record.key ;
        x.nkey ++;

        //����¼�ĵ�ַ����x.Pointer[i]

        x.Pointer[i] = record.Raddress;

        WriteBPlusNode(current ,x);

    }

}



void	BPlusTree :: Split_BPlus_Node(BPlusNode &father ,BPlusNode &current ,const int childnum) {		//��������B+���ڵ�
    int half = MAX_KEY/2 ;

    int i ;

    for(i = father.nkey ; i > childnum ; i -- ) {
        father.key[i] = father.key[i-1] ;
        father.Pointer[i+1] = father.Pointer[i];
    }
    father.nkey ++;

    BPlusNode t;

    long address = GetBPlusNode();

    father.key[childnum] = current.key[half] ;
    father.Pointer[childnum + 1] = address;

    for( i = half + 1 ; i < MAX_KEY ; i ++ ) {
        t.key[i-half-1] = current.key[i] ;
        t.Pointer[i-half-1] = current.Pointer[i];
    }

    t.nkey = MAX_KEY - half - 1;
    t.Pointer[t.nkey] = current.Pointer[MAX_KEY];

    t.isleaf = current.isleaf ;

    current.nkey = half ;

    if(current.isleaf ) {	//�����ǰ�����ѽڵ���Ҷ��
        current.nkey ++;
        t.Pointer[MAX_KEY] = current.Pointer[MAX_KEY];
        current.Pointer[MAX_KEY] = address ;
    }

    WriteBPlusNode(address ,t );

}



void	BPlusTree :: Search_BPlus_Tree(TRecord &record ,SearchResult &result ) const {	//��B+����ѯһ���ؼ���
    int i;

    BPlusNode a;
    long current = ROOT;

    do {
        ReadBPlusNode(current ,a );

        for(i = 0 ; i < a.nkey && record.key > a.key[i] ; i ++ );

        if( i < a.nkey && a.isleaf && record.key == a.key[i] ) {	//��B+��Ҷ�ڵ��ҵ��˵�ֵ�Ĺؼ���
            result.Baddress = current;
            result.Raddress = a.Pointer[i];						//���ظùؼ�������Ӧ�ļ�¼�ĵ�ַ
            result.exist = true;

            return ;
        }
        current = a.Pointer[i] ;

    } while(!a.isleaf);

    result.exist = false;
}




void	BPlusTree :: delete_BPlus_tree(long current ,TRecord &record ) {
    int i , j;

    BPlusNode x;
    ReadBPlusNode(current ,x );


    for(i = 0 ; i < x.nkey && record.key > x.key[i] ; i++ );

    if(i < x.nkey && x.key[i] == record.key ) {	//�ڵ�ǰ�ڵ��ҵ��ؼ���

        if(!x.isleaf) {  //���ڽڵ��ҵ��ؼ���
            BPlusNode child;
            ReadBPlusNode(x.Pointer[i] ,child );

            if( child.isleaf ) { //���������Ҷ�ڵ�
                if(child.nkey > MAX_KEY/2 ) {	//���A
                    x.key[i] = child.key[child.nkey - 2];
                    child.nkey --;

                    WriteBPlusNode(current ,x );
                    WriteBPlusNode(x.Pointer[i] ,child );

                    return ;
                } else {	//�����ӽڵ�Ĺؼ�������������
                    if(i > 0) {	//�����ֵܽڵ�
                        BPlusNode lbchild;
                        ReadBPlusNode(x.Pointer[i-1] ,lbchild );

                        if(lbchild.nkey > MAX_KEY/2 ) {	//���B
                            for( j = child.nkey ; j > 0 ; j -- ) {
                                child.key[j] = child.key[j-1];
                                child.Pointer[j] = child.Pointer[j-1];
                            }

                            child.key[0] = x.key[i-1];
                            child.Pointer[0] = lbchild.Pointer[lbchild.nkey-1];

                            child.nkey ++;

                            lbchild.nkey --;

                            x.key[i-1] = lbchild.key[lbchild.nkey-1];
                            x.key[i] = child.key[child.nkey-2];

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );
                            WriteBPlusNode(x.Pointer[i] ,child );

                        } else {	//���C
                            for( j = 0 ; j < child.nkey ; j++ ) {
                                lbchild.key[lbchild.nkey + j ] = child.key[j];
                                lbchild.Pointer[lbchild.nkey + j ] = child.Pointer[j];
                            }
                            lbchild.nkey += child.nkey;

                            lbchild.Pointer[MAX_KEY ] = child.Pointer[MAX_KEY];

                            //�ͷ�child�ڵ�ռ�õĿռ�x.Pointer[i]

                            for( j = i - 1 ; j < x.nkey - 1; j ++) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            x.key[i-1] = lbchild.key[lbchild.nkey-2];

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );

                            i --;

                        }


                    } else {	//ֻ�����ֵܽڵ�
                        BPlusNode rbchild;
                        ReadBPlusNode(x.Pointer[i+1] ,rbchild );

                        if(rbchild.nkey > MAX_KEY/2 ) {	//���D
                            x.key[i] = rbchild.key[0];
                            child.key[child.nkey] = rbchild.key[0];
                            child.Pointer[child.nkey] = rbchild.Pointer[0];
                            child.nkey ++;

                            for( j = 0 ; j < rbchild.nkey - 1 ; j ++) {
                                rbchild.key[j] = rbchild.key[j+1];
                                rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            }

                            rbchild.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );
                            WriteBPlusNode(x.Pointer[i+1] ,rbchild );

                        } else {	//���E
                            for( j = 0 ; j < rbchild.nkey ; j ++) {
                                child.key[child.nkey + j] = rbchild.key[j];
                                child.Pointer[child.nkey +j] = rbchild.Pointer[j];
                            }
                            child.nkey += rbchild.nkey ;

                            child.Pointer[MAX_KEY] = rbchild.Pointer[MAX_KEY];

                            //�ͷ�rbchildռ�õĿռ�x.Pointer[i+1]

                            for( j = i  ; j < x.nkey - 1; j ++) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );

                        }

                    }

                }

            } else {	//���F

                //�ҵ�key��B+��Ҷ�ڵ�����ֵܹؼ���,������ؼ���ȡ��key��λ��

                TRecord trecord;
                trecord.key = record.key;
                SearchResult result;
                Search_BPlus_Tree(trecord ,result );

                BPlusNode last;

                ReadBPlusNode(result.Baddress ,last );

                x.key[i] = last.key[last.nkey - 2 ];

                WriteBPlusNode(current ,x);


                if(child.nkey > MAX_KEY/2 ) {	  //���H

                } else {	 //�����ӽڵ�Ĺؼ�������������,���ֵܽڵ��ĳһ���ؼ�����������
                    if(i > 0 ) { //x.key[i]�����ֵ�
                        BPlusNode lbchild;
                        ReadBPlusNode(x.Pointer[i-1] ,lbchild );

                        if( lbchild.nkey > MAX_KEY/2 ) {	//���I
                            for( j = child.nkey ; j > 0 ; j -- ) {
                                child.key[j] = child.key[j-1];
                                child.Pointer[j+1] = child.Pointer[j];
                            }
                            child.Pointer[1] = child.Pointer[0];
                            child.key[0] = x.key[i-1] ;
                            child.Pointer[0] = lbchild.Pointer[lbchild.nkey];

                            child.nkey ++;

                            x.key[i-1] = lbchild.key[lbchild.nkey-1] ;
                            lbchild.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );
                            WriteBPlusNode(x.Pointer[i] ,child );
                        } else {	//���J
                            lbchild.key[lbchild.nkey] = x.key[i-1];	//�����ӽڵ㸴�Ƶ������ֵܵ�ĩβ
                            lbchild.nkey ++;

                            for(j = 0 ; j < child.nkey ; j++) {	//��child�ڵ㿽����lbchild�ڵ��ĩβ,
                                lbchild.key[lbchild.nkey + j] = child.key[j] ;
                                lbchild.Pointer[lbchild.nkey + j] = child.Pointer[j];
                            }
                            lbchild.Pointer[lbchild.nkey + j] = child.Pointer[j];
                            lbchild.nkey += child.nkey ;		  //�Ѿ���child������lbchild�ڵ�


                            //�ͷ�child�ڵ�Ĵ洢�ռ�,x.Pointer[i]


                            //���ҵ��ؼ��ֵĺ���child��ؼ������ֵܵĺ���lbchild�ϲ���,���ùؼ���ǰ��,ʹ��ǰ�ڵ�Ĺؼ��ּ���һ��
                            for(j = i - 1  ; j < x.nkey - 1 ; j++) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );

                            i --;

                        }

                    } else {	 //����x.key[i]ֻ�����ֵ�
                        BPlusNode rbchild;
                        ReadBPlusNode(x.Pointer[i+1] ,rbchild );

                        if( rbchild.nkey > MAX_KEY/2 ) {  //���K

                            child.key[child.nkey] = x.key[i];
                            child.nkey ++;

                            child.Pointer[child.nkey] = rbchild.Pointer[0];
                            x.key[i] = rbchild.key[0];

                            for( j = 0 ; j < rbchild.nkey -1 ; j++) {
                                rbchild.key[j] = rbchild.key[j+1];
                                rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            }
                            rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            rbchild.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );
                            WriteBPlusNode(x.Pointer[i+1] ,rbchild );

                        } else {	//���L
                            child.key[child.nkey] = x.key[i];
                            child.nkey ++;

                            for(j = 0; j < rbchild.nkey ; j++) {	//��rbchild�ڵ�ϲ���child�ڵ��
                                child.key[child.nkey + j] = rbchild.key[j];
                                child.Pointer[child.nkey +j] = rbchild.Pointer[j];
                            }
                            child.Pointer[child.nkey +j] = rbchild.Pointer[j];

                            child.nkey += rbchild.nkey;

                            //�ͷ�rbchild�ڵ���ռ�õĿռ�,x,Pointer[i+1]

                            for(j = i ; j < x.nkey - 1 ; j++ ) { //��ǰ���ؼ���֮��Ĺؼ�������һλ,ʹ�ýڵ�Ĺؼ���������һ
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );

                        }

                    }
                }

            }

            delete_BPlus_tree(x.Pointer[i] ,record );

        } else { //���G
            for( j = i ; j < x.nkey - 1 ; j ++ ) {
                x.key[j] = x.key[j+1];
                x.Pointer[j] = x.Pointer[j+1];
            }
            x.nkey-- ;

            WriteBPlusNode(current ,x);

            return ;
        }

    } else {	 //�ڵ�ǰ�ڵ�û�ҵ��ؼ���
        if(!x.isleaf ) {  //û�ҵ��ؼ���,��ؼ��ֱ�Ȼ��������Pointer[i]Ϊ����������
            BPlusNode child;
            ReadBPlusNode(x.Pointer[i] ,child );

            if(!child.isleaf ) {  //����亢�ӽڵ����ڽڵ�
                if(child.nkey > MAX_KEY/2 ) {	  //���H

                } else {	 //�����ӽڵ�Ĺؼ�������������,���ֵܽڵ��ĳһ���ؼ�����������
                    if(i > 0 ) { //x.key[i]�����ֵ�
                        BPlusNode lbchild;
                        ReadBPlusNode(x.Pointer[i-1] ,lbchild );

                        if( lbchild.nkey > MAX_KEY/2 ) {	//���I
                            for( j = child.nkey ; j > 0 ; j -- ) {
                                child.key[j] = child.key[j-1];
                                child.Pointer[j+1] = child.Pointer[j];
                            }
                            child.Pointer[1] = child.Pointer[0];
                            child.key[0] = x.key[i-1] ;
                            child.Pointer[0] = lbchild.Pointer[lbchild.nkey];

                            child.nkey ++;

                            x.key[i-1] = lbchild.key[lbchild.nkey-1] ;
                            lbchild.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );
                            WriteBPlusNode(x.Pointer[i] ,child );
                        } else {	//���J
                            lbchild.key[lbchild.nkey] = x.key[i-1];	//�����ӽڵ㸴�Ƶ������ֵܵ�ĩβ
                            lbchild.nkey ++;

                            for(j = 0 ; j < child.nkey ; j++) {	//��child�ڵ㿽����lbchild�ڵ��ĩβ,
                                lbchild.key[lbchild.nkey + j] = child.key[j] ;
                                lbchild.Pointer[lbchild.nkey + j] = child.Pointer[j];
                            }
                            lbchild.Pointer[lbchild.nkey + j] = child.Pointer[j];
                            lbchild.nkey += child.nkey ;		  //�Ѿ���child������lbchild�ڵ�


                            //�ͷ�child�ڵ�Ĵ洢�ռ�,x.Pointer[i]


                            //���ҵ��ؼ��ֵĺ���child��ؼ������ֵܵĺ���lbchild�ϲ���,���ùؼ���ǰ��,ʹ��ǰ�ڵ�Ĺؼ��ּ���һ��
                            for(j = i - 1  ; j < x.nkey - 1 ; j++) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );

                            i --;

                        }

                    } else {	 //����x.key[i]ֻ�����ֵ�
                        BPlusNode rbchild;
                        ReadBPlusNode(x.Pointer[i+1] ,rbchild );

                        if( rbchild.nkey > MAX_KEY/2 ) {  //���K

                            child.key[child.nkey] = x.key[i];
                            child.nkey ++;

                            child.Pointer[child.nkey] = rbchild.Pointer[0];
                            x.key[i] = rbchild.key[0];

                            for( j = 0 ; j < rbchild.nkey -1 ; j++) {
                                rbchild.key[j] = rbchild.key[j+1];
                                rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            }
                            rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            rbchild.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );
                            WriteBPlusNode(x.Pointer[i+1] ,rbchild );

                        } else {	//���L
                            child.key[child.nkey] = x.key[i];
                            child.nkey ++;

                            for(j = 0; j < rbchild.nkey ; j++) {	//��rbchild�ڵ�ϲ���child�ڵ��
                                child.key[child.nkey + j] = rbchild.key[j];
                                child.Pointer[child.nkey +j] = rbchild.Pointer[j];
                            }
                            child.Pointer[child.nkey +j] = rbchild.Pointer[j];

                            child.nkey += rbchild.nkey;

                            //�ͷ�rbchild�ڵ���ռ�õĿռ�,x,Pointer[i+1]

                            for(j = i ; j < x.nkey - 1 ; j++ ) { //��ǰ���ؼ���֮��Ĺؼ�������һλ,ʹ�ýڵ�Ĺؼ���������һ
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x);
                            WriteBPlusNode(x.Pointer[i] ,child );

                        }

                    }
                }
            } else {	//�����亢�ӽڵ�����ڵ�
                if(child.nkey > MAX_KEY/2 ) { //���M

                } else {	//�����ӽڵ㲻������
                    if( i > 0 ) { //�����ֵ�
                        BPlusNode lbchild;
                        ReadBPlusNode(x.Pointer[i-1] ,lbchild );

                        if( lbchild.nkey > MAX_KEY/2 ) {	//���N
                            for(j = child.nkey ; j > 0  ; j--) {
                                child.key[j] = child.key[j-1];
                                child.Pointer[j] = child.Pointer[j-1];
                            }
                            child.key[0] = x.key[i-1];
                            child.Pointer[0] = lbchild.Pointer[lbchild.nkey-1];
                            child.nkey ++;
                            lbchild.nkey --;

                            x.key[i-1] = lbchild.key[lbchild.nkey-1];

                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );
                            WriteBPlusNode(x.Pointer[i] ,child );
                            WriteBPlusNode(current ,x );

                        } else {	//���O

                            for( j = 0 ; j < child.nkey ; j++ ) {	//�����ֵܺ��ӽڵ�ϲ�
                                lbchild.key[lbchild.nkey + j ] = child.key[j] ;
                                lbchild.Pointer[lbchild.nkey + j] = child.Pointer[j] ;
                            }
                            lbchild.nkey += child.nkey ;

                            lbchild.Pointer[MAX_KEY] = child.Pointer[MAX_KEY];

                            //�ͷ�childռ�õĿռ�x.Pointer[i]

                            for( j = i - 1; j < x.nkey - 1 ; j ++ ) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }

                            x.nkey --;

                            WriteBPlusNode(x.Pointer[i-1] ,lbchild );
                            WriteBPlusNode(current ,x );

                            i --;

                        }

                    } else {	 //����ֻ�����ֵ�
                        BPlusNode rbchild;
                        ReadBPlusNode(x.Pointer[i+1] ,rbchild );

                        if( rbchild.nkey > MAX_KEY/2 ) {	//���P
                            x.key[i] = rbchild.key[0] ;
                            child.key[child.nkey] = rbchild.key[0];
                            child.Pointer[child.nkey] = rbchild.Pointer[0];
                            child.nkey ++;

                            for(j = 0 ; j < rbchild.nkey - 1 ; j ++) {
                                rbchild.key[j] = rbchild.key[j+1];
                                rbchild.Pointer[j] = rbchild.Pointer[j+1];
                            }
                            rbchild.nkey --;

                            WriteBPlusNode(current ,x );
                            WriteBPlusNode(x.Pointer[i+1] ,rbchild );
                            WriteBPlusNode(x.Pointer[i] ,child );

                        } else {	//���Q
                            for(j = 0 ; j < rbchild.nkey ; j ++) {
                                child.key[child.nkey + j] = rbchild.key[j];
                                child.Pointer[child.nkey + j] = rbchild.Pointer[j];
                            }
                            child.nkey += rbchild.nkey;
                            child.Pointer[MAX_KEY] = rbchild.Pointer[MAX_KEY];

                            //�ͷ�rbchildռ�õĿռ�x.Pointer[i+1]

                            for(j = i ; j < x.nkey - 1 ; j ++ ) {
                                x.key[j] = x.key[j+1];
                                x.Pointer[j+1] = x.Pointer[j+2];
                            }
                            x.nkey --;

                            WriteBPlusNode(current ,x );
                            WriteBPlusNode(x.Pointer[i] ,child );


                        }

                    }

                }

            }

            delete_BPlus_tree(x.Pointer[i] ,record );
        }


    }


}



void	BPlusTree :: Delete_BPlus_Tree(TRecord &record ) {	//��B+��ɾ��һ���ؼ���
    delete_BPlus_tree(ROOT ,record );

    BPlusNode rootnode;
    ReadBPlusNode(ROOT ,rootnode );

    if( !rootnode.isleaf && rootnode.nkey == 0 ) {  //���ɾ���ؼ��ֺ���ڵ㲻��Ҷ�ڵ㣬���ҹؼ�������Ϊ0ʱ���ڵ�ҲӦ�ñ�ɾ��
        //�ͷ�ROOT�ڵ�ռ�õĿռ�
        ROOT = rootnode.Pointer[0];			//���ڵ�����,B+���߶ȼ�1

    }

}




void  BPlusTree :: EnumLeafKey() {	//����ö��B+��Ҷ�ڵ�����йؼ���
    BPlusNode head;

    ReadBPlusNode(ROOT ,head );

    while(!head.isleaf ) {
        ReadBPlusNode(head.Pointer[0] ,head );
    }

    while(1) {
        for(int i = 0 ; i < head.nkey ; i ++)
            printf("%d\n",head.key[i] );

        if(head.Pointer[MAX_KEY] == 0 )
            break;

        ReadBPlusNode(head.Pointer[MAX_KEY] ,head );
    }

}




inline long	BPlusTree :: GetBPlusNode()	 const { //�ڴ����Ϸ���һ��B+���ڵ�ռ�
    fseek(Bfile ,0 ,SEEK_END);

    return  ftell(Bfile );
}

inline void	BPlusTree :: ReadBPlusNode(const long address ,BPlusNode	&r ) const { //��ȡaddress��ַ�ϵ�һ��B+���ڵ�
    fseek(Bfile ,address ,SEEK_SET );
    fread((char*)(&r) ,sizeof(BPlusNode) ,1 ,Bfile);

}


inline void	BPlusTree :: WriteBPlusNode(const long address ,const BPlusNode &r ) { //��һ��B+���ڵ�д��address��ַ
    fseek(Bfile ,address ,SEEK_SET );
    fwrite((char*)(&r) ,sizeof(BPlusNode) ,1 ,Bfile);

}



int main() {
    BPlusTree tree;

    tree.Build_BPlus_Tree();		//����

    TRecord record;
    SearchResult result;

    int time1 = clock();

    int i;
    for(i = 0 ; i < 100000 ; i ++ ) {
        record.key = i;
        tree.Insert_BPlus_Tree(record );
        //	printf("%d\n",i );
    }

    for( i = 99997 ; i > 0; i--) {
        record.key = i;
        tree.Delete_BPlus_Tree(record );
        tree.Search_BPlus_Tree(record ,result );
        if(result.exist )
            break;
        //	printf("%d\n",i);
    }

    cout<<clock() - time1 <<endl;
    system("pause");
    tree.EnumLeafKey();

    tree.~BPlusTree();
    system("pause");
    return 0;
}

