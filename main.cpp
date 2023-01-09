#include<math.h>
#include<stdio.h>
#include<conio.h>

template<typename ElementType> struct less
{
    bool operator ()(const ElementType & A,const ElementType &B)
    {
        return A<B ;
    }
} ;
template<typename ElementType> struct greater
{
    bool operator ()(const ElementType &A,const ElementType &B)
    {
        return A>B ;
    }
} ;

template<typename ElementType>
void swap(ElementType &A,ElementType &B)
{
     ElementType temp=A ;
     A=B ; B=temp ;
} ;

template<typename ElementType> class vector
{

private:
    ElementType* Array ;
    int cur_size,cur_limit_size ;

public:
    typedef ElementType* iterator ;
    typedef ElementType value_type ;

    void push_back(ElementType x)
    {
         if(cur_size+1<cur_limit_size)
         {
             Array[cur_size++]=x ;
            //printf("DID THIS with %d %d\n",cur_size,cur_limit_size) ;
         }
         else
         {
           // printf("DID THIS with %d %d\n",cur_size,cur_limit_size) ;
             if(cur_limit_size==0) ++cur_limit_size ;
             ElementType* NewArray=(ElementType*)malloc(2*cur_limit_size*sizeof(ElementType)) ;

             for(int i=0;i<cur_size;++i)
                {
                    NewArray[i]=Array[i] ;
                }

             free(Array) ;
             NewArray[cur_size++]=x  ;

             cur_limit_size=2*cur_limit_size ;
             Array=NewArray ;

         }

    }

    void clear()
    {
        free(Array) ;
        cur_limit_size=0 ;
        cur_size=0 ;
    }

    void pop_back()
    {
        --cur_size ;
    }
    bool empty()
    {
        return cur_size==0 ;
    }
    iterator begin()
    {
        return Array ;
    }
    iterator end()
    {
        return Array+cur_size ;
    }
    int size()
    {
        return cur_size ;
    }
    void resize(int n=0,ElementType value=ElementType())
    {
        free(Array) ;
        Array=(ElementType*)malloc(n*sizeof(ElementType)) ;
        for(int i=0;i<n;++i)
        {
            Array[i]=value ;
        }
        cur_limit_size=n ;
        cur_size=n ;
    }

    vector<ElementType>(int initial_size=0,ElementType value=ElementType())
    {
        Array=(ElementType*)malloc(initial_size*sizeof(ElementType)) ;
        cur_size=initial_size ;
        cur_limit_size=initial_size ;
        for(int i=0;i<cur_size;++i)
        {
             Array[i]=value ;
        }


    }
    ElementType& operator [](int x)
    {
        return this->Array[x] ;
    }


} ;

template<class ElementType,class Container=vector<ElementType>,class Compare=less<ElementType> >
class priority_queue
{
private :
    Container tree ;
    Compare comp ;
    int numNode ;
public:
     priority_queue<ElementType,Container,Compare>()
     {
         numNode=0 ;
         tree=vector<ElementType>(1,0) ;
     }
     int size()
     {
         return numNode ;
     }
     bool empty()
     {
         return numNode==0 ;
     }
     ElementType top()
     {
         return tree[1] ;
     }
     void push(ElementType x)
     {
         ++numNode ;
         tree.push_back(x) ;
         for(int k=numNode;k>1;k/=2)
            if(comp(tree[k/2],tree[k])==true)
                {
                    swap(tree[k],tree[k/2]) ;
                }
            else break ;
     }
     void printToCheck()
     {
         for(auto it=tree.begin()+1;it!=tree.end();++it)
         printf("%d ",*it) ;
         printf("\n") ;
     }
     void pop()
     {
         swap(tree[1],tree[numNode]) ;
         tree.pop_back() ;
         --numNode ;
         for(int node=1;node*2<=numNode;)
         {
             if(comp(tree[node],tree[node*2])==false && (node*2+1>numNode || comp(tree[node],tree[node*2+1])==false))
                  break ;
             if(node*2+1>numNode)
             {
                 swap(tree[node],tree[node*2]) ;
                 node=node*2 ;
             }
             else if(comp(tree[node*2],tree[node*2+1])==true)
             {
                 swap(tree[node],tree[node*2+1]) ;
                 node=node*2+1 ;
             }
             else
             {
                 swap(tree[node],tree[node*2]) ;
                 node=node*2 ;
             }
         }
     }


} ;

int main()
{

    // TEST SOME EXAMPLES HERE
    priority_queue<int,vector<int>,greater<int>> q ;
    q.push(1) ; q.push(3) ; q.push(5) ; q.pop() ;
    q.push(2) ; q.push(4) ; q.push(6) ; q.pop() ;
    q.push(9) ; q.push(8) ; q.push(7) ; q.pop();

    while(!q.empty())
    {
        q.printToCheck() ;
        q.pop() ;
    }
}
