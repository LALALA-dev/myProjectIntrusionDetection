#include "internet.h"
extern int flag,intrusion_flag;

void server::setupConnection(){
     //create socket
     int listening = socket(AF_INET,SOCK_STREAM,0);
     if(listening == 0){
        std::cerr << "Create socket error\n";
        return;
     }

     //bind socket to ip and port
     sockaddr_in hint;
     hint.sin_family = AF_INET; // ipv4 family
     hint.sin_port = htons(portNum); //host to network short
     inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr); //internet command convert a number to an array of integers; 0.0.0.0 means any address

     if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == 1){
        std::cerr << "Cannot bind to IP/Port\n";
        return;
     }

     //mark the socket for listening
    if(listen(listening,SOMAXCONN) == -1){ // SOMAXCONN means maximum connection, typically 128
        std::cerr << "Cannot listen\n";
    }

     //accept a call
     sockaddr_in client;
     socklen_t clientSize = sizeof(client);
     char host[NI_MAXHOST];
     char svc[NI_MAXSERV];

     int clientSocket = accept(listening,(sockaddr*)&client, &clientSize);
     if(clientSocket == -1){
        std::cerr<<"Problem with client connection\n";
        return;
     }
     //close the listening socket
     close(listening);

     memset(host,0,NI_MAXHOST);
     memset(svc,0,NI_MAXSERV);

     int result = getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
     if(result){
        std::cout << "Connected on "<< svc <<std::endl;
     }else{
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        std::cout << "Host on "<<ntohs(client.sin_port)<<std::endl;
     }
     //while receiving, display message and do something
     char buf[4096];
     std::thread t1{serverListening,clientSocket};
     while(true){
        //clear buff
        memset(buf,0,4096);
        if(flag == 1){
         break;
        }
        if(intrusion_flag == 1){
         std::string detected = "Something detected\n";
         strcpy(buf,detected.c_str());
         send(clientSocket,buf,strlen(buf)+1,0);
         intrusion_flag = 0;
        }
     }
     t1.join();
     //close socket
     close(clientSocket);
     return;
}

void server::serverListening(int clientSocket){
   char buf[4096];
   while(true){
      memset(buf,0,4096);
      int byteRecv= recv(clientSocket,buf,4096,0);
            if(byteRecv == 1){
                  std::cerr <<"Connection issue\n";
            }else if(byteRecv == 0){
                  std::cout << "The client disconnected\n";
                  break;
            }
            std::cout << "Received: "<<std::string(buf,0,byteRecv)<<std::endl;
            
            if(*buf == 'quit' || *buf == 'q'){
               flag = 1;
               std::string temp = "Remote close camera\n";
               strcpy(buf,temp.c_str());
               byteRecv = strlen(buf);
            }
            send(clientSocket,buf,byteRecv+1,0);
   }
   
}