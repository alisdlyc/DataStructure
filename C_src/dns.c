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
    unsigned short transactionID;   // �Ự��ʶ
    /**
     * flags(2 Bytes):cd
     * QR : 1 bit               0��ѯ / 1��Ӧ
     * Opcode : 4 bit           0��׼��ѯ / 1�����ѯ / 2������״̬����
     * AA : 1 bit               ��ʾ��Ȩ�ش�
     * TC : 1 bit               ��ʾ���Խض�
     * RD : 1 bit               ��ʾ�����ݹ��ѯ
     * RA : 1 bit               ��ʾ���õݹ��ѯ
     * Z : 3 bits               ����
     * Rcode : 4 bit            �����룺0û�в�� / 2���������� / 3���ֲ��
     */ 
    unsigned short flags;           // ��־
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
 * �������Զ���������ת��Ϊ�ַ�����ʽ����.��
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
 * ��ѯ IP - ���� ���ձ�
 * ������������ip��ַ���ڴ��ָ��
 * ����ip��ַת��Ϊ�ֽ���ʽ
 * ���ҳɹ�����1������ʧ�ܷ���0
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
        // �ҵ����������õ�ip��ַ

        if (strcmp(dn, domainName) == 0) {

            // �õ�ip��ַ
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
 * ������Ӧ����
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
     * 00.��ʼ������
     */
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int MySocket, bindStatus, resvStatus;
    char buf[BUFFER_SIZE];

    /**
     * 01.���ñ��ط�������ַ
     */
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_aton(LOCAL_HOST, &serverAddress.sin_addr);

    /**
     * 02.���ÿͻ��˵�ַ
     */
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(PORT);
    inet_aton(LOCAL_HOST, &clientAddress.sin_addr);

    /**
     * 03.����MySocket
     */
    MySocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (MySocket < 0) {
        perror("MySocket error\n");
        exit(1);
    }

    /**
     * 04.��MySocket�󶨵����ط�����
     */
    bindStatus = bind(MySocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (bindStatus < 0) {
        perror("bind error\n");
        exit(1);
    }

    /**
     * 05.��ʵ���ɵ�����Ϣ�������ƣ�
     */

    /**
     * 06.��������������
     */
    unsigned int len = sizeof(clientAddress);
    while (TRUE) {
        /**
         * 01.�ӿͻ��˽�������
         */
        memset(buf, 0, BUFFER_SIZE);
        resvStatus = recvfrom(MySocket, buf, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, &len);
        if (resvStatus < 0) {
            perror("recvfrom error\n");
            exit(1);
        }

        /**
         * 02.�������ݣ���ȡ��ѯ����
         */
        // ����Buffer
        char *temp = (char *)malloc(BUFFER_SIZE);
        // ����IP
        char *ip = (char *)malloc(IPSIZE);
        // ͨ��strcpy��������Ҫ��ѯ������
        strcpy(temp, buf + sizeof(dnsHeader) + 1);
        to_domain_name(temp);
        // �ڱ��ص�IP-�������ձ��в�ѯ
        int find_in_map = lookup_int_text(temp, ip);
        // ���ز�ѯ���
        printf("find: %d\n", find_in_map);
        // �ͷ��ڴ�
        free(temp);
        // �����ѯ���
        printf("%u.%u.%u.%u\n", *ip & 0x000000ff, *(ip + 1) & 0x000000ff, *(ip + 2) & 0x000000ff, *(ip + 3) & 0x000000ff);

        /**
         * 03.�ڱ��ص�����-IP���ձ��в�ѯ
         *      1�����ڱ����ҵ���������Ӧ���ķ���
         *      2����δ�ҵ�������Զ���������������Ͳ�ѯ���󣬲�������Ӧ����
         */
        if (find_in_map) {
            creat_msg_manully(buf, ip);
            free(ip);
        } else {

            /**
             * 01.����Զ��DNS�����������ĵ�ַ
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
             * 02.��DNS���������Ͳ�ѯ���󣬲�������Ӧ
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
         * 04.������Ӧ��Ϣ
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
    // ����DNS�м̷�����
    dns_relay();
}
