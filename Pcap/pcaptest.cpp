#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
 
void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
    int * id = (int *)arg;

    printf("id: %d\n", ++(*id));
    printf("Packet length: %d\n", pkthdr->len);
    printf("Number of bytes: %d\n", pkthdr->caplen);
    printf("Recieved time: %s", ctime((const time_t *)&pkthdr->ts.tv_sec)); 

    int i;
    for(i=0; i<pkthdr->len; ++i)
    {
        printf(" %02x", packet[i]);
        if( (i + 1) % 16 == 0 )
        {
            printf("\n");
        }
    }
    printf("\n\n");
}

 int main()
 {
     char errBuf[PCAP_ERRBUF_SIZE],*selectDevName;
     pcap_if_t *allDev,*selectDev;
     int iNum,i;

    /*
     * @brief 获取网络设备名称
     */
    if(pcap_findalldevs(&allDev,errBuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errBuf);
        exit(1);
    }
    for(selectDev=allDev; selectDev; selectDev=selectDev->next)
    {
        printf("%d. %s", ++i, selectDev->name);
        if (selectDev->description)
            printf(" (%s)\n", selectDev->description);
        else
            printf(" (No description available)\n");
    }

    printf(" (please input number for select devices)\n");
    scanf("%d", &iNum);
    for(selectDev=allDev, i=0; i< iNum-1 ;selectDev=selectDev->next, i++);

    selectDevName = selectDev->name;
    if(selectDevName)
    {
        printf("success: device: %s\n", selectDevName);
    }
    else
    {
        printf("error: %s\n", errBuf);
        exit(1);
    }

    /* open a device, wait until a packet arrives */
    pcap_t * device = pcap_open_live(selectDevName, 65535, 1, 0, errBuf);
    if(!device)
    {
        printf("error: pcap_open_live(): %s\n", errBuf);
        exit(1);
    }
    /* construct a filter */
    struct bpf_program filter;
    int filterState = pcap_compile(device, &filter, "dst port 80 and src host 192.168.1.159 and dst host 192.168.1.159 and src port 8080", 1, 0); //与或非用and or not
    printf("filterState: %d\n\n",filterState); //0--成功，-1--失败
    pcap_setfilter(device, &filter);

    /* wait loop forever */
    int id = 0;
    pcap_loop(device, -1, getPacket, (u_char*)&id);

    pcap_close(device);

    return 0;
 }
