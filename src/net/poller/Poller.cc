#include "Poller.h"

Poller::Poller(EventLoop *Loop)
    : ownerLoop_(Loop)
{
}

// 判断channel是否在当前Poller中
bool Poller::hasChannel(Channel *channel) const
{
    // 通过channel的fd在map中查找
    auto it = channels_.find(channel->fd());
    // 如果找到了，判断是否是同一个channel
    return it != channels_.end() && it->second == channel;
}