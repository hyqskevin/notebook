###1.概述
|端系统/主机(资源子网)|边缘路由器|—通信链路/分组交换机—|ISP(网络的网络)|网络核心(通信子网)|
|:----- |:-----|:-----|:----|:----|
|end system/host|edge router|packet switch|Internet Service Provider|Internet|
|PC/服务器(server)/移动计算机|DSL/电缆/FTTH/以太网/WiFi/3G|路由器(router)/链路层交换机(link-layer switch)|ISP/PoP/多宿/对等/IXP|

|链接方式|协议|数据传输方式|丢包|
|:---|:---|:---|:---|
|通信链路(communication link)|TCP/IP/UDP/私有|包(package)、电路(circuit)报文(message)交换|节点处理(nodal processing)、排队(queue)、传输(transmission)、传播(propagation)时延||
|bit/s，bps/双绞铜线，同轴电缆，光纤，无线信道|定义在多个通信实体间交换报文的格式,次序和动作(语法，语义，同步)|电路交换需要预留通信沿路径需要的资源，分为频分复用(FDM)和时分复用(TDM)<br>报文需要分组(packet)，用通信链路传输,宽带共享更好，更简单有效，成本更低<br>包交换不常用|到达的分组发现队列已满，无存储空间时，路由器将丢弃分组|

- 时延
  - 节点时延：$d_{nomal}=d_{proc}+d_{queue}+d_{trans}+d_{prop}$<br>
  - 端到端时延：$d_{end-end}=N(d_{proc}+d_{tran}+d_{prop})$<br>
  - 传输时延：$d_{tran}=\frac{L(报文长度)}{R(传输速率)}$

- Internet 协议栈层次

|协议栈层次|应用层(application)|运输层(transport)|网络层(network)|链路层(link)|物理层(physical)|
|:---|:---|:---|:---|:---|:---|
|作用|包括应用程序及应用层协议|应用程序端点之间传送|主机间连接|节点间传输|比特传输|
|信息名称|报文(message)|报文段(segment)|数据报(datagram)|帧(frame)||
|协议|HTTP/SMTP/FTP|TCP/UDP|IP|Enternet/Wifi…||

- 封装(encapsulation)：

  $M$(application-layer message)<br>
  —>$H_t$(teansport-lsyer segment)<br>
  ———>$H_n$(network-layer datagram)<br>
  —————>$H_l$(link-layer frame)<br>

### 2.应用层(application-layer)
- 应用层结构(application architecture)
  - 客户-服务器系统结构(client-server)：由一个总是打开的主机作为服务器，完成其它称为客户机的请求
  - P2P结构：应用程序在间断连接的主机之间使用直接通信(BitTorrent,Skype),具有自扩展性
  - 进程通信：
- 运输服务(网络服务)
  - 数据传输|定时|吞吐量|安全性 服务
  - 运输服务类型：TCP：面向连接的服务(握手过程)，可靠的数据传输(无差错，丢失，乱序)，网络控制(收发双方速度同步)，拥塞控制<br>
    UDP：轻量级，无连接服务，不可靠的数据传输,无拥塞控制<br>
    TCP/UDP：不提供带宽保障和定时功能

- ####应用层协议(protocol)：HTTP，SMTP，FTP，DNS，P2P…  
  - 协议定义交换报文类型，语法，语义，发送响应规则
  - Web & HTTP：
  - SMTP：
  - FTP：
  - DNS：
  - P2P：
- TCP套接
