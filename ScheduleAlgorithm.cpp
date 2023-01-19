#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
void fcfs(vector<int> p,int n);
void sjf(vector<int> p,int n);
void srtf(vector<int> p, vector<int> ar,int n);
void roundRobin(vector<int> bt,int n);
void priorityNp(vector<int> p,vector<int> pr,int n);
void priorityP(vector<int> p,vector<int> ar,vector<int> pr,int n);
int getIndex(int value, vector<int> in);
void availableProcess(vector<int> &ar,vector<int> &p,vector<int> &ap,int a);
vector<int> cp;
vector<string> cname;
int main()
{
    int n,a,choice,n2,m;
    vector<int> inBt,inAt,inPr,Bt,At,Pr;
    int index;
    cout<<"Enter number of process: ";
    cin>>n;
    cout<<"Enter BT  AT Priority: "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"p["<<i+1<<"]: ";
        cin>>a;
        inBt.push_back(a);
        cin>>a;
        inAt.push_back(a);
        cin>>a;
        inPr.push_back(a);

    }
    while(1)
    {
        cout<<"\n\n------------Menu------------\n1.First Come, First Served (FCFS)\n2.Shortest Job First (SJF)\n3.Round Robin\n4.Priority Scheduling\n5.Compare\n6.exit\nEnter a choice: ";
        cin>>choice;
        int n1=0;
        switch(choice)
        {
        case 1:
            fcfs(inBt,n);
            break;
        case 2:
            cout<<"--Shortest Job First (SJF)--\n1.Preemptive\n2.Non Preemptive\nEnter your choice: ";
            int n1;
            cin>>n1;
            switch(n1)
            {
            case 1:
                Bt=inBt;
                At=inAt;
                srtf(Bt,At,n);
                break;
            case 2:
                sjf(inBt,n);
                break;
            }
            break;
        case 3:
            Bt=inBt;
            roundRobin(Bt,n);
            break;
        case 4:
            cout<<"--Priority Scheduling--\n1.Preemptive\n2.Non Preemptive\nEnter your choice: ";
            cin>>n1;
            switch(n1)
            {
            case 1:
                Bt=inBt;
                At=inAt;
                Pr=inPr;
                priorityP(Bt,At,Pr,n);
                break;
            case 2:
                Bt=inBt;
                Pr=inPr;
                priorityNp(Bt,Pr,n);
                break;
            }
            break;
        case 5:
            cout<<"Algorithm Name                 Waiting Time"<<endl;
            cout<<endl;
            for(int i=0;i<cp.size();i++)
            {
                cout<<cname[i]<<"                  "<<cp[i]<<endl;
            }
            m=*min_element(cp.begin(), cp.end());
            index=getIndex(m,cp);
            cout<<"Best Algorithm is "<<cname[index]<<endl;

                break;
        case 6: exit(0);
            break;
        }
    }
}
void fcfs(vector<int> p,int n)
{
    int c=0,l=0,a;
    float avg=0;
    vector<int> wt;

    for(int i=0;i<n;i++)
    {
        wt.push_back(-1);
        l=l+p[i];
    }
    cout<<"------First Come, First Served (FCFS)------"<<endl;
    cout<<"\nGantt chart: "<<endl;
    for(int i=0;i<l+n;i++)
        cout<<"--";
        cout<<endl;
    for(int i=0;i<n;i++)
    {
        wt[i]=c;
        cout<<"|";
        for(int j=0;j<p[i];j++)
        {
            c++;
            cout<<i+1<<"-";
        }
    }
    cout<<"|"<<endl;
    c=0;
    for(int i=0;i<n;i++)
    {
        cout<<c;
        for(int j=0;j<p[i];j++)
        {
            c++;
            if(j!=0||c>9)
            cout<<"--";
        }
    }
    cout<<c<<endl;
    cout<<"\nProcess        Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        cout<<i+1<<"                "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("FCFS");
    cout<<"\nAverage Waiting Time: "<<avg/n;

}

void sjf(vector<int> p,int n)
{
    int tBt=0,m,c=0;
    float avg=0;
    vector<int> p1,wt,rec;
    p1=p;
    for(int i=0;i<n;i++)
    {
        wt.push_back(-1);
        tBt=tBt+p[i];
    }
    cout<<"------Shortest Job First (SJF)------"<<endl;
    cout<<"\nGantt Chart:"<<endl;
    for(int i=0;i<tBt+n;i++)
        cout<<"--";
        cout<<"\n|";
    for(int i=0;i<tBt;i++)
    {
        m=*min_element(p.begin(), p.end());
        auto index=getIndex(m,p);
        p[index]--;
        cout<<"-"<<index+1;
        if(p[index]==0)
        {
            wt[index]=(i+1-p1[index]);
            cout<<"|";
            p[index]=INT_MAX;
        }

    }
    rec=wt;
    sort(rec.begin(),rec.end());
    cout<<"\n";
    for(int i=0;i<tBt;i++)
    {
        if(count(rec.begin(),rec.end(),i))
            cout<<i;
        cout<<"--";
    }
    cout<<tBt<<endl;
    cout<<"\nProcess       Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        cout<<"p"<<i+1<<"               "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("SJF Non Preemptive");
    cout<<"\nAverage Waiting Time: "<<avg/n;
}
int getIndex(int value, vector<int> in)
{
    for(int i=0;i<in.size();i++)
    {
        if(in[i]==value)
            return i;
    }
}
void srtf(vector<int> p, vector<int> ar,int n)
{
    int tBt=0,m;
    float avg=0;
    vector<int> ap,p1,wt;
    p1=p;
    for(int i=0;i<n;i++)
    {
        wt.push_back(-1);
        tBt=tBt+p[i];
    }

    int m_ar=*min_element(ar.begin(), ar.end());
    cout<<"------Shortest Remaining Time First (SRTF)------"<<endl;
    cout<<"\nGantt Chart: "<<endl;
    for(int i=0;i<tBt+m_ar;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==ar[j])
            {
                cout<<"|";
                ap.push_back(p[j]);
            }
        }
            if(ap.size()>=1)
            {
                m=*min_element(ap.begin(), ap.end());
                auto index=getIndex(m,ap);
                int value=ap[index];
                value--;
                ap[index]=value;
                auto in=getIndex(m,p);
                cout<<in+1;
                p[in]=value;
               // cout<<index<<endl;
                if(ap[index]==0)
                {
                    wt[in]=(i+1-ar[in]-p1[in]);
                    cout<<"|";
                    ap[index]=INT_MAX;
                }
            }
            cout<<"-";

    }
    cout<<endl;
    cout<<"\nProcess       Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        cout<<"p"<<i+1<<"               "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("SJF Preemptive");
    cout<<"\nAverage Waiting Time: "<<avg/n;
}
void availableProcess(vector<int> &ar,vector<int> &p,vector<int> &ap,int a)
{
    for(int i=0;i<p.size();i++)
    {
        if(ar[i]==a)
        {
            ap.push_back(p[i]);
        }

    }
}

void roundRobin(vector<int> bt,int n)
{
    int q,a;
    float avg=0;
    vector<int> p,bt1,wt;
    bt1=bt;
    cout<<"Enter time quantum: ";
    cin>>q;
    for(int i=0;i<n;i++)
    {
        p.push_back(-1);
        wt.push_back(-1);
    }
    int j=0,pe,time=0;
    cout<<"------Round-robin (RR)------"<<endl;
    cout<<"\nGantt Chart: "<<endl;
    while(1)
    {
        int sum=0;
        if(p[j]==0)
        {
            j=(j+1)%n;
            continue;
        }
        else if(bt[j]>q)
        {
            cout<<"|";
            for(int i=0;i<q;i++)
                cout<<j+1<<"-";
            bt[j]=bt[j]-q;
            time=time+q;
        }
        else
        {
            cout<<"|";
            for(int i=0;i<bt[j];i++)
                cout<<j+1<<"-";
            if(bt[j]<q)
                wt[j]=time;
            else
            {
                pe=floor(bt1[j]/q);
                wt[j]=time-((pe*q)-q);
            }
            p[j]=0;
            time=time+bt[j];
        }
        j=(j+1)%n;
        for(int i=0;i<n;i++)
            sum=sum+p[i];
        if(sum==0)
            break;
    }
    cout<<"|"<<endl;
    cout<<"\nProcess    Burst time   Waiting time\n";
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        printf("%d",i+1);
        cout<<i+1<<"            "<<bt1[i]<<"           "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("Round Robin");
    cout<<"\nAverage Waiting Time: "<<avg/n;
}
void priorityNp(vector<int> p,vector<int> pr,int n)
{
    int tBt=0,m;
    float avg=0;
    vector<int> p1,wt;
    p1=p;
    for(int i=0;i<n;i++)
    {
        tBt=tBt+p[i];
        wt.push_back(-1);
    }
    cout<<"------Non Preemptive Priority Scheduling------"<<endl;
    cout<<"\nGantt Chart: \n|";

    for(int i=0;i<tBt;i++)
    {
        m=*min_element(pr.begin(), pr.end());
        auto index=getIndex(m,pr);
        p[index]--;
        cout<<"-"<<index+1;
        if(p[index]==0)
        {
            wt[index]=(i+1-p1[index]);
            cout<<"|";
            pr[index]=INT_MAX;
        }

    }
    cout<<endl;
    cout<<"\nProcess       Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        cout<<"p"<<i+1<<"               "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("Priority Non Preemptive");
    cout<<"\nAverage Waiting Time: "<<avg/n;
}

void priorityP(vector<int> p,vector<int> ar,vector<int> pr,int n)
{
    int tBt=0,m;
    float avg=0;
    vector<int> wt,ap,p1;
    p1=p;
    for(int i=0;i<n;i++)
    {
        wt.push_back(-1);
        tBt=tBt+p[i];
    }

    int m_ar=*min_element(ar.begin(), ar.end());
    cout<<"------Preemptive Priority Scheduling------"<<endl;
    cout<<"\nGantt Chart: "<<endl;
    for(int i=0;i<tBt+m_ar;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==ar[j])
            {
                cout<<"|";
                ap.push_back(pr[j]);
            }
        }
            if(ap.size()>=1)
            {
                m=*min_element(ap.begin(), ap.end());
                auto in=getIndex(m,pr);
                auto index=getIndex(m,ap);
                cout<<in+1;
                int value=p[in];
                value--;
                p[in]=value;
                if(p[in]==0)
                {
                    wt[in]=(i+1-ar[in]-p1[in]);
                    cout<<"|";
                    ap[index]=INT_MAX;
                }
            }
            cout<<"-";

    }
    cout<<endl;
    cout<<"\nProcess       Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        avg=avg+wt[i];
        cout<<"p"<<i+1<<"               "<<wt[i]<<endl;
    }
    cp.push_back(avg/n);
    cname.push_back("Priority Preemptive");
    cout<<"\nAverage Waiting Time: "<<avg/n;
}
