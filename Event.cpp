#include <iostream>
#include <thread>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <optional>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <memory>

using namespace std;

enum class EventType
{
    NA = 0,
    EVENT1 = 1,
    EVENT2 = 2,
    EVENT3 = 3,
    TIMER1S = 4,

};

using EventHandler = function<void(const EventType)>;

typedef chrono::steady_clock t1;
typedef chrono::milliseconds t_ms;

class EventObserver
{
public:
    virtual void notify() = 0;
    virtual ~EventObserver() = default;
};

struct Timer
{
    chrono::milliseconds expiry;
    std::chrono::time_point<std::chrono::steady_clock> register_t;
    function<void(shared_ptr<void>)> callback;
    shared_ptr<void> context;
    /*Timer(chrono::milliseconds e,std::chrono::time_point<std::chrono::steady_clock> r,function<void(shared_ptr<void>)> c,shared_ptr<void> ct)
     {
         expiry=e;
         register_t=r;
         callback=c;
         context=ct;



     }
         */
};

class EventTimer
{
    std::vector<Timer> timers_;

public:
    void add(chrono::seconds timeout, function<void(shared_ptr<void>)> callback, shared_ptr<void> context)
    {
        Timer t1;
        t1.expiry = timeout;
        t1.context = context;
        t1.register_t = chrono::steady_clock::now();
        t1.callback = callback;
        timers_.emplace_back(t1);
    }

    void poll()
    {
        cout << "polling vector for expired timer" << endl;
        if (timers_.empty() == true)
        {
            return;
        }
        std::vector<Timer> expiredTimer;
        auto t_now = std::chrono::steady_clock::now();

        auto begin = remove_if(timers_.begin(), timers_.end(), [&t_now, &expiredTimer](const Timer &timer)
                               {
                                   long elapsed=chrono::duration_cast<chrono::milliseconds>(t_now-timer.register_t).count();
                                   long expired=chrono::duration_cast<chrono::milliseconds>(timer.expiry).count();
                                   if (elapsed >= expired)
                                   {
                                       expiredTimer.push_back(timer);
                                       return true;
                                   }

                                   return false; });
        timers_.erase(begin, timers_.end());

        for (const auto &t : expiredTimer)
        {
            t.callback(t.context);
        }
    }
    void run_timer()
    {
        int count = 0;
        while (true)
        {

            cout << count << " second passed" << endl;
            usleep(5);
            count++;
            poll();
        }
    }
};

class EventLoop
{
    bool running;
    unordered_map<EventType, EventHandler> eventhandler;
    // bool event_Recieved;
    // EventType incoming_event;
    queue<EventType> eventQueue;
    mutex mutex_;
    condition_variable cv;

public:
    EventLoop() : running{true}
    {
    }

    void registerHandler(EventType e, EventHandler handler)
    {
        eventhandler[e] = handler;
    }

    EventType GetNextEvent()
    {
        unique_lock<mutex> lock{mutex_};

        cv.wait_for(lock, std::chrono::milliseconds(200), [this]()
                    { return !eventQueue.empty(); });

        if (eventQueue.empty() == false)
        {

            EventType e = eventQueue.front();
            eventQueue.pop();

            return e;
        }

        return EventType::NA;
    }

    void PostEvent(EventType e)
    {
        unique_lock<mutex> lock{mutex_};

        eventQueue.push(e);

        // event_Recieved=true;
        // incoming_event=e;

        cv.notify_one();
    }

    void HandleEvent(EventType e)
    {
        auto it = eventhandler.find(e);
        if (it != eventhandler.end())
        {
            it->second(e);
        }
    }

    void run()
    {
        cout << "timer is running" << endl;
        auto t_now = chrono::steady_clock::now();
        auto t_last = t_now;
        long elapsed = 0;
        while (running)
        {
            t_now = chrono::steady_clock::now();
            elapsed += chrono::duration_cast<std::chrono::milliseconds>(t_now - t_last).count();
            t_last = t_now;

            if (elapsed >= 2000)
            {
                PostEvent(EventType::TIMER1S);
                elapsed = 0;
            }

            cout << "[main] waiting for....." << endl;
            EventType e = GetNextEvent();
            if (e != EventType::NA)
            {
                HandleEvent(e);
            }
        }
    }
    void stop()
    {
        running = false;
    }
};

int main()
{
    /*
    EventLoop ev;

    auto handler = [](const EventType e)
    {
        cout << "received event : " << static_cast<int>(e) << endl;
    };

    auto handler_timer = [](const EventType e)
    {
        cout << "received event for timer: " << static_cast<int>(e) << endl;
    };

    auto thread_ = thread([&ev]()
                          {
                              this_thread::sleep_for(chrono::milliseconds(200));
                              ev.PostEvent(EventType::EVENT1);
                              this_thread::sleep_for(chrono::milliseconds(200));
                              ev.PostEvent(EventType::EVENT2);
                              this_thread::sleep_for(chrono::milliseconds(200));
                              ev.PostEvent(EventType::EVENT3);
                              this_thread::sleep_for(chrono::seconds(10));

                              ev.stop(); });

    ev.registerHandler(EventType::EVENT1, handler);
    ev.registerHandler(EventType::EVENT2, handler);
    ev.registerHandler(EventType::EVENT3, handler);
    ev.registerHandler(EventType::TIMER1S, handler_timer);

    ev.run();

    thread_.join();

    */
    EventTimer et;

    auto handler = [](int n)
    {
        cout << "received int : " << n << endl;
    };

    auto thread_ = thread([&et]() {

    });

    et.run_timer();

    return 0;
}