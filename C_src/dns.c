#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <arpa/inet.h>

#define PORT 53
#define BUFFER_SIZE 1024
#define IPSIZE 4
#define bzero(a, b) memset(a, 0, b)
const char *SRV_IPADDR = "10.3.9.4";
const char *LOCAL_HOST = "127.0.0.1";


typedef struct DNSHEADER 
{
    unsigned short transactionID;   // 会话标识
    /**
     * flags(2 Bytes):cd
     * QR : 1 bit               0查询 / 1响应
     * Opcode : 4 bit           0标准查询 / 1反向查询 / 2服务器状态请求
     * AA : 1 bit               表示授权回答
     * TC : 1 bit               表示可以截断
     * RD : 1 bit               表示期望递归查询
     * RA : 1 bit               表示可用递归查询
     * Z : 3 bits               保留
     * Rcode : 4 bit            返回码：0没有差错 / 2服务器错误 / 3名字差错
     */ 
    unsigned short flags;           // 标志
    unsigned short quesNumber;      // Questions
    unsigned short ansNumber;       // Answer RRs
    unsigned short authNumber;      // Authority RRs
    unsigned short addNumber;       // Additional RRs

} dnsHeader;


#pragma pack(push, 1)
typedef struct DNSRR
{
    unsigned short type;
    unsigned short classes;
    unsigned int ttl;
    unsigned short data_length;
} dnsRR;
#pragma pack(pop)

typedef struct DNSQUERY
{
    /**
     * main type:
     * A(1) : IPv4
     * AAAA(28) : IPv6
     */
    unsigned short type;

    /**
     * IN(1) : Internet
     */
    unsigned short classes;
} dnsQuery;

/**
 * 将域名以二进制数据转换为字符串形式（带.）
 */
void to_domain_name(char *buf)
{
    char *p = buf;
    while (*p != 0) {
        if (*p >= '!')
            p++;
        else {
            *p = '.';
            p++;
        }
    }
    printf("%s\n", buf);
}

/**
 * 查询 IP - 域名 对照表
 * 输入域名与存放ip地址的内存的指针
 * 并将ip地址转换为字节形式
 * 查找成功返回1，查找失败返回0
 */
int lookup_int_text(char *dn, char *ip)
{
    int flag = 0;
    FILE *fp;
    char ipAddr[BUFFER_SIZE];
    char domainName[BUFFER_SIZE];
    if ((fp = fopen("dnsrelay.txt", "r")) == NULL) {
        printf("file open error\n");
        exit(1);
    }
    while (!feof(fp)) {
        fgets(ipAddr, 1024, fp);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (ipAddr[i] == ' ') {
                ipAddr[i] = '\0';
                break;
            }
        }
        strcpy(domainName, ipAddr + strlen(ipAddr) + 1);
        if (domainName[strlen(domainName) - 1] == '\n')
            domainName[strlen(domainName) - 1] = '\0';
        else
            domainName[strlen(domainName)] = '\0';
        

        //printf("111:%s!\n", domainName);
        //printf("222:%s!\n", dn);
        //printf("333:%d\n", strcmp(dn, domainName));
        // 找到了域名，得到ip地址

        if (strcmp(dn, domainName) == 0) {

            // 得到ip地址
            char *h = ipAddr;
            char *p = ipAddr;
            int i = 0;
            //printf("%s\n", ipAddr);
            while (*p != '\0') {
                if (*p == '.') {
                    *p = '\0';
                    ip[i] = (char)atoi(h);
                    i++;
                    h = p + 1;
                }
                p++;
            }
            ip[i] = atoi(h);
            flag = 1;
            return flag;
        }
    }
    return flag;
}

/**
 * 构造响应报文
 */
void creat_msg_manully(char *buf, char *ip)
{
    dnsHeader *header = (dnsHeader *)buf;
    dnsRR *rr;
    if (*ip == (char)0 && *(ip + 1) == (char)0 && *(ip + 2) == (char)0 && *(ip + 3) == (char)0)
        header->flags = htons(0x8183);
    else
        header->flags = htons(0x8180);
    header->ansNumber = htons(1);
    char *dn = buf + sizeof(dnsHeader);
    //printf("%lu\n", strlen(dn));
    //dnsQuery *query = (dnsQuery *)(dn + strlen(dn) + 1);
    //query->type = htons((unsigned short)1);
    //query->classes = htons((unsigned short)1);
    char *name = dn + strlen(dn) + 1 + sizeof(dnsQuery);
    unsigned short *_name = (unsigned short *)name;
    *_name = htons((unsigned short)0xC00C);
    rr = (dnsRR *)(name + 2);
    rr->type = htons(1);
    rr->classes = htons(1);
    rr->ttl = htons(0xFFF);
    rr->data_length = htons(4);
    char *data = (char *)rr + 10;
    *data = *ip;
    *(data + 1) = *(ip + 1);
    *(data + 2) = *(ip + 2);
    *(data + 3) = *(ip + 3);
}

void dns_relay() {

    /**
     * 00.初始化参数
     */
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int MySocket, bindStatus, resvStatus;
    char buf[BUFFER_SIZE];

    /**
     * 01.配置本地服务器地址
     */
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_aton(LOCAL_HOST, &serverAddress.sin_addr);

    /**
     * 02.配置客户端地址
     */
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(PORT);
    inet_aton(LOCAL_HOST, &clientAddress.sin_addr);

    /**
     * 03.创建MySocket
     */
    MySocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (MySocket < 0) {
        perror("MySocket error\n");
        exit(1);
    }

    /**
     * 04.将MySocket绑定到本地服务器
     */
    bindStatus = bind(MySocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (bindStatus < 0) {
        perror("bind error\n");
        exit(1);
    }

    /**
     * 05.事实生成调试信息（需完善）
     */

    /**
     * 06.启动域名服务器
     */
    unsigned int len = sizeof(clientAddress);
    while (TRUE) {
        /**
         * 01.从客户端接收数据
         */
        memset(buf, 0, BUFFER_SIZE);
        resvStatus = recvfrom(MySocket, buf, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, &len);
        if (resvStatus < 0) {
            perror("recvfrom error\n");
            exit(1);
        }

        /**
         * 02.解析数据，获取查询域名
         */
        // 建立Buffer
        char *temp = (char *)malloc(BUFFER_SIZE);
        // 建立IP
        char *ip = (char *)malloc(IPSIZE);
        // 通过strcpy，拷贝出要查询的域名
        strcpy(temp, buf + sizeof(dnsHeader) + 1);
        to_domain_name(temp);
        // 在本地的IP-域名对照表中查询
        int find_in_map = lookup_int_text(temp, ip);
        // 返回查询结果
        printf("find: %d\n", find_in_map);
        // 释放内存
        free(temp);
        // 输出查询结果
        printf("%u.%u.%u.%u\n", *ip & 0x000000ff, *(ip + 1) & 0x000000ff, *(ip + 2) & 0x000000ff, *(ip + 3) & 0x000000ff);

        /**
         * 03.在本地的域名-IP对照表中查询
         *      1、若在表中找到，则构造响应报文返回
         *      2、若未找到，则向远程域名服务器发送查询请求，并回送响应数据
         */
        if (find_in_map) {
            creat_msg_manully(buf, ip);
            free(ip);
        } else {

            /**
             * 01.配置远程DNS域名服务器的地址
             */
            struct sockaddr_in DnsSrvAddr;
            int inquireSocket = socket(AF_INET, SOCK_DGRAM, 0);
            if (inquireSocket < 0) {
                perror("socket error\n");
                exit(1);
            }
            bzero(&DnsSrvAddr, sizeof(DnsSrvAddr));   
            DnsSrvAddr.sin_family = AF_INET;       
            inet_aton(SRV_IPADDR, &DnsSrvAddr.sin_addr); 
            DnsSrvAddr.sin_port = htons(PORT);  

            /**
             * 02.向DNS服务器发送查询请求，并接收响应
             */
            unsigned int i = sizeof(DnsSrvAddr);
            len = sendto(inquireSocket, buf, BUFFER_SIZE, 0, (struct sockaddr*)&DnsSrvAddr, sizeof(DnsSrvAddr));
            len = recvfrom(inquireSocket, buf, BUFFER_SIZE, 0, (struct sockaddr*)&DnsSrvAddr, &i);
            if (len < 0) {
                printf("recv error\n");
                exit(1);
            }
            close(inquireSocket);
        }
        /**
         * 04.返回响应信息
         */
        bindStatus = sendto(MySocket, buf, sizeof(buf), 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
        if (bindStatus < 0) {
            perror("sendto error\n");
            exit(1);
        }  
        
    }
    
}


int main()
{   
    // 开启DNS中继服务器
    dns_relay();
}
