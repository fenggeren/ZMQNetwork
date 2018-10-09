//
//  ZMQLogin.hpp
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
    class ZMQLogin
    {
    public:
        
        ZMQLogin()
        {
            router_ = zsock_new(ZMQ_ROUTER);
            push_ = zsock_new(ZMQ_PUSH);
            gateWayDealer_ = zsock_new(ZMQ_DEALER);
        }
        
        void start()
        {
//            zsock_bind(router_, "tcp://*:%d", LOGIN_ROUTER_PORT);
            zsock_connect(gateWayDealer_, "tcp://%s:%d", GATEWAY_LOGIN_DEALER_IP, GATEWAY_LOGIN_DEALER_PORT);
            zsock_connect(push_, "tcp://%s:%d", GATEWAY_PULL_IP, GATEWAY_PULL_PORT);
            reactor_.addSocket(gateWayDealer_, [&](zsock_t* sock){
                zmsg_t* msg = zmsg_recv(sock);
//                zframe_t* source = zmsg_pop(msg);
                zmsg_send(&msg, push_);
                zmsg_destroy(&msg);
//                zframe_destroy(&source);
            });
            reactor_.loop();
        }
        
    public:
        
        
    private:
        zsock_t* router_;
        zsock_t* push_;
        zsock_t* gateWayDealer_;
        ZMQReactor reactor_;
    };
}








