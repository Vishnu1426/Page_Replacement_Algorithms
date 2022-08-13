#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n, fs;

int check(int frame[fs], int fs)
    {
        int cnt = 0;
        for(int i = 0; i < fs; i++)
            {
                if(frame[i] != -1)
                    {
                        cnt+= 1;
                    }
            }
        return cnt;
    }

int print(int frame[fs])
    {
        printf("\nFrame: ");
        for(int i = 0 ; i < fs; i++)
            {
                if(frame[i] != -1)
                    {
                        printf(" P%d", frame[i]);
                    }
                else
                    {
                        printf(" %d", frame[i]);
                    }
            }
        return 0;
    }

int FIFO(int p_id[n], int fs)
    {
        int frame[fs], pf = 0, order[fs], page_hit = 0, used;

        for(int i = 0; i < fs; i++)
            {
                frame[i] = -1;
                order[i] = 0;
            }

        for(int i = 0; i < n; i++)
            {
                printf("\n-----------------------------------------------------------------");
                printf("\n\nRequested Process: P%d", p_id[i]);
                if((used = check(frame, fs)) < fs)
                    {
                        for(int j = 0; j < fs; j++)
                            {
                                if(frame[j] == p_id[i])
                                    {
                                        page_hit = 1;
                                        print(frame);
                                        printf("\nPage Hit");
                                        break;
                                    }
                                else
                                    {
                                        page_hit = 0;
                                    }
                            }
                        if(page_hit != 1 && i != 0)
                            {
                                pf = pf + 1;
                                print(frame);
                                frame[used] = p_id[i];
                                order[used] = order[used-1] + 1;
                                printf("\nPage Fault!\nAfter Page replacement: ");
                                print(frame);
                            }
                        else if(page_hit != 1)
                            {
                                pf = pf + 1;
                                print(frame);
                                frame[i] = p_id[i];
                                order[i] = 1;
                                printf("\nPage Fault!\nAfter Page Replacement: ");
                                print(frame);
                            }
                    }
                else
                    {
                        for(int j = 0; j < fs; j++)
                            {
                                if(frame[j] == p_id[i])
                                    {
                                        page_hit = 1;
                                        print(frame);
                                        printf("\nPage Hit");
                                        break;
                                    }
                                else
                                    {
                                        page_hit = 0;
                                    }
                            }
                        if(page_hit != 1)
                            {
                                for(int j = 0; j < fs; j++)
                                    {
                                        if(order[j] != 1)
                                            {
                                                order[j] = order[j] - 1;
                                            }
                                        else
                                            {
                                                pf = pf + 1;
                                                print(frame);
                                                frame[j] = p_id[i];
                                                order[j] = fs;
                                                printf("\nPage Fault!\nAfter Page Replacement:");
                                                print(frame);                                               
                                            }
                                    }
                            }   
                    }
            }

        printf("\n-----------------------------------------------------------------");
        printf("\n\nTotal Page Faults: %d", pf);
        printf("\nTotal Page Hits: %d\n", n - pf);
        printf("\n-----------------------------------------------------------------\n");
        return 0;
    }

int LRU(int p_id[n], int fs)
    {
        int frame[fs],pf = 0, order[fs], page_hit = -1, page_hit_pos, used;
        for(int i = 0; i < fs; i++)
            {
                frame[i] = -1;
                order[i] = 0;
            }

        for(int i = 0; i < n; i++)
            {
                printf("\n\n-----------------------------------------------------------------");
                printf("\nRequested Process: P%d", p_id[i]);
                if((used = check(frame, fs)) < fs)
                    {
                        for(int j = 0; j < fs; j++)
                            {
                                if(frame[j] == p_id[i])
                                    {
                                        page_hit = j;
                                        print(frame);
                                        printf("\nPage Hit");
                                        break;
                                    }
                                else
                                    {
                                        page_hit = -1;
                                    }
                            }
                        if(page_hit == -1 && i != 0)
                            {
                                pf = pf + 1;
                                print(frame);
                                frame[used] = p_id[i];
                                order[used] = order[used-1] + 1;
                                printf("\nPage Fault!\nAfter Page replacement: ");
                                print(frame);
                            }
                        else if(page_hit == -1)
                            {
                                pf = pf + 1;
                                print(frame);
                                frame[i] = p_id[i];
                                order[i] = 1;
                                printf("\nPage Fault!\nAfter Page replacement: ");
                                print(frame);
                            }
                    }
                else
                    {
                        for(int j = 0; j < fs; j++)
                            {
                                if(frame[j] == p_id[i])
                                    {
                                        page_hit = j;
                                        print(frame);
                                        printf("\nPage Hit");
                                        break;
                                    }
                                else
                                    {
                                        page_hit = -1;
                                    }
                            }
                        if(page_hit == -1)
                            {
                                for(int j = 0; j < fs; j++)
                                    {
                                        if(order[j] != 1)
                                            {
                                                order[j] = order[j] - 1;
                                            }
                                        else
                                            {
                                                pf = pf + 1;
                                                print(frame);
                                                frame[j] = p_id[i];
                                                order[j] = fs;
                                                printf("\nPage Fault!\nAfter Page replacement: ");
                                                print(frame);                             
                                            }
                                    }
                            }
                        else
                            {
                                for(int j = 0; j < fs; j++)
                                    {
                                        if(j != page_hit && order[j] > order[page_hit])
                                            {
                                                order[j] = order[j] - 1;
                                            }
                                    }
                                order[page_hit] = fs;            
                            }
                    }
            }

        printf("\n-----------------------------------------------------------------");
        printf("\n\nTotal Page Faults: %d", pf);
        printf("\nTotal Page Hits: %d\n", n - pf);
        printf("\n-----------------------------------------------------------------\n");
        return 0;
    }


int main()
    {
        printf("\n-----------------------------------------------------------------\n");
        printf("\tPage Replacement ALgorithms Simulation");
        printf("\n-----------------------------------------------------------------");
        printf("\nEnter the number of processes: ");
        scanf("%d", &n);
        
        int p_id[n];
        int ch;
        
        printf("Enter the Frame Size:");
        scanf("%d", &fs);
        
        for(int i = 0; i < n; i++)
            {
                printf("\nProcess ID: ");
                scanf("%d", &p_id[i]);
            }
        while(1)
            {
                printf("\nChoose the Page Replacement Algorithm:\n");
                printf("1. First In First Out\n2. Least Recently Used\n3. Exit\n");
                printf("Choice: ");
                scanf("%d", &ch);
                if(ch == 1)
                    {
                        FIFO(p_id, fs);
                    }
                else if(ch == 2)
                    {
                        LRU(p_id, fs);
                    }
                else if(ch == 3)
                    {
                        exit(1);
                    }
                else
                    {
                        printf("Invalid Choice!!");
                    }
            }

        return 0;
    }