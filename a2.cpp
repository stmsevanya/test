#include<bits/stdc++.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>

using namespace std;


int main()
{
    string program;
    char* iofilename;
    int i,fd,c, P[20],count,end;
    char* args[10];
    char command = ' ';
    while(command!='G' || command!='g')
    {
        puts("Enter command option from menu");
        puts("A.      Run an internal command");
        puts("B.      Run an external command");
        puts("C.      Run an external command by redirecting standard input from a file");
        puts("D.      Run an external command by redirecting standard output to a file");
        puts("E.      Run an external command in the background");
        puts("F.      Run several external commands in the pipe mode");
        puts("G.      Quit the shell");

        command = getchar();
        getchar();
        puts("Enter command( and its arguments if applicable)");
        getline(cin,program);

        c=0;
        i=0;
        if(command=='A' || command=='a' || command=='B' || command=='b' || command=='E' || command=='e')
        {

            while(program[i]!='\n' && program[i]!='\0')
            {
                while(program[i]==' ')program[i++]='\0';
                if(program[i]=='\n' && program[i]=='\0')break;
                args[c++]=&program[i];
                while(program[i]!=' ' && program[i]!='\n' && program[i]!='\0')i++;
            }
            args[c]=(char*)NULL;

            if(!fork())
            {
                execvp(args[0],args);
            }
            if(command!='E' && command!='e')wait(NULL);
        }
        else if(command=='C' || command=='c' || command=='D' || command=='d')
        {

            while(program[i]!='<' && program[i]!='>')
            {
                while(program[i]==' ')program[i++]='\0';
                if(program[i]=='<' || program[i]=='>')break;
                args[c++]=&program[i];
                while(program[i]!=' ' && program[i]!='<' && program[i]!='>')i++;
            }
            program[i++]='\0';
            while (program[i]==' ')i++;
            iofilename = &program[i];
            args[c]=(char*)NULL;

            if((command=='C' || command=='c') && !fork())
            {
                fd = open(iofilename,ios::in);
                if(fd<0)cout<<"can't open input file"<<endl;
                dup2(fd,STDIN_FILENO);
                //close(fd);
                execvp(args[0],args);
            }

            else if((command=='D' || command=='d') && !fork())
            {
                fd = open(iofilename,O_WRONLY | O_APPEND);
                if(fd<0)cout<<"can't open output file"<<endl;
                dup2(fd,STDOUT_FILENO);
                dup2(fd,STDERR_FILENO);
                //close(fd);
                execvp(args[0],args);
            }
            wait(NULL);
        }
        else if(command=='F' || command=='f')
        {
            for(count=0,i=0,end=0;end==0;count++)
            {
                c=0;
                while(program[i]!='|' && program[i]!='\n' && program[i]!='\0')
                {
                    while(program[i]==' ')program[i++]='\0';
                    if(program[i]=='|' && program[i]=='\n' && program[i]=='\0')break;
                    args[c++]=&program[i];
                    while(program[i]!=' ' && program[i]!='|' && program[i]!='\n' && program[i]!='\0')i++;
                }
                args[c]=(char*)NULL;
                if(program[i]=='\n' || program[i]=='\0')end=1;
                program[i++]='\0';
                while(program[i]==' ')i++;
                cout<<program[0]<<endl;

                if(!end)pipe(&P[2*count]);

                if(!fork())
                {
                    if(count)dup2(P[2*count-2],0);
                    if(!end)dup2(P[2*count+1],1);
                    if(!end)dup2(P[2*count+1],2);
                    execvp(args[0],args);
                }
                //if(!end)close(P[2*count+1]);
                //if(count)close(P[2*count-2]);
                wait(NULL);
            }

        }

        cout<<"command executed"<<endl<<endl;
    }

    return 0;

}
