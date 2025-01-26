//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "RoutingLayer.h"

Define_Module(RoutingLayer);

RoutingLayer::RoutingLayer() {
    // Constructor (auto-generated)
}

RoutingLayer::~RoutingLayer() {
    // Destructor (auto-generated)
}

void RoutingLayer::initialize() {
    routingAlgorithm = par("routingAlgorithm").stringValue();
}

void RoutingLayer::handleMessage(cMessage *msg) {
    cPacket *pkt = check_and_cast<cPacket *>(msg);
    int destAddress = pkt->par("destAddress");

    if (destAddress == getIndex()) {
        // Packet is for this node
        send(pkt, "localOut");
    } else {
        // Forward to the next hop
        int nextHop = findNextHop(destAddress);
        send(pkt, "out", nextHop);
    }
}

int RoutingLayer::findNextHop(int destAddress) {
    // Simplified routing logic: send to port 0
    return 0;
}

