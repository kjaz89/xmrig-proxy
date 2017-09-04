/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <inttypes.h>


#include "proxy/Events.h"
#include "proxy/events/CloseEvent.h"
#include "proxy/events/ConnectionEvent.h"
#include "proxy/events/LoginEvent.h"
#include "proxy/events/SubmitEvent.h"
#include "proxy/ProxyDebug.h"
#include "log/Log.h"
#include "proxy/Miner.h"
#include "proxy/LoginRequest.h"


ProxyDebug::ProxyDebug()
{
    Events::subscribe(IEvent::ConnectionType, this);
    Events::subscribe(IEvent::CloseType, this);
    Events::subscribe(IEvent::LoginType, this);
    Events::subscribe(IEvent::SubmitType, this);
}


ProxyDebug::~ProxyDebug()
{
}


void ProxyDebug::onEvent(IEvent *event)
{
    switch (event->type())
    {
    case IEvent::ConnectionType: {
            auto e = static_cast<ConnectionEvent*>(event);
            LOG_INFO("[debug] connection <Miner id=%" PRId64 ", ip=%s> via port: %d", e->miner()->id(), e->miner()->ip(), e->port());
        }
        break;

    case IEvent::LoginType: {
            auto e = static_cast<LoginEvent*>(event);
            LOG_INFO("[debug] login <Miner id=%" PRId64 ", ip=%s>, <Request login=%s, agent=%s>", e->miner()->id(), e->miner()->ip(), e->request.login(), e->request.agent());
        }
        break;

    case IEvent::CloseType: {
            auto e = static_cast<CloseEvent*>(event);
            LOG_INFO("[debug] close <Miner id=%" PRId64 ", ip=%s>", e->miner()->id(), e->miner()->ip());
        }
        break;


    default:
        break;
    }
}


void ProxyDebug::onRejectedEvent(IEvent *event)
{
    switch (event->type())
    {
    case IEvent::ConnectionType: {
            ConnectionEvent *e = static_cast<ConnectionEvent*>(event);
            LOG_ERR("[error] connection <Miner id=%" PRId64 ", ip=%s> via port: %d", e->miner()->id(), e->miner()->ip(), e->port());
        }
        break;

    case IEvent::LoginType: {
            auto e = static_cast<LoginEvent*>(event);
            LOG_ERR("[error] login <Miner id=%" PRId64 ", ip=%s>, <Request login=%s, agent=%s>", e->miner()->id(), e->miner()->ip(), e->request.login(), e->request.agent());
        }
        break;

    case IEvent::CloseType: {
            auto e = static_cast<CloseEvent*>(event);
            LOG_INFO("[debug] close <Miner id=%" PRId64 ", ip=%s>", e->miner()->id(), e->miner()->ip());
        }
        break;

    default:
        break;
    }
}
