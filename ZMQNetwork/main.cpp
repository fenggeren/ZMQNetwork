//
//  main.cpp
//  ZMQNetwork
//
//  Created by huanao on 2018/9/28.
//  Copyright © 2018年 fgr. All rights reserved.
//

#include <iostream>
#include "ZMQLogin.hpp"
#include "ZMQMatchServer.hpp"
#include "ZMQMatchManager.hpp"
#include "ZMQGateWay.hpp"
#include <thread>


void test_gateway()
{
    ZGW::ZMQGateWay gateway;
    
    gateway.start();
}

void test_matchserver()
{
    ZGW::ZMQMatchServer matchserver;
    matchserver.start();
}

void test_login()
{
    ZGW::ZMQLogin login;
    login.start();
}

void test_matchmanager()
{
    ZGW::ZMQGateWay gateway;
    
    gateway.start();
}

int main(int argc, const char * argv[])
{
    test_gateway();
    return 0;
}






