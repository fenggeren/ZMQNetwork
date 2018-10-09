//
//  ZMQGateWay.hpp
//  ZMQNode
//
//  Created by huanao on 2018/9/28.
//  Copyright © 2018年 huanao. All rights reserved.
//

#pragma once
#include <czmq.h>
#include <string>
#include "ZMQReactor.hpp"
#include "ZMQNetworkDefine.h"
#include <map>

namespace ZGW
{
    
class ZMQGateWay
{
public:
    
    ZMQGateWay()
    {
        pub_ = zsock_new(ZMQ_PUB);
        pull_ = zsock_new(ZMQ_PULL);
        loginDealer_ = zsock_new(ZMQ_DEALER);
        matchManagerDealer_ = zsock_new(ZMQ_DEALER);
        
        zsock_set_sndhwm(pull_, 0);
        zsock_set_rcvhwm(pull_, 0);
        zsock_set_rcvtimeo(pull_, 500);
        zsock_set_sndtimeo(pull_, 500);
    }
    
    void start()
    {
        zsock_set_identity(loginDealer_, "GW");
        zsock_bind(pub_, "tcp://*:%d", GATEWAY_PUB_PORT);
        zsock_bind(pull_, "tcp://*:%d", GATEWAY_PULL_PORT);
        zsock_bind(loginDealer_, "tcp://*:%d", GATEWAY_LOGIN_DEALER_PORT);
        zsock_bind(matchManagerDealer_, "tcp://*:%d", GATEWAY_MATCHMANAGER_DEALER_PORT);
 
        reactor_.addSocket(pull_, [&](zsock_t* sock){
            zmsg_t* msg = zmsg_recv(sock);
            zmsg_destroy(&msg);
            rcvCount_++;
        });
        reactor_.addTimer(5000, INTMAX_MAX, [&]{
            printf("%llu --  %llu\n", sendCount_, rcvCount_);
        });
        reactor_.asyncLoop();
        test();
    }
    
    void test()
    {
        std::thread thread1([&]{
            while (true) {
            sendCount_++;
            sendLoginRQ(123, "PING PONG");
            }
        });
        std::thread thread2([&]{
             while (true) {
                sendCount_++;
                sendMatchListRQ(123);
             }
        });
//        std::thread thread3([&]{
//             while (true) {
//            sendCount_++;
//             }
//        });
        std::thread thread4([&]{
             while (true) {
                sendCount_++;
                 sendMatchJoinRQ(123, 30001);
                 sendMatchJoinRQ(123, 30001);
                sendMatchUnjoinRQ(123, 40001);
                sendMatchUnjoinRQ(123, 40001);
             }
        });
        thread1.detach();
        thread2.detach();
//        thread3.detach();
        thread4.join();
    }
    
public:
    void sendLoginRQ(int uid, const std::string& token);
    void sendMatchListRQ(int uid);
    void sendMatchJoinRQ(int uid, int mid);
    void sendMatchUnjoinRQ(int uid, int mid);

public:
    
    
private:
    zsock_t* loginDealer_;
    zsock_t* matchManagerDealer_;
    zsock_t* pub_;
    zsock_t* pull_;
    ZMQReactor reactor_;
    unsigned long long sendCount_{0};
    unsigned long long rcvCount_{0};
};
    
}



