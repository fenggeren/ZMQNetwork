//
//  ZMQGateWay.cpp
//  ZMQNode
//
//  Created by huanao on 2018/9/28.
//  Copyright © 2018年 huanao. All rights reserved.
//

#include "ZMQGateWay.hpp"

namespace ZGW
{
    void ZMQGateWay::sendLoginRQ(int uid, const std::string& token)
    {
        zmsg_t* msg = zmsg_new();
        zmsg_addstrf(msg, "%d--%s", uid, token.c_str());
        zmsg_send(&msg, loginDealer_);
        zmsg_destroy(&msg);
    }
    
    void ZMQGateWay::sendMatchListRQ(int uid)
    { 
        
        zmsg_t* msg = zmsg_new();
        zmsg_addstrf(msg, "%d", uid);
        zmsg_send(&msg, matchManagerDealer_);
        zmsg_destroy(&msg);
    }
    
    void ZMQGateWay::sendMatchJoinRQ(int uid, int mid)
    {
        
        zmsg_t* msg = zmsg_new();
        zmsg_addstrf(msg, "%d", mid);
        zmsg_addstrf(msg, "%d--%d", uid, mid);
        zmsg_send(&msg, pub_);
        zmsg_destroy(&msg);
    }
    
    void ZMQGateWay::sendMatchUnjoinRQ(int uid, int mid)
    {
        zmsg_t* msg = zmsg_new();
        zmsg_addstrf(msg, "%d", mid);
        zmsg_addstrf(msg, "%d--%d", uid, mid);
        zmsg_send(&msg, pub_);
        zmsg_destroy(&msg);
    }
}
