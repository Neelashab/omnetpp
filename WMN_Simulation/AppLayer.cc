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

#include "AppLayer.h"

Define_Module(AppLayer);

AppLayer::AppLayer() {
    // Constructor (auto-generated)
}

AppLayer::~AppLayer() {
    // Destructor (auto-generated)
}

void AppLayer::initialize() {
    // Initialize parameters
    generationInterval = par("generationInterval");
    scheduleAt(simTime() + generationInterval, new cMessage("generatePacket"));
}

void AppLayer::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Generate and send a packet
        cPacket *pkt = new cPacket("AppPacket");
        send(pkt, "out");
        scheduleAt(simTime() + generationInterval, msg);
    } else {
        // Handle incoming packets
        delete msg; // For simplicity, just delete the received packet
    }
}
