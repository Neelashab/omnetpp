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

#include "QueueModule.h"

QueueModule::QueueModule() {
    // Constructor (auto-generated)
}

QueueModule::~QueueModule() {
    // Destructor (auto-generated)
}

void QueueModule::initialize() {
    queueSize = par("queueSize");
    queueLengthSignal = registerSignal("queueLength");
}

void QueueModule::handleMessage(cMessage *msg) {
    if (queue.getLength() < queueSize) {
        queue.insert(msg);
        emit(queueLengthSignal, queue.getLength()); // Record queue length
        scheduleAt(simTime() + 0.1, new cMessage("processQueue"));
    } else {
        delete msg; // Drop packet if queue is full
    }
}

void QueueModule::processQueue() {
    if (!queue.isEmpty()) {
        cMessage *msg = check_and_cast<cMessage *>(queue.pop());
        send(msg, "out");
    }
}


