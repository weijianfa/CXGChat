//
//  PtlLoginRet.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"


PtlLoginRet::PtlLoginRet(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "PtlLoginRet\n");
}
