/**
 * Tencent is pleased to support the open source community by making Tseer available.
 *
 * Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
 * 
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * 
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */

#ifndef __API_LB_H_
#define __API_LB_H_

#include <string>
#include "TseerAgentComm.h"
#include "RollLogger.h"

using namespace std;
using namespace Tseer;

//节点状态信息
struct RouterNodeStat
{
    std::string        ip;
    unsigned int        port;
    unsigned int        succNum;                //成功次数
    unsigned int        errNum;                //错误次数
    unsigned int        continueErrNum;        //持续错误的次数
    unsigned long long    timeCost;                //耗时
    bool                available;                //是否可用
    unsigned long long    nextRetryTime;            //下次再尝试的时间（在状态不可用的时候设置尝试）
    unsigned long long    lastCheckTime;            //上次统计时间
    unsigned long long    continueErrTime;        //错误持续时间点（用做统计时间点前的错误信息）
};


class LoadBalance
{
public:
    virtual ~LoadBalance(){};

    //新增节点
    virtual int addRouter(const Tseer::RouterNodeInfo& nodeInfo) = 0;

    //根据负载均衡获取一个节点
    virtual int getRouter(Tseer::RouterNodeInfo& nodeInfo, string &errMsg);

    //根据负载均衡和key值获取一个节点，只当负载均衡算法与key值相关时此函数才有意义
    virtual int getRouter(unsigned long long key, Tseer::RouterNodeInfo& nodeInfo, string &errMsg);

    //获取所有节点
    virtual int getRouters(vector<Tseer::RouterNodeInfo> &nodeInfoList, string &errMsg);

    //清理节点
    virtual void clear() = 0;

    //重建所有状态
    virtual int rebuild() = 0;

    //删除指定的节点
    virtual int del(const vector<Tseer::RouterNodeInfo> &nodeInfoList) = 0;

    //记录节点调用状态
    virtual int statResult(const Tseer::RouterNodeInfo& nodeInfoRsp, int ret, int timeCost) = 0;
};


#endif
