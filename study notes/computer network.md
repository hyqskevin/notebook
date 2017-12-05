## <center>第一章 概述</center>
  - 1.1 计算机网络定义：通过传输介质、通信设施和网络协议，把分散在不同地点的计算机设备连接起来，实现资源共享和数据传输
  - 1.2 网路基本功能：数据通信，资源共享，给网络用户提供好的性价比，提供大容量网络存储，提供分布式处理，对分散的计算机进行集中控制，提供高可靠性的系统
  - #### 1.3 网络的组成结构
    - 物理结构：通信子网(网络核心，分为交换节点和访问节点)，资源子网(网络边缘，端节点)

    |端系统/主机(资源子网)|边缘路由器|通信链路/分组交换机|ISP(网络的网络)|网络核心(通信子网)|
    |:----- |:-----|:-----|:----|:----|
    |end system/host|edge router|packet switch|Internet Service Provider|Internet|
    |PC/服务器(server)/移动计算机|DSL/电缆/FTTH/以太网/WiFi/3G|路由器(router)/链路层交换机(link-layer switch)|ISP/PoP/多宿/对等/IXP|

    |链接方式|协议|数据传输方式|丢包|
    |:---|:---|:---|:---|
    |通信链路(communication link)|TCP/IP/UDP/私有|包(package)、电路(circuit)报文(message)交换|节点处理(nodal processing)、排队(queue)、传输(transmission)、传播(propagation)时延||
    |bit/s，bps/双绞铜线，同轴电缆，光纤，无线信道|定义在多个通信实体间交换报文的格式,次序和动作(语法，语义，同步)|电路交换需要预留通信沿路径需要的资源，分为频分复用(FDM)和时分复用(TDM)<br>报文需要分组(packet)，用通信链路传输,宽带共享更好，更简单有效，成本更低<br>包交换不常用|到达的分组发现队列已满，无存储空间时，路由器将丢弃分组|

    - 协议体系结构：Internet 协议栈
      - 协议数据单元(PDU)格式：边界|地址|控制 | 数据 | 校验|边界
      - 网络服务：面向连接的服务(通信前先建立一条连接)|无连接服务(不需要事先建立连接，通过PDU格式发送)

    |协议栈层次|应用层(application)|运输层(transport)|网络层(network)|链路层(link)|物理层(physical)|
    |:---|:---|:---|:---|:---|:---|
    |作用|包括应用程序及应用层协议|应用程序端点之间传送|主机间连接|节点间传输|比特传输|
    |信息名称|报文(message)|报文段(segment)|数据报(datagram)|帧(frame)||
    |协议|HTTP/SMTP/FTP|TCP/UDP|IP|Enternet/Wifi…||

      - 封装(encapsulation)：<p>
      $M$(application-layer message)<br>
      —>$H_t$(teansport-lsyer segment)<br>
      ———>$H_n$(network-layer datagram)<br>
      —————>$H_l$(link-layer frame)<br>

    - 拓扑结构：总线型，环形，星形……
  - 1.4 网络分类
    - 局域网，城域网，广域网
    - 公用网，专用网
    - 电路交换网络，存储转发网络(报文交换，分组交换)
  - 1.5 时延
    - 节点时延：$d_{nomal}=d_{proc}+d_{queue}+d_{trans}+d_{prop}$<br>
    - 端到端时延：$d_{end-end}=N(d_{proc}+d_{tran}+d_{prop})$<br>
    - 传输时延：$d_{tran}=\frac{L(报文长度)}{R(传输速率)}$
---
## <center>第二章 应用层(application-layer)</center>
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
---
## <center>第三章 运输层</center>
  - 3.1 概述：为不同主机上的应用进程之间提供逻辑通信
  - 3.2 协议数据单元(TPDU)：运输层首部+运输层报文段(segment)
  - 3.3 复用与分用：应用层多个进程通过不同**端口号**到运输层，运输层通过**IP地址**到网络层，端口号+IP构成套接字，通过
    - 无连接的
    - 面向连接的
  - 3.4 运输实现
    - 连接：
    - 释放：
    - 运输控制：

  - #### 3.5 TCP*

  - #### 3.6 UDP*

  - #### 3.7 可靠的数据传输协议(RDT)*
      - 停-等协议
      - 回退N协议
      - 选择重传协议

- #### 3.8 拥塞控制
---
## <center>第四章 网络层</center>
