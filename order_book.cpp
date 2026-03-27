#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <array>
#include <atomic>
template<typename T,size_t size>

class LockFreeQueue
{
    static constexpr size_t buffersize=size+1;
    std::array<T,buffersize> buffer;
    std::atomic<size_t> head{0};
    std::atomic<size_t> tail{0};

    static constexpr size_t getpositionAfter(size_t pos)
    {
        return (pos+1)%size;
    }
    LockFreeQueue()
    {}
    bool push(const T& data)
    {
        auto oldwritepos=head.load();
        auto newritepos=getpositionAfter(oldwritepos);
        if(newritepos==tail.load())
        return false;

        buffer[oldwritepos]=data;
        head.store(newritepos);
        return true;
    }
    bool pop(T& data)
    {
        auto oldwritepos=tail.load();
        auto oldreadpos=head.load();
        if(oldwritepos==oldreadpos)
        return false;

        data=buffer[oldreadpos];
        tail.store(getpositionAfter(oldreadpos));
        return true;
    }
};

enum class type{
    buy,
    sell
};

struct Order{
    int id;
    type type;
    double price;
    int quantity;
    int seq;
};

struct Trade{
    int buyid;
    int sellid;
    double price;
    int quantity;
};

typedef std::shared_ptr<Order> OrderPtr;

struct buycomp{
    bool operator()(const OrderPtr& a,const OrderPtr& b)
    {
        if(a->price!=b->price)
        {
            return a->price<b->price;
        }
        return a->seq>b->seq;
    }
};

struct sellcomp{
    bool operator()(const OrderPtr& a,const OrderPtr& b)
    {
        if(a->price!=b->price)
        {
            return a->price>b->price;
        }
        return a->seq>b->seq;
    }
};

class OrderBook{

    private:

    std::priority_queue<OrderPtr,std::vector<OrderPtr>,buycomp> buys;
    std::priority_queue<OrderPtr,std::vector<OrderPtr>,sellcomp> sells;
    int seq=0;
    std::map<int,OrderPtr> live;

    void purgesell()
    {
        while(!sells.empty())
        {
            const auto& top=sells.top();
            if(top->quantity<=0||live.count(top->id)==false)
            {
                sells.pop();
            }
            else
            {
                break;
            }
        }
    }

    void purgebuy()
    {
        while(buys.empty()!=false)
        {
            const auto& top=buys.top();
            if(top->quantity<=0||live.count(top->id)==false)
            {
                buys.pop();
            }
            else
            {
                break;
            }
        }
    }

    void match()
    {
        while(true)
        {
            purgebuy();
            purgesell();
            if(buys.empty()||sells.empty())
            {
                break;
            }
            OrderPtr buy=buys.top();
            OrderPtr sell=sells.top();
            if(buy->price<sell->price)
            {
                break;
            }
            int qty=std::min(buy->quantity,sell->quantity);
            trades.push_back(Trade{buy->id,sell->id,buy->price,qty});
            buy->quantity-=qty;
            sell->quantity-=qty;
            if(buy->quantity==0)
            {
                live.erase(buy->id);
            }
            if(sell->quantity==0)
            {
                live.erase(sell->id);
            }
        }
    }

    public:
    std::vector<Trade> trades;

    OrderBook()
    {
        
    }   

    bool newOrder(int id,type type,double price,int qty)
    {
        if(live.find(id)==live.end())
        {
            auto o=std::make_shared<Order>(Order{id,type,price,qty,this->seq++});
            live.insert({id,o});
            if(type==type::buy)
            {
                buys.push(o);
            }
           else
           {
            sells.push(o);
           }
        }
        match();
        return true;
    }

    bool cancelOrder(int id)
    {
        auto it=live.find(id);
        if(it!=live.end())
        {
            it->second->quantity=0;
            live.erase(it);
            return true;
        }
        return false;
    }

    bool modifyOrder(int id,double price,int qty)
    {
        auto it=live.find(id);
        if(it!=live.end())
        {
            type t=it->second->type;
            it->second->quantity=0;
            auto o=std::make_shared<Order>(Order{id,t,price,qty,this->seq++});
            it->second=o;
            if(t==type::buy)
            {
                buys.push(o);
            }
            else
            {
                sells.push(o);
            }
            match();
            return true;
        }
        return false;
    }

    void print(){

        std::map<int,int,std::greater<int>> buy;
        std::map<int,int> sell;

        for(auto itr=live.begin();itr!=live.end();itr++)
        {
            if(itr->second->type==type::buy)
            {
                buy[itr->second->price]+=itr->second->quantity;
            }
            else
            {
                sell[itr->second->price]+=itr->second->quantity;
            }
        }

        std::cout<<"BUY QTY"<<" "<<"PRICE"<<" "<<"SELL QTY"<<std::endl;
        
        std::vector<int> prices;
        for(auto itr=buy.begin();itr!=buy.end();itr++)
        {
            prices.push_back(itr->first);
        }
        for(auto itr=sell.begin();itr!=sell.end();itr++)
        {
            prices.push_back(itr->first);
        }
        sort(prices.begin(),prices.end());
        prices.erase(std::unique(prices.begin(),prices.end()),prices.end());

        for(int i=0;i<prices.size();i++)
        {
            int p=prices[i];
            if(buy.find(p)!=buy.end())
            {
                std::cout<<buy[p]<<" "<<p<<" ";
            }
            else{
                std::cout<<" "<<p<<" ";
            }
            if(sell.find(p)!=sell.end())
            {
                std::cout<<sell[p]<<"\n";
            }
            else{
                std::cout<<" "<<"\n";
            }
        }
        



    }
      

};

void run()
{
    OrderBook order;
    while(1)
    {
        std::string s1;
        std::cin>>s1;
        if(s1=="new")
        {
            int id,qty;
            double price;
            std::string type;
            std::cin>>id>>type>>price>>qty;
            if(type=="buy")
            {
                order.newOrder(id,type::buy,price,qty);
            }
            else
            {
                order.newOrder(id,type::sell,price,qty);
            }
        }
        else if(s1=="cancel")
        {
            int id;
            std::cin>>id;
            order.cancelOrder(id);
        }
        else if(s1=="modify")
        {
            int id,qty;
            double price;
            std::cin>>id>>price>>qty;
            order.modifyOrder(id,price,qty);
        }
        else if(s1=="print")
        {
            order.print();
        }
        else if(s1=="exit")
        {
            break;
        }   
    }
}


int main()
{
    run();
    return 0;
}