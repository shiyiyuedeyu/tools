# 一 结论
一个socket是否设置为阻塞模式，只会影响到connect/accept/send/recv等四个socket API函数，不会影响到select/poll/epoll_wait函数，后三个函数的超时或者阻塞时间是由其函数自身参数控制的。

# 二 原理分析
accept函数并不参与三次握手过程，accept函数从已经连接的队列中取出连接，返回clientfd，最后客户端与服务端分别通过connfd和clientfd进行通信（调用send或者recv函数）。

## 2.1 socket是否被设置成阻塞模式对下列API造成的影响
1、当connfd被设置为阻塞模式时（默认行为，无需设置），connect函数会一直阻塞到连接成功或超时或出错，超时值需要修改内核参数。
2、当connfd被设置成非阻塞模式，无论连接是否建立成功，connect函数都会立刻返回，那如何判断connect函数是否连接成功呢？
接下来使用select和poll函数去判断socket是否可写即可，当然，linux系统上还需要额外加一步——使用getsocketopt函数判断此时socket是否有错误，这就是所谓的异步connect或者叫非阻塞connect。
3、当listenfd设置成阻塞模式（默认行为，无需额外设置）时，如果连接pending队列中有需要处理的连接，accept函数会立即返回，否则会一直阻塞下去，直到洗呢连接到来。
4、当listenfd设置成非阻塞模式，无论连接pending队列中是否有需要处理的连接，accept都会立即返回，不会阻塞。如果有连接，则accept返回一个大于0的值，这个返回值即是我们上文所说的clientfd；
如果没有连接，accept返回值小于0，错误码errno为EWOULDBLOCK（或者EAGAIN，这两个错误码相等）。
5、当connfd或clienfd设置成阻塞模式时：send函数会尝试发送数据，如果对端因为TCP窗口太小导致本端无法将数据发送出去，send函数会一直阻塞直到对端TCP窗口变大足以发送数据或者超时，
有的话，取到数据后返回。send和recv函数的超时时间可以分别使用SO_SNDTIMEO和SO_RECVTIMEO两个socket选项来设置。
6、当connfd或clientfd设置成非阻塞模式时，send和recv函数都会立即返回，send函数即使因为对端TCP窗口太小发不出去也会立即返回，recv函数如果无数据可收也会立即返回，此时这两个函数的
返回值都是-1.错误码errno是EWOULDBLOCK（或EAGAIN，与上面同）。两种情况下，send和recv函数的返回值有三种情形，分别是大于0，等于0和小于0。

# 三 select/poll/epoll_wait函数的等待或超时时间

# 四 使用epoll模型是否要将socket设置成非阻塞的
答案是需要的。
epoll模型通常用于服务端，那讨论的socket只有listenfd和clientfd了。
