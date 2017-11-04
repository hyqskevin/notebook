### 6to4
6to4，一种转送机制，设计目的是为了从网际协议版本 4（IPv4）过渡到版本 6（IPv6）。这个协定可以让IPv6封包，不必经过外部通道（tunnel）就可以穿越IPv4互联网。为了能够使6to4网络能够与原生IPv6网络之间沟通，必须建立一个特定的转送服务器。RFC 6343 规范了6to4网络的建置方式。
这个机制提出的主要目的，是当成暂时的过渡机制，到IPv6网络完全建置之后可能就会消失。

### tedero
Teredo通过在UDP/IPv4数据包内封装IPv6数据包来缓解这个问题，大多数NAT可以正确转发此种流量。这样一来，NAT后的IPv6感知主机可以作为Teredo隧道端点，即使它没有专用的公网IPv4地址。实际上，一个实现Teredo的主机可以在没有本地网络环境合作的条件下获得IPv6连通性。

### 配置教程
- 1.Win+R gpedit.msc
- 打开计算机配置——管理模板——网络——TCPIP设置——IPv6转换技术
- 6to4 状态：已启用   已禁用状态
- ISATAP 状态：已启用   已禁用状态
- Teredo 状态：已启用   企业客户端
- Teredo 默认限定：已启用   已启用状态
- Teredo 服务器名称：已启用    teredo.remlab.net

以下几个服务器可通过ping通的质量择优选取:
      teredo.remlab.net / teredo-debian.remlab.net (Germany)
      teredo.autotrans.consulintel.com (Spain)
      teredo.ipv6.microsoft.com (USA, Redmond) (default for WindowsXP/2003/Vista/2008 OS)
      teredo.ngix.ne.kr (South Korea)
      teredo.managemydedi.com (USA, Chicago)
      teredo.trex.fi (Finland)
更多服务器动态请前往[]http://en.wikipedia.org/wiki/Teredo_tunneling#Servers 查看

- 配置DNS优先解析为ipv6地址:
管理员CMD
```
Reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\Dnscache\Parameters /v AddrConfigControl /t REG_DWORD /d 0
```

- 测试是否成功配置：
```
netsh int ipv6 show teredo state
```
