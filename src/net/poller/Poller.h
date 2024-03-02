#ifndef POLLER_H
#define POLLER_H


#include "noncopyable.h"
#include "Timestamp.h"
#include "Channel.h"

#include <vector>
#include <unordered_map>

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel *>;

    Poller(EventLoop *loop);
    virtual ~Poller();

    // 需要交给派生类实现的接口
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    // 判断channel是否在当前Poller中
    bool hasChannel(Channel *channel) const;

    // EventLoop可以通过该接口获取默认的IO复用实现方式(默认epoll)
    /** 
     * 它的实现并不在 Poller.cc 文件中
     * 如果要实现则可以预料会其会包含EPollPoller PollPoller
     * 那么外面就会在基类引用派生类的头文件，这个抽象的设计就不好
     * 所以外面会单独创建一个 DefaultPoller.cc 的文件去实现
     */
    static Poller* newDefaultPoller(EventLoop *Loop);

protected:
    
    using ChannelMap = std::unordered_map<int, Channel *>;

    // 储存 channel 的映射，（sockfd -> channel*）
    ChannelMap channels_;

private:
    // 定义Poller所属的事件循环EventLoop
    EventLoop *ownerLoop_; 
};


#endif // POLLER_H


