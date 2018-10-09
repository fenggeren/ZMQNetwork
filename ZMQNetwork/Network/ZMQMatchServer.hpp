//
//  ZMQMatchServer.hpp
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

namespace ZGW
{
    class ZMQMatchServer
    {
    public:
        
        ZMQMatchServer()
        {
            sub_ = zsock_new(ZMQ_SUB);
            push_ = zsock_new(ZMQ_PUSH);
        }
        
        void start()
        {
            unsigned long long count;
            zsock_connect(sub_, "tcp://%s:%d", GATEWAY_PUB_IP, GATEWAY_PUB_PORT);
            zsock_connect(push_, "tcp://%s:%d", GATEWAY_PULL_IP, GATEWAY_PULL_PORT);
            zsock_set_subscribe(sub_, "30001");
            zsock_set_subscribe(sub_, "40001");
            reactor_.addSocket(sub_, [&](zsock_t* sock){
                zmsg_t* msg = zmsg_recv(sock);
                zmsg_send(&msg, push_);
                zmsg_destroy(&msg);
                count++;
            });
            reactor_.addTimer(5000, INTMAX_MAX, [&]{
                printf("%llu\n", count);
            });
            reactor_.loop();
        }
        
        
    private:
        zsock_t* sub_;
        zsock_t* push_;
        
        ZMQReactor reactor_;
    };
}
